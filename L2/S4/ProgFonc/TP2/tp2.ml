"-----------------" ;;	
"(* Introduction *)" ;;
"-----------------" ;;
let empty l =
	match l with
	| [] -> true
	| _ -> false
;;

"-----------------" ;;	
"(* Récursivité sur les listes I *)" ;;
"-----------------" ;;

let rec length l =
	match l with
	| [] -> 0
	| h :: [] -> 1
	| h :: t -> 1 + length t
;;

let rec mem e l =
	match l with
	| [] -> false
	| h :: [] -> if(e == h) then true else false
	| h :: t -> if(e == h) then true else mem e t
;;

"-----------------" ;;	
"(* Récursivité sur les listes II *)" ;;
"-----------------" ;;

let rec nth (l,ie) =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> if(ie == 1) then h else failwith("Element inconnu")
	| h :: t -> if(ie == 1) then h else nth (t,(ie-1))
;;

let rec drop (l,ie) =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> if(ie == 1) then [] else h :: []
	| h :: t -> if(ie == 1) then drop (t,0) else h :: drop (t,(ie-1))
;;

let rec insert e (l,i) =
	match l with
	| [] -> e :: []
	| h :: [] -> if(i == 1) then e :: h :: [] else h :: e :: []
	| h :: t -> if(i == 1) then h :: e :: t else h :: insert e (t,(i-1))
;;

let rec compare (l1,l2) =
	match (l1,l2) with
	| ([],[]) -> true
	| ([],_)
	| (_,[]) -> false
	| (h1 :: [],h2 :: []) -> h1 == h2
	| (h1 :: [],h2 :: t2) -> false
	| (h1 :: t1,h2 :: []) -> false
	| (h1 :: t1,h2 :: t2) -> if(h1 == h2) then compare(t1,t2) else false
;;

let rec append (l1,l2) =
	match (l1,l2) with
	| ([],[]) -> []
	| (l,[])
	| ([],l) -> l
	| (h1 :: [],l)
	| (l, h1 :: []) ->  h1 :: l
	| (l, h2 :: t2) -> append(h2 :: l,t2)
;;

let rec rev l =
	match l with
	| [] -> []
	| h :: [] -> h :: []
	| h :: t -> h :: rev t
;;

"-----------------" ;;	
"(* Itérateur map *)" ;;
"-----------------" ;;

let rec abs_list l =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> if(h < 0) then (h*(-1)) :: [] else h :: []
	| h :: t -> if(h < 0) then (h*(-1)) :: (abs_list t) else h :: (abs_list t)
;;

let rec not_list l =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> if(h == true) then false :: [] else true :: []
	| h :: t -> if(h == true) then false :: (not_list t) else true :: (not_list t)
;;

let rec int_list_of_string_list l =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> int_of_string h :: []
	| h :: t -> (int_of_string h) :: (int_list_of_string_list t)
;; 

let rec map f l =
	match l with
	| [] -> failwith("Liste non-vide attendue")
	| h :: [] -> (f h) :: []
	| h :: t -> (f h) :: (map f t)
;;

"-----------------" ;;	
"(* Filtre et partition de liste *)" ;;
"-----------------" ;;

let even x =
	(x) mod 2 == 0
;;


let rec even_list l =
	match l with
	| [] -> []
	| h :: [] -> if(even h) then h :: [] else []
	| h :: t -> if(even h) then h :: (even_list t) else even_list t
;;

let empty_string s =
	match s with
	| "" ->  true
	| _ -> false
;;

let rec no_empty_string_list l =
	match l with
	| [] -> []
	| h :: [] -> if(empty_string h) then [] else h :: []
	| h :: t -> if(empty_string h) then no_empty_string_list t else h :: no_empty_string_list t
;;

let rec filter f l =
	match l with
	| [] -> []
	| h :: [] -> if(f h) then h :: [] else [] 
	| h :: t -> if(f h) then h :: filter f t else filter f t  
;;
