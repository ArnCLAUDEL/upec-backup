type couleur = Trefle | Carreau | Coeur | Pique;;

type valeur = Nombre of int | Valet | Dame | Roi ;;

let valeur_valide v =
	match v with
		| Nombre n -> n > 0 && n <= 10
		| Valet | Dame | Roi -> true
;;
		
let force_of_valeur v =
	match v with
		|Nombre 1 -> 13
		|Nombre n -> n
		|Valet -> 10
		|Dame -> 11
		|Roi -> 12
;;

type carte = Carte of valeur * couleur ;;

let carte_joueur1 = Carte(Nombre 8, Trefle) ;;
let carte_joueur2 = Carte(Roi, Coeur) ;; 

(* Exercice sur les cartes *)

let carte_valide c = 
	match c with
		|Carte(Nombre n,couleur) -> n > 0 && n <= 13
		|Carte(Valet,couleur)
		|Carte(Dame,couleur)
		|Carte(Roi,couleur) -> true
;;

let string_of_couleur c =
	match c with
		| Coeur -> "de coeur"
		| Trefle-> "de trefle"
		| Pique-> "de pique"
		| Carreau-> "de carreau"
;;

let string_of_valeur v =
	match v with
	| Nombre 1 -> "as "
	| Nombre 2 -> "deux "
	| Nombre 3 -> "trois "
	| Nombre 4 -> "quatre "
	| Nombre 5 -> "cinq "
	| Nombre 6 -> "six "
	| Nombre 7 -> "sept "
	| Nombre 8 -> "huit "
	| Nombre 9 -> "neuf "
	| Nombre 10 -> "dix "
	| Nombre n -> "Unknow "
	| Valet -> "valet "
	| Dame -> "dame "
	| Roi -> "roi "
;;

let string_of_carte (n,c) =
	(string_of_valeur n) ^ (string_of_couleur c)
;; 

(* La famille Simpson *)

type personne = Personne of string * string * personne * personne
				| Inconnu
;;

let person01 = Personne("Abraham","Simpson",Inconnu,Inconnu) ;;
let person02 = Personne("Mona","Olsen",Inconnu,Inconnu) ;;
let person03 = Personne("Jacqueline","Bouvier",Inconnu,Inconnu) ;;
let person04 = Personne("Clancy","Bouvier",Inconnu,Inconnu) ;;
let person05 = Personne("Herbert","Powell",person01,person02) ;;
let person06 = Personne("Homer","Simpson",person01,person02) ;;
let person07 = Personne("Marge","Simpson",person03,person04) ;;
let person08 = Personne("Patty","Bouvier",person03,person04) ;;
let person09 = Personne("Selma","Bouvier",person03,person04) ;;
let person10 = Personne("Bart","Simpson",person06,person07) ;;
let person11 = Personne("Lisa","Simpson",person06,person07) ;;
let person12 = Personne("Maggie","Simpson",person06,person07) ;;
let person13 = Personne("Ling","Bouvier",person09,Inconnu) ;;

let nombre_de_parents_connus person =
		match person with
		| Inconnu -> 0
		| Personne(_,_,Inconnu,Inconnu)-> 0
		| Personne(_,_,Inconnu,_)
		| Personne(_,_,_,Inconnu) -> 1
		| Personne(_,_,_,_) -> 2
;;

nombre_de_parents_connus person01 ;;
nombre_de_parents_connus person13 ;;

let nombre_de_grands_parents_connus person = 
	match person with
		| Inconnu -> 0
		| Personne(_,_,Inconnu,Inconnu)-> 0

		| Personne(_,_,Personne(_,_,Inconnu,Inconnu),Inconnu)
		| Personne(_,_,Inconnu,Personne(_,_,Inconnu,Inconnu)) -> 0

		| Personne(_,_,Inconnu,Personne(_,_,Inconnu,_))
		| Personne(_,_,Inconnu,Personne(_,_,_,Inconnu))
		| Personne(_,_,Personne(_,_,Inconnu,_),Inconnu)
		| Personne(_,_,Personne(_,_,_,Inconnu),Inconnu) -> 1

		| Personne(_,_,Personne(_,_,Inconnu,Inconnu),Personne(_,_,Inconnu,Inconnu))
		| Personne(_,_,Personne(_,_,_,_),Personne(_,_,_,_)) -> 2
		| _ -> -1
;;

let rec nombre_d_ancetres_connus person =
	match person with
		| Personne(_,_,Inconnu,Inconnu) -> 0
		| Personne(_,_,Inconnu,y) -> 1 + nombre_d_ancetres_connus y
		| Personne(_,_,x,Inconnu) -> 1 + nombre_d_ancetres_connus x
		| Personne(_,_,x,y) -> 2 + nombre_d_ancetres_connus x + nombre_d_ancetres_connus y
;;


nombre_d_ancetres_connus person13 ;;