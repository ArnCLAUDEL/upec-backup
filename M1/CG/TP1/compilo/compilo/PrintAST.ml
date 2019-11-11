open CLessType
open Format
       
(** Fonction d'impression pour le débogage de [CLessType] sous forme d'AST*)


       
let print_mop o = function
  | Not -> fprintf o "Not"
  | MinusM -> fprintf o "MinusM"
  | Deref -> fprintf o "Deref"

let print_bop o = function
  | Mult -> fprintf o "Mult"
  | Add -> fprintf o "Add"
  | Div -> fprintf o "Div"
  | Sub -> fprintf o "Sub"
  | Mod -> fprintf o "Mod"
  | And -> fprintf o "And"
  | Or -> fprintf o "Or"
  | EQ -> fprintf o "EQ"
  | NEQ -> fprintf o "NEQ"
  | LE -> fprintf o "LE"
  | LL -> fprintf o "LL"
(* | Index -> fprintf o "Index" 
  | SetReference -> fprintf o "SetReference"*)

let rec print_list sep f o = function
  | [] -> ()
  | h::[] -> f o h
  | h::t -> f o h;
            fprintf o sep;
            print_list sep f o t
                       
let print_tab o tab =
  let s = String.make tab ' ' in
  fprintf o "%s" s
	      
let rec  print_expression o = function
  | Var s -> fprintf o  "@[<hv 2>Var@ \"%s\"@]" s
  (*  | Ref s -> fprintf o "Ref \"%s\"" s*)
  | Const i -> fprintf o  "@[<hv 2>Const@ %i@]" i
  | Set(s,e) -> fprintf o "@[<hv 2>Set@ (\"%s\",%a)@]" s print_expression e
  | Call(s,el) -> fprintf o "@[<hv 2>Call@ (\"%s\",[%a])@]" s (print_list "," print_expression) el
  | UOperator(m,e) ->
     fprintf o "@[<hv 2>UOperator@ (%a,%a)@]"
             print_mop m
             print_expression e
(*  | BOperator(e,Index,i) ->
     fprintf o "%a[%a]" print_expression e
       print_expression i*)
  | BOperator(e1,b,e2) ->
     fprintf o "@[<hv 2>BOperator@ (%a,%a,%a)@]" print_expression e1
                    print_bop b
                    print_expression e2
  | Seq(el) -> fprintf o "[%a]" (print_list ";@;" print_expression) el
  | String(s) -> fprintf o ("\"%s\"") (String.escaped s)
(*  | SetArray(s,i,e) -> fprintf o "%s[%a]=%a" s print_expression i print_expression e*)

let perror_exp e =
  fprintf err_formatter "Fail to generate %a\n" print_expression e
                         
                       
let print_escaped o s =
  fprintf o "\"%s\"" s
                               
let rec print_declaration o = function
  | VarDec(s,None) -> fprintf o "@[<hv 2>VarDec@ \"%s\"@]" s
  | VarDec(s,Some i) -> fprintf o "@[<hv 2>VarDec@ \"%s=%i\"@]" s i
  | FunDec(s,dl,stat) -> fprintf o "@[<hv 2>FunDec(\"%s\",[%a],%a)@]" s
                                        (print_list ";" print_escaped) dl
                                        (print_statement) stat
and print_statement o = function
  | Expr(e) -> fprintf o "@[<hv 2>Expr(%a)@]" print_expression e
  | BlockStat(dl,sl) ->
     fprintf o "@[<hv 2>BlockStat([%a],@,[%a])@]"
             (print_list ";@;" print_escaped) dl
             (print_list ";@;" print_statement) sl
  | IfStat(e,s1,s2) ->
     fprintf o "@[<hv 2>IfStat(%a,@,%a,@,%a)@]"
             print_expression e
             (print_statement) s1
             (print_statement) s2
  | WhileStat(e,s) -> fprintf o "@[<hv 2>WhileStat(%a,@,%a)@]"
                              print_expression e
                              print_statement s
  | ReturnStat(None) -> fprintf o "@[<hv 2>ReturnStat@ (None)@]"
  | ReturnStat(Some s) -> fprintf o "@[<hv 2>ReturnStat@ (Some@ (%a))@]" print_expression s

let perror_stat e =
  fprintf err_formatter "Fail to generate %a\n" print_statement e
                                  
let print_dec_list o dl =
  fprintf o "[@[<hv 2>@;%a@;@]]@." (print_list ";@;" print_declaration) dl  
          
