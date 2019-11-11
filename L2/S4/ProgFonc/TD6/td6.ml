type orientation = Nord | Sud | Est | Ouest ;;
type directive = Avancer | Reculer | Gauche | Droite ;;

let inverse d =
	match d with
	| Avancer -> Reculer
	| Reculer -> Avancer
	| Droite -> Gauche
	| Gauche -> Droite
;;

type path = 
	| Stop
	| Instruction of directive * path
;;

let stop = Stop ;;

let forward p = 
	Instruction(Avancer,p)
;;

let backward p =
	Instruction(Reculer,p)
;;

let left p =
	Instruction(Gauche,p)
;;

let right p =
	Instruction(Droite,p)
;;

let p = forward (forward (left (backward (left (forward stop))))) ;;

let rec string_of_path p =
	match p with
	| Stop -> " "
	| Instruction(Avancer,reste) -> " ; Avancer d'un pas" ^ string_of_path reste
	| Instruction(Reculer,reste) -> " ; Reculer d'un pas" ^ string_of_path reste
	| Instruction(Gauche,reste) -> " ; Tourner a gauche" ^ string_of_path reste
	| Instruction(Droite,reste) -> " ; Tourner a droite" ^ string_of_path reste
;;

string_of_path p ;;

let rec number_of_steps p =
	match p with
	| Stop -> 0
	| Instruction(Avancer,reste) -> 1 + number_of_steps reste
	| Instruction(Reculer,reste) -> 1 + number_of_steps reste
	| Instruction(Gauche,reste) -> 0 + number_of_steps reste
	| Instruction(Droite,reste) -> 0 + number_of_steps reste
;;

number_of_steps p ;;

(*
let rec simplify p =
	match p with
	| Stop -> p
	| Instruction(i,reste1) ->	match reste1 with
								| Stop -> p
								| Instruction(invI,reste2) -> simplify reste2
								| Instruction(other,_) -> simplify reste1
;;
*)

type hunter = Hunter of int * int * float * orientation ;;

let move h d =
	match h with
	| Hunter(x,y,t,o) -> match d with
							| Avancer -> match o with
										| Nord -> Hunter(x,y+1,t,o)
										| Sud -> Hunter(x,y-1,t,o)
										| Est -> Hunter(x-1,y,t,o)
										| Ouest -> Hunter(x+1,y,t,o)
							| Reculer -> match o with 			
										| Nord -> Hunter(x,y-1,t,o)
										| Sud -> Hunter(x,y+1,t,o)
										| Est -> Hunter(x+1,y,t,o)
										| Ouest -> Hunter(x-1,y,t,o)
							| Droite -> match o with 			
										| Nord -> Hunter(x+1,y,t,o)
										| Sud -> Hunter(x-1,y,t,o)
										| Est -> Hunter(x,y+1,t,o)
										| Ouest -> Hunter(x,y-1,t,o)
							| Gauche -> match o with 			
										| Nord -> Hunter(x-1,y,t,o)
										| Sud -> Hunter(x+1,y,t,o)
										| Est -> Hunter(x,y-1,t,o)
										| Ouest -> Hunter(x,y+1,t,o)
;;

