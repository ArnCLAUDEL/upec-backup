(* Syntaxe abstraite *)
type expr
type cond

(* Constructeurs d'expression *)
val cst: int -> expr
val add: expr -> expr -> expr
val neg: expr -> expr
val mul: expr -> expr -> expr
val par: expr -> expr
val div: expr -> expr -> expr
val mMod: expr -> expr -> expr


val mBool: bool -> cond
val eq: expr -> expr -> cond
val dif: expr -> expr -> cond
val inf: expr -> expr -> cond
val inforeq: expr -> expr -> cond
val mNot: cond -> cond
val mAnd: cond -> cond -> cond
val mOr: cond -> cond -> cond

(* Conversion en chaîne de caractères pour affichage *)
val string_of_expr: expr -> string
val string_of_cond: cond -> string

(* Evaluateur *)
val eval: expr -> int
val eval_cond: cond -> bool