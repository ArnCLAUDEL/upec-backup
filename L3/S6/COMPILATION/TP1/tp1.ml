type 'a env = Empty | Env of string * 'a * 'a env ;;

let empty_env = Empty ;;

let add_env s1 v1 e1 = 
		Env(s1,v1,e1)
;;

let rec find_env =
	fun s ->
	fun e ->
		match e with
		| Empty -> None
		| Env(s1,v,e1) -> if(s = s1) then Some(v)
							else find_env s e1
	;;


type expr = 
	| Const of int
	| Add of expr * expr
	| Sub of expr * expr
	| Neg of expr
	| Mul of expr * expr
	| Div of expr * expr
	| Mod of expr * expr
	| Id of string 
	| If of cond * expr * expr

type cond =
	| False
	| True
	| Eq of expr * expr
	| Dif of expr * expr
	| Inf of expr * expr
	| InfOrEq of expr * expr
	| Not of cond
	| And of cond * cond
	| Or of cond * cond
	| Id of string
;;

let rec pp_expr =
	fun e ->
	match e with
		| Const x -> Printf.sprintf "%i" x
		| Add (e1,e2) -> " ("^(pp_expr e1)^" + "^(pp_expr e2)^") "
		| Sub (e1,e2) -> " ("^(pp_expr e1)^" - "^(pp_expr e2)^") "
		| Neg e1 -> " (-"^(pp_expr e1)^") "
		| Mul (e1,e2) -> " ("^(pp_expr e1)^" * "^(pp_expr e2)^") "
		| Div (e1,e2) -> " ("^(pp_expr e1)^" / "^(pp_expr e2)^") "
		| Mod(e1,e2) -> " ("^(pp_expr e1)^" % "^(pp_expr e2)^") "
		| Id s ->  s
		| If(c,e1,e2) -> Printf.sprintf "if(%s) then (%s) else (%s)" (pp_cond c) (pp_expr e1) (pp_expr e2)
;;

let rec eval_expr =
	fun env ->
	fun e ->	
	match e with
		| Const x -> x
		| Add (e1,e2) -> (+) (eval_expr env e1) (eval_expr env e2)
		| Sub (e1,e2) ->  (eval_expr env e1) - (eval_expr env e2)
		| Neg e1 -> (eval_expr env e1) * (-(1))
		| Mul (e1,e2) ->  (eval_expr env e1) * (eval_expr env e2)
		| Div (e1,e2) ->  (eval_expr env e1) / (eval_expr env e2)
		| Mod(e1,e2) -> (eval_expr env e1) mod (eval_expr env e2)
		| Id s ->  (match find_env s env with
		               | Some v -> v
		               | None -> failwith (s^ "n'existe pas"))
		| If(c,e1,e2) -> (match (eval_cond c) with
							| true -> (eval_expr e1)
							| false -> (eval_expr e2))
		               
;;

(* Test *)
let e2 = Const(2) ;;
let e4 = Const(4) ;;
let e5 = Const(5) ;;
let e10 = Const(10) ;;

let em1 = Mul(e2,e10);;
let es1 = Sub(e10,e5);;
let en1 = Neg(e2);;
let ed1 = Div(e4,e2);;
let emo1 = Mod(e10,e5);;
let eId1 = Id("x");;

let env = add_env "x" 6 empty_env;;



pp_expr e2 ;;
pp_expr em1;;
pp_expr es1;;
pp_expr ed1;;
pp_expr emo1;;
pp_expr en1;;
pp_expr eId1;;
eval_expr env eId1

(* End of test *)

let rec pp_cond =
	fun c ->
	match c with
		| True -> "true"
		| False -> "false"
		| Eq (e1,e2) -> " ("^(pp_expr e1)^" = "^(pp_expr e2)^") "
		| Dif(e1,e2) -> " ("^(pp_expr e1)^" <> "^(pp_expr e2)^") "
		| Inf(e1,e2) -> " ("^(pp_expr e1)^" < "^(pp_expr e2)^") " 
		| InfOrEq(e1,e2) -> " ("^(pp_expr e1)^" <= "^(pp_expr e2)^") "
		| Not c1 -> " ( not("^(pp_cond c1)^") )"
		| And(c1,c2) -> " ("^(pp_cond c1)^" and "^(pp_cond c2)^") "
		| Or(c1,c2) -> " ("^(pp_cond c1)^" or "^(pp_cond c2)^") " 
		| Id s -> s
;;

let rec eval_cond =
	fun envInt -> 
	fun envBool ->
	fun c ->
	match c with
	| True -> true
	| False -> false
	| Eq (e1,e2) -> ( (eval_expr envInt e1) = (eval_expr envInt e2) )
	| Dif(e1,e2) -> ( (eval_expr envInt e1) != (eval_expr envInt e2) )
	| Inf(e1,e2) -> ( (eval_expr envInt e1) < (eval_expr envInt e2) )
	| InfOrEq(e1,e2) -> ( (eval_expr envInt e1) <= (eval_expr envInt e2) )
	| Not c1 -> ( not (eval_cond envInt envBool c1) )
	| And(c1,c2) -> ( (eval_cond envInt envBool c1) && (eval_cond envInt envBool c2) )
	| Or(c1,c2) -> ( (eval_cond envInt envBool c1) || (eval_cond envInt envBool c2) )
	| Id s ->  match find_env s envBool with
	               | Some v -> v
	               | None -> failwith (s^ "n'existe pas")
;;

type constant =
	| Int of int
	| Float of float
;;

let app op1 op2 =
	fun x1 ->
	fun x2 ->
	match (x1,x2) with
	| (Float x3,Int y3) ->  Float( op1 x3 (float_of_int y3))
	| (Int x3,Float y3) ->  Float(op1 (float_of_int x3)  y3)
	| (Float x4, Float y4) -> Float(op1 x4 y4)
	| (Int x5, Int y5) -> Int(op2 x5  y5)

let mul x1 x2 = app ( *. ) ( * ) x1 x2
let add x1 x2 = app (+.) (+) x1 x2 
let neg x1 = app ( *. ) ( * ) x1 (Int(-1))
let sub x1 x2 = app (-.) (-) x1 x2
let div x1 x2 = app (/.) (/) x1 x2

let modulo =
	fun x1 ->
	fun x2 ->
	match (x1,x2) with
	| (Float x3,Int y3) ->  Int((int_of_float x3) mod y3)
	| (Int x3,Float y3) ->  Int(x3 mod (int_of_float y3))	
	| (Float x4, Float y4) -> Int(( int_of_float x4) mod (int_of_float y4) )
	| (Int x5, Int y5) -> Int(x5 mod y5)
