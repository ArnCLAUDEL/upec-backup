(* Coordonnées et transformations *)

type coord = Coord of float * float ;;

let string_of_coord c =
	match c with
		|Coord(x,y) -> "("^string_of_float x^","^string_of_float y^")"
;;

let coord1 = Coord(2.,3.) ;;
string_of_coord coord1 ;;

let coordinate x y =
	Coord(x,y)
;;

let translate_pt p v s =
	match p with
		|Coord(x1,y1) ->match v with
							| Coord(x2,y2) -> Coord(x1+.s*.x2,y1+.s*.y2)
;;

let translate_point p v =
		translate_pt p v 1.
;;

let inv_translate_point p v =
	translate_pt p v (-.(1.))
;;

let vect1 = Coord(1.,1.) ;;

translate_point coord1 vect1 ;;
inv_translate_point coord1 vect1 ;;

let rotate_pt p t s =
	match p with
	| Coord(x1,y1) -> Coord(( x1*.s*.cos t )-.( y1*.s*.sin t ),( x1*.s*.sin t )+.( y1*.s*.cos t ))
;;

let rotate_point p t =
	rotate_pt p t 1.
;;

let inv_rotate_point p t =
	rotate_pt p t (-.(1.))
;;

"-----------------" ;;
"(* Test *)" ;;
"-----------------" ;;

let pi = 4. *. atan 1. ;;
let pi_2 = pi /. 2. ;;
let pi_4 = pi /. 4. ;;
 
let pt = coordinate 10. 20. ;;
 
string_of_coord pt ;;
string_of_coord (inv_translate_point pt pt) ;;
string_of_coord (inv_rotate_point pt pi_2) ;;
string_of_coord (inv_rotate_point pt (-.pi_4)) ;;

"-----------------" ;;
"(* Figures *)" ;;
"-----------------" ;;

type fig_spec = Cercle of float | Rectangle of float * float | Ligne of float ;; 

type figure = Figure of char * coord * float * fig_spec ;;

let circle r =
	Figure('+',Coord(0.,0.),0.,Cercle(r))
;;

let rectangle w h =
	Figure('+',Coord(0.,0.),0.,Rectangle(w,h))
;;

let line l =
	Figure('+',Coord(0.,0.),0.,Ligne(l))
;;

let color_figure f c =
	match f with
	| Figure(a,b1,c1,d1) -> Figure(c,b1,c1,d1)
;;

let translate_figure f dx dy =
	let dv = Coord(dx,dy) in
	match f with
	| Figure(a,b,c,d) -> Figure(a,translate_point b dv,c,d)
;;

let rotate_figure f dt =
	match f with
	| Figure(a,b,c,d) -> Figure(a,b,dt,d)
;;


let intersect_figure p f grain =
	match f with
	| Figure(a,b,c,d) -> 
		let p = inv_translate_point p b in
			let p = rotate_point p c in
				 match p with
				  | Coord(x,y) -> match d with
								  | Cercle(r) -> if( x*.x +. y*.y <= r*.r ) 
								  					then Some a
								  					else None
								  |Rectangle(w,h) -> if( abs_float(x) <= w/.2. && abs_float(y) <= h/.2.)
								  					then Some a
								  					else None
								  |Ligne(l) -> if(abs_float(x) <= l/.2. && abs_float(x) <= grain)	
								 				then Some a
								 				else None				
;;
"-----------------" ;;
"(* Test pour figures *)";;
"-----------------" ;;
let f = rectangle 10. 7. ;;
let f = translate_figure f 10. 8. ;;
let f = rotate_figure f (45. *. pi /. 180.) ;;
intersect_figure (coordinate 5. 5.) f 1. ;;
intersect_figure (coordinate 10. 10.) f 1. ;;
intersect_figure (coordinate 18. 18.) f 1. ;;
 
let f = circle 12. ;;
let f = translate_figure f 20. 13. ;;
let f = color_figure f 'O' ;;
intersect_figure (coordinate 5. 5.) f 1. ;;
intersect_figure (coordinate 10. 10.) f 1. ;;
intersect_figure (coordinate 18. 18.) f 1. ;;
 
let f = line 20. ;;
let f = translate_figure f 18. 18. ;;
let f = rotate_figure f (-60. *. pi /. 180.) ;;
let f = color_figure f '*' ;;
intersect_figure (coordinate 5. 5.) f 1. ;;
intersect_figure (coordinate 10. 10.) f 1. ;;
intersect_figure (coordinate 18. 18.) f 1. ;;

"-----------------" ;;
"(* Images *)" ;;
"-----------------" ;;

type image = Image of int * int * float * figure list ;;

let image w h grain =
	Image(w,h,grain,[])
;;

let append img f =
	match img with
	| Image(w,h,grain,l) -> Image(w,h,grain,f :: l)
;;


let rec intersect_figures grain p l =
	match l with
	| Image(w,h,grain,[]) -> None
	| Image(w,h,g,f :: l') -> if( (intersect_figure p f grain) = None)
									then intersect_figures grain p (Image(w,h,g,l'))
								else match f with
								| Figure(color,_,_,_) -> Some color

								

;;

let string_of_image img =
 	
 	let rec fori i =
	 	match img with
	 	| Image(w,h,grain,l) -> if(i <= h) then
	 		let rec forj j =
		 		match img with
		 		| Image(w,h,grain,l) -> if(j <= w) then
		 			let c = Coord(float_of_int i,float_of_int j) in
		 				match img with
		 				| Image(w,h,grain,l)-> match intersect_figures grain c img with
			 									|None -> " "
			 									|Some c -> ""^c
			 	forj (j+1)
			 else " "
			 	fori (i+1)
		else " "
		in 
 	match img with
 	| Image(w,h,grain,l) -> fori h
;;

