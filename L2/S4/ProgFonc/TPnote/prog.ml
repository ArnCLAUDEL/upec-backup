(* Fonction récursive *)

let rec f x y =
	let r = 0 in
	match x with
		| 0 -> r 
		| _ -> if((x mod 2) == 1) then
					let r = r + y in
					let x = x - 1 in
						f (x/2) (y*2)
				else f (x/2) (y*2)
;;

(* fonctions sur les listes *)

(*
let rec series l =
	match l with
	| []
	| None :: [] -> []
	| (Some x) :: [] -> x :: []
	| (Some x) :: (None :: t) -> x :: series t  (* je ne sais plus comment implémenter des list list *)
	| (Some x) :: ((Some y) :: t) -> (x :: y) :: series t
;;
*)

(* Structures inductives *)

type device = Device of int * bool ;;
type reseau = 
			| Pc of device 
			| Serveur of device 
			| Firewall of device * reseau 
			| Routeur of device * reseau list
;;

let rec simplifie r =
	match r with
	| Firewall(d,r2) ->  Firewall(d,(simplifie r2))
	| Routeur(_,(r2 :: [])) -> r2
	| Routeur(mac,(r2 :: rl)) -> simplifie (Routeur(mac,rl)) 	
	| _ -> r
;; 

let dAllume d =
	match d with
	| Device(_,b) -> b
;;

let rec forall p l =
	match l with
	| [] -> false
	| h :: t -> (p h)&(forall p t)
;;

(*

let rec allumes r =
	match r with
	| Firewall(_,r2) -> allumes r2
	| Routeur(_) -> (forall dAllume )
;;
*)