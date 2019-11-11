(* Entiers : int *)

0 ;;
1653 ;;
-134564532 ;;
max_int ;;
min_int ;;

3 + 4 ;;
(+) 3 4 ;;
(+) 3 ;;
((+) 3) 4 ;;

( + ) ;;
( * ) ;;
( - ) ;;
( / ) ;;
( mod ) ;;

(* Flottants : float *)

0.0 ;;
0. ;;
2058720358. ;;
-346252. ;;
2345234.2346347 ;;
-. 234623.46 ;;

23452.4568 +. 2345.64536 ;;
( +. ) 23452.4568 2345.64536 ;;
( +. ) ;;
( *. ) ;;
( -. ) ;;
( /. ) ;;

int_of_float ;; (* float -> int *)
float_of_int ;; (* int -> float *)

int_of_float 3.14 ;;

sqrt ;;
exp ;;
log ;;
cos ;;
sin ;;
floor ;;
ceil ;;

int_of_float (ceil 3.15) ;;

(* Booléens : bool *)

true ;;
false ;;
not ;;
( && ) ;;
( || ) ;;

( = ) ;;
( <> ) ;;
( < ) ;;
( > ) ;;
( <= ) ;;
( >= ) ;;

(* Caractères : char *)

'f' ;;
'@' ;;
'\045' ;;

int_of_char ;;
char_of_int ;;
int_of_char 'a' ;;
char_of_int 45 ;;

(* Chaînes de caractères : string *)

"sdùmfgkjsdmfgklj" ;;
"23452345 \" SDFbxcvbxcbv" ;;
"\\" ;;

( ^ ) ;;
"Hello" ^ "World" ;;
("Hello World").[4] ;;

(* Abstraction *)

(fun x -> string_of_float ((float_of_int x) +. 1.)) ;;
(fun x -> string_of_float ((float_of_int x) +. 1.)) 80 ;;

(fun f -> f 3) (fun n -> n + 1) ;;
(fun n -> n + 1) ;;
(fun f -> f 3) ;;
(fun f -> f 3) float_of_int ;;
(fun f -> f 3) string_of_int ;;

(* Environnement *)

let successeur = fun x -> x + 1 ;;
successeur 3 ;;
successeur ;;

let distance =
  fun x1 ->
  fun y1 ->
  fun x2 ->
  fun y2 ->
    sqrt (  (x2 -. x1) *. (x2 -. x1)
         +. (y2 -. y1) *. (y2 -. y1) )
;;

let distance x1 x2 y1 y2 =
  let dx = x2 -. x1 in
  let dy = y2 -. y1 in
    sqrt ( dx *. dx +. dy *. dy )
;;


let x = 3 ;;

x + 2 ;;

let succ = fun x -> x + 1 ;;

let app_sur_3 = fun f -> f 3 ;;

app_sur_3 succ ;;

let succ x = x  + 1 ;;

let fact n = n + 5 ;;

let fact n = 
  if n = 0
  then 1
  else n * (fact (n-1))
;;

fact 5 ;;

