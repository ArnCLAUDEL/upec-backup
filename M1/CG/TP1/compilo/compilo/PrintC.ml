open CLessType
open Printf

(** Fonction d'impression pour le débogage de [CLessType] sous forme de code C*)       
                                            
let print_mop o = function
  | Not -> output_string o "!"
  | MinusM -> output_string o "-"
  | Deref -> output_string o "*"
    
let print_bop o = function
  | Mult -> output_string o "*"
  | Add -> output_string o "+"
  | Div -> output_string o "/"
  | Sub -> output_string o "-"
  | Mod -> output_string o "%"
  | And -> output_string o "&&"
  | Or -> output_string o "||"
  | EQ -> output_string o "=="
  | NEQ -> output_string o "!="
  | LE -> output_string o "<="
  | LL -> output_string o "<"
(* | Index -> output_string o "[]" 
  | SetReference -> output_string o "="*)

                        
let rec print_list sep f o = function
  | [] -> ()
  | h::[] -> f o h
  | h::t -> f o h;
            output_string o sep;
            print_list sep f o t

let print_tab o tab =
  let s = String.make tab ' ' in
  output_string o s
	      
let rec  print_expression o = function
  | Var s -> output_string o s
  | Const i -> output_string o (string_of_int i)
  | Set(s,e) -> fprintf o "%s=%a" s print_expression e
  | Call(s,el) -> fprintf o "%s(%a)" s (print_list "," print_expression) el
  | UOperator(m,e) ->
     fprintf o "(%a%a)"
                    print_mop m
                    print_expression e
  (*  | BOperator(e,Index,i) ->
     fprintf o "%a[%a]" print_expression e
       print_expression i
  | BOperator(e1,SetReference,e2) ->
     fprintf o "(*%a=%a)" print_expression e1
                    print_expression e2 "*)"*)
  | BOperator(e1,b,e2) ->
     fprintf o "(%a%a%a)" print_expression e1
                    print_bop b
                    print_expression e2
  | Seq(el) -> print_list ";\n" print_expression o el
  | String(s) -> output_string o ("\""^(String.escaped s)^"\"")
(*  | SetArray(s,i,e) -> fprintf o "%s[%a]=%a" s print_expression i print_expression e
  | Ref s -> fprintf o "&%s" s*)
                               
let print_var tab o s =
  fprintf o "%aint %s" print_tab tab s
    
let rec print_declaration o = function
  | VarDec(s,None) -> fprintf o "%aint %s" print_tab 0 s
  | VarDec(s,Some i) -> fprintf o "%aint %s=%i" print_tab 0 s i
  | FunDec(s,dl,BlockStat(varl,statl)) -> fprintf o "int %s(%a)%a\n" s
                                        (print_list "," (print_var 0)) dl
                                        (print_statement 0) (BlockStat(varl,statl))
  | FunDec(s,dl,stat) -> fprintf o "int %s(%a){%a}\n" s
                                        (print_list "," (print_var 0)) dl
                                        (print_statement 0) stat
                                        
and print_statement tab o = function
  | Expr(e) -> fprintf o "%a%a;\n" print_tab tab print_expression e
  | BlockStat(dl,sl) ->
     fprintf o "%a{\n" print_tab tab;
     print_list ";\n" (print_var (tab+2)) o dl;
     if List.length dl > 0 then output_string o ";\n";
     print_list "" (print_statement (tab+2)) o sl;
     fprintf o "%a}\n" print_tab tab;
  | IfStat(e,s1,s2) ->
     fprintf o "%aif(%a)\n%a%aelse\n%a" print_tab tab
                    print_expression e
                    (print_statement (tab+2)) s1 print_tab tab
                    (print_statement (tab+2)) s2
  |  WhileStat(e,s) -> fprintf o "%awhile(%a)\n%a" print_tab tab
                                      print_expression e
                                      (print_statement (tab+2)) s
  | ReturnStat(None) -> fprintf o "%areturn ;\n" print_tab tab
  | ReturnStat(Some s) -> fprintf o "%areturn %a;\n" print_tab tab print_expression s
