let distance_squared x1 y1 x2 y2 =
  let dx = x2 - x1 in
  let dy = y2 - y1 in
    ( + ) (( * ) dx dx) (( * ) dy dy)
;;

let distance_squared_float x1 y1 x2 y2 =
  let dx = x2 -. x1 in
  let dy = y2 -. y1 in
    ( +. ) (( *. ) dx dx) (( *. ) dy dy)
;;

distance_squared 2 2 1 3  ;;

let distance x1 y1 x2 y2 =
    sqrt (float_of_int (distance_squared x1 y1 x2 y2))
;;

let distance_float x1 y1 x2 y2 =
    sqrt (distance_squared_float x1 y1 x2 y2)
;;

distance 2 2 1 3 ;;

let vector_norm =
  fun x -> 
  fun y ->
    distance 0 0 x y
;;

let vector_norm_float =
  fun x -> 
  fun y ->
    distance_float 0. 0. x y
;;
