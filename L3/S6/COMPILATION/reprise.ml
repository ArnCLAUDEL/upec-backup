let distance_squared x1 x2 y1 y2 =
	let dx = x2 - x1 in
	let dy = y2 - y1 in
	dx * dx + dy * dy
;;

let distance x1 y1 x2 y2 =
	sqrt (float_of_int (distance_squared x1 x2 y1 y2) )
;;

let vector_norm x =
x
	fun y -> 
    distance 0 0 x y
;;

