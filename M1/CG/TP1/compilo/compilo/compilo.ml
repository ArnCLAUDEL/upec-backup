open ASMType
open CLessType
open Tools
       
let input = ref stdin
let output = ref stdout
let inputName = ref "stdin"
let outputName = ref "a.out"
let doLinking = ref true
let pp = ref false
let pt = ref false
let ptdot = ref false
let exec = ref None
let optim = ref 0
let interpret = ref 0
let inline = ref false
                    
let _ = Arg.parse [
  "-o", Arg.Set_string outputName, "Output file";
  "-S", Arg.Clear doLinking, "Output assembly";
  "-O", Arg.Set_int optim, "Optimisation level";
  "-p", Arg.Set pp, "print preprocessing";
  "-d", Arg.Set ptdot, "print AST as dot";
  "-t", Arg.Set pt, "print AST";
  "--inline", Arg.Set inline, "Use function inlining";
  "-i", Arg.Set_int interpret, "Interpret assembly 0 -> No; 1 -> Yes; 2 -> With debug; 3 -> Step by step";
  "--", Arg.Rest (fun s -> exec := Some s), "Execute the outputted program";
]
                  (function s ->
                            inputName := s;
                            input := open_in s)
    "usage"

module StringSet = Set.Make(String)
  
let isLinux =
  let fo = Unix.open_process_in "uname" in
  let s = input_line fo in
  close_in fo;
  (String.sub s 0 5) = "Linux"

let renameExt s =
  if isLinux then s
  else "_"^s

let rec renameIt fs = function
  | Call(fn,el) when not (StringSet.mem fn fs) ->
     Some (Call(renameExt fn,List.map (iter_fun_expr (renameIt fs)) el))
  | _ -> None
     
let externalizeFun fl =
  let inFun,inVar = List.fold_left (fun (fs,vs) f ->
                  match f with
                    FunDec(n,_,_) -> (StringSet.add n fs,vs)
                  | VarDec(n,nv) -> (fs,(n,nv)::vs))
                                   (StringSet.empty,[]) fl in
  fl
  |> List.filter (function FunDec(_)-> true | _ -> false)
  |> List.map (function
               |  FunDec("main",dl,s) ->
                   FunDec(renameExt "main",dl, iter_fun_stat (renameIt inFun) (fun _-> None) s)
            |  FunDec(fn,dl,s) -> FunDec(fn,dl,iter_fun_stat (renameIt inFun) (fun _-> None) s)
            | _ -> failwith "no global variable declaration")
  |> (fun x -> x,inVar)

let initProg =
  ASMType.LinkInstr ("globl "^renameExt "main")
  :: (if isLinux then [ASMType.LinkInstr "text"]
  else [ASMType.LinkInstr "section __TEXT,__text,regular,pure_instructions"]) 

let rosection = ASMType.LinkInstr (if isLinux then "section\t.rodata"
  else "section    __TEXT,__cstring,cstring_literals")

  
let _ =
  let defList = try
    let lexbuf = Lexing.from_channel (!input) in
    CLessGram.translation_unit CLessLex.ctoken lexbuf
    with
      Parsing.Parse_error ->
      Printf.fprintf stderr "%s:%i:%i: Parse Error\n" !inputName !cline !ccol;
      exit 1 in
  
  if (!pp) then List.iter (fun x ->
		 Printf.fprintf stdout "%a\n" PrintC.print_declaration x) defList;
  if (!pt) then PrintAST.print_dec_list Format.std_formatter defList;
  let defListExt,globVarSet = externalizeFun defList in
  let varList,prog =
    globVarSet
    |> List.fold_left (fun (vl,il) (v,nv) ->
			 let label = Tools.fresh_lbl ("globvar_"^v) in
			 (v,(ASMType.ARL (label,ASMType.RIP)))::vl,
			 (ASMType.GlobVar(label,nv))::il
			) ([],initProg)
  in
  if !inline || !optim > 1 then List.iter (function
	    | FunDec(fn,al,s)-> funDecList:= StringMap.add  fn (al,s) !funDecList;
            | VarDec(_) ->()) defListExt;
  (*let defListExt2 = (if !optim > 1 then OptimisationAST.inlineFun defListExt
                       else defListExt ) in*)
  let asm_prog = defListExt
    |> (fun x ->try List.fold_left (Generate.generate_asm_top varList) prog x
                with
                | Code_gen_failure_expression e as exn -> PrintAST.perror_exp e; raise exn;
                | Code_gen_failure_statment s as exn ->  PrintAST.perror_stat s; raise exn;
                | e -> Printf.fprintf stderr "Exception in Generate.ml\n"; raise e)
    |> (fun x -> rosection::x)
    |> Hashtbl.fold (fun a b il -> ASMType.StrLit (a) :: ASMType.Label (L b) :: il) string_tab
    |> List.rev
(*    |> (fun x -> if !optim >0 then
	         x
                 |> Optimisation.removeZeroAdd 
                 |> Optimisation.removePopPush
	         |> Optimisation.removeDeadCode
	       else x)*)
  in 
  if !doLinking then
    let o = Unix.open_process_out ("cc -x assembler -o "^ !outputName ^" -") in
    output := o;
  else if !outputName <> "a.out" then
    output := open_out !outputName;
  
  List.iter (ASMType.print_instruction !output) asm_prog;

  if !doLinking then
    ignore (Unix.close_process_out !output);
  
  if !interpret >0 then
    let (linked,rip) =
      let alloc = Interpreter.allocator (renameExt "malloc") in
      Interpreter.link (renameExt "main") (List.rev_append alloc asm_prog) in
    if !interpret >1 then Array.iteri (fun i ins ->
      let ins2 = ASMType.map_arg Interpreter.unbox_arg ins in
      Printf.printf "%i>%a" i ASMType.print_instruction ins2) linked;
    let machine = Interpreter.new_state (linked,rip) 1024 in
    exit (Interpreter.run_machine !interpret machine)
      
let _ = match !exec with
    Some e -> ignore (Sys.command ("./"^ !outputName^" "^e)) 
  | _ -> ()
           
           
