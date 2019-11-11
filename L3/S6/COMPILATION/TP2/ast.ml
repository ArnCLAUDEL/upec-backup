(* Syntaxe abstraite *)
type expr =
  | ECst of int
  | EAdd of expr * expr 
  | EMul of expr * expr
  | ENeg of expr
  | EPar of expr
  | EDiv of expr * expr
  | EMod of expr * expr

type cond =
  | CFalse
  | CTrue
  | CEq of expr * expr
  | CDif of expr * expr
  | CInf of expr * expr
  | CInfOrEq of expr * expr
  | CNot of cond
  | CAnd of cond * cond
  | COr of cond * cond

(* Constructeurs d'expressions *)
let cst i = ECst i

let add e1 e2 = EAdd (e1, e2)

let neg e = ENeg e

let mul e1 e2 = EMul (e1,e2)

let par e = EPar e

let div e1 e2 = EDiv (e1,e2)

let mMod e1 e2 = EMod (e1,e2)

let mBool b = match b with
              | true  -> CTrue
              | false -> CFalse

let eq e1 e2 = CEq(e1,e2)

let dif e1 e2 = CDif(e1,e2)

let inf e1 e2 = CInf(e1,e2)

let inforeq e1 e2 = CInfOrEq(e1,e2)

let mNot c = CNot(c)

let mAnd c1 c2 = CAnd(c1,c2) 

let mOr c1 c2 = COr(c1,c2)

(* Conversion en chaîne de caractères pour affichage *)
let rec string_of_expr e = match e with
  | ECst i        -> string_of_int i
  | EAdd (e1, e2) -> Printf.sprintf "(%s) + (%s)" (string_of_expr e1) (string_of_expr e2)
  | EMul (e1, e2) -> Printf.sprintf "(%s) * (%s)" (string_of_expr e1) (string_of_expr e2)
  | ENeg e        -> Printf.sprintf "-(%s)" (string_of_expr e)
  | EPar e        -> Printf.sprintf "(%s)" (string_of_expr e)
  | EDiv (e1,e2)  -> Printf.sprintf "(%s) / (%s)" (string_of_expr e1) (string_of_expr e2)
  | EMod (e1,e2)  -> Printf.sprintf "(%s) mod (%s)" (string_of_expr e1) (string_of_expr e2)

let rec string_of_cond =
  fun c ->
  match c with
    | CTrue           -> "true"
    | CFalse          -> "false"
    | CEq (e1,e2)     -> Printf.sprintf "(%s) = (%s)" (string_of_expr e1) (string_of_expr e2)
    | CDif(e1,e2)     -> Printf.sprintf "(%s) <> (%s)" (string_of_expr e1) (string_of_expr e2)
    | CInf(e1,e2)     -> Printf.sprintf "(%s) < (%s)" (string_of_expr e1) (string_of_expr e2)
    | CInfOrEq(e1,e2) -> Printf.sprintf "(%s) <= (%s)" (string_of_expr e1) (string_of_expr e2)
    | CNot c1         -> Printf.sprintf "(not (%s))" (string_of_cond c1)
    | CAnd(c1,c2)     -> Printf.sprintf "(%s) and (%s)" (string_of_cond c1) (string_of_cond c2)
    | COr(c1,c2)      -> Printf.sprintf "(%s) or (%s)" (string_of_cond c1) (string_of_cond c2)


(* Evaluateur *)
let rec eval e = match e with
  | ECst i        -> i
  | EAdd (e1, e2) -> (eval e1) + (eval e2)
  | EMul (e1, e2) -> (eval e1) * (eval e2)
  | EDiv (e1, e2) -> (eval e1) / 
      ( match (eval e2) with
        | 0 -> failwith "Cannot div with 0"
        | x -> x )
  | EMod (e1, e2) -> (eval e1) mod (eval e2)
  | ENeg e        -> - (eval e)
  | EPar e        -> eval e


let rec eval_cond =
  fun c ->
  match c with
  | CTrue           -> true
  | CFalse          -> false
  | CEq (e1,e2)     -> ( (eval e1) = (eval e2) )
  | CDif(e1,e2)     -> ( (eval e1) != (eval e2) )
  | CInf(e1,e2)     -> ( (eval e1) < (eval e2) )
  | CInfOrEq(e1,e2) -> ( (eval e1) <= (eval e2) )
  | CNot c1         -> ( not (eval_cond c1) )
  | CAnd(c1,c2)     -> ( (eval_cond c1) && (eval_cond c2) )
  | COr(c1,c2)      -> ( (eval_cond c1) || (eval_cond c2) )
;;