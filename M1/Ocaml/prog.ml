type regexp =
	| Vide
	| Epsilon
	| Lettre 	of char
	| Plus 		of regexp * regexp
	| Concat 	of regexp * regexp
	| Etoile 	of regexp
;;

let rec pp r = 
	match r with
		| Vide 				-> "0"
		| Epsilon 			-> "eps"
		| Lettre c 			-> Printf.sprintf "%c" c
		| Plus (r1,r2) 		-> Printf.sprintf "%s + %s" (pp r1) (pp r2)
		| Concat (r1,r2) 	-> Printf.sprintf "(%s)(%s)" (pp r1) (pp r2)
		| Etoile (r) 		-> Printf.sprintf "%s *" (pp r)
;;

let rec nullable r = 
	match r with
		| Vide 				-> false
		| Epsilon 			-> true
		| Lettre _ 			-> false
		| Plus (r1,r2) 		-> (nullable r1) || (nullable r2)
		| Concat (r1,r2) 	-> (nullable r1) && (nullable r2)
		| Etoile (r) 		-> true
;;

let rec deriv c r =
	match r with
		| Vide 				-> Vide
		| Epsilon			-> Vide
		| Lettre (c2) 		-> if (c == c2)
								then Epsilon
								else Vide
		| Plus (r1,r2) 		-> Plus( (deriv c r1),(deriv c r2) )
		| Concat (r1,r2) 	-> if (nullable r1)
								then Plus( Concat((deriv c r1),r2), (deriv c r2) )
								else Concat( (deriv c r1),r2 )
		| Etoile(r) 		-> Concat( (deriv c r),Etoile(r) )							
;;