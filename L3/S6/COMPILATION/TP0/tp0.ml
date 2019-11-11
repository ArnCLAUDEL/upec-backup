type regex = Vide | Epsilon 
			| Lettre of char 
			| Plus of regex * regex 
			| Concat of regex * regex
			| Etoile of regex

let rec pp r = match r with
  | Vide -> "0"
  | Epsilon -> "eps"
  | Lettre c -> Printf.sprintf "%c" c
  | Plus (Lettre a, Lettre b) -> Printf.sprintf "%c + %c" a b
  | Plus (Lettre a, r2) -> Printf.sprintf "%c + (%s)" a (pp r2)
  | Plus (r1, Lettre b) -> Printf.sprintf "(%s) + %c" (pp r1) b
  | Plus (r1, r2) -> Printf.sprintf "(%s) + (%s)" (pp r1) (pp r2)
  | Concat (r1, r2) -> Printf.sprintf "%s%s" (pp r1) (pp r2)
  | Etoile r -> Printf.sprintf "(%s)*" (pp r)
 

let rec nullable r = 
	match r with
		| Vide -> false
		| Epsilon -> true
		| Lettre l -> false
		| Plus(r1,r2) -> nullable r1 || nullable r2
		| Concat(r1,r2) -> nullable r1 && nullable r2
		| Etoile _ -> true


let rec deriv c r =
	match r with
		| Vide -> Vide
		| Epsilon -> Vide
		| Lettre l -> 	if( l=c ) then Epsilon 
						else Vide
		| Plus (r1, r2) -> Plus((deriv c r1), (deriv c r2))
		| Concat(r1,r2) -> Plus (Concat((deriv c r1),r2),
									if(nullable r1) then deriv c r2
									else Epsilon
									)
		|Etoile r1 -> Concat(deriv c r1, r1)
;; 

let r1 = Concat(Concat(Lettre('a'),Lettre('b')),Lettre('c'));;
let r =
  Concat (
    Etoile (Plus (Lettre 'a', Lettre 'b')),
    Concat (
      Concat (Lettre 'a', Lettre 'b'), 
      Etoile (Plus (Lettre 'a', Lettre 'b'))
    )
  )
;;
pp r;;
pp (deriv 'a' r) ;;



