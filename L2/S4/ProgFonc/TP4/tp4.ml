type ('a, 'b)tree = Leaf of 'a | Node of ('a, 'b)tree * 'b * ('a, 'b)tree ;;

let rec read t bl =
	match t with
	| Leaf(a) -> (a,bl)
	| Node(l,_,r) -> match bl with
					| true :: tl -> read r tl 
					| false :: tl-> read l tl
;;


let l1 = Leaf('a') ;;
let l2 = Leaf('b') ;;
let n1 = Node(l1,1,l2) ;;

let l3 = Leaf('d') ;;
let l4 = Leaf('e') ;;
let n2 = Node(l3,2,l4) ;;

let n3 = Node(n1,3,n2) ;;

let bl1 = true :: ( false  :: []) ;;

read n3 bl1 ;;

(* décodage *)

let rec insert l e =
	match l with
	| [] -> e :: []
	| h :: t -> if( e > h) then e :: l
				else insert t e
;;

let rec to_list w = 
	match w with
	| "" -> []
	| "a'^_"^"_" -> w.[0] :: []

;;

let a  = to_list "ab" ;; 