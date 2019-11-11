open CLessType
open Tools
open ASMType

let rec generate_asm_expression varl sp e il =
  try match e with
  (* *) 
  | Const i -> il |% [%asm "movq %i, %rax" i ]
  with Match_failure(_) -> raise (Code_gen_failure_expression e)
              
let rec generate_asm_statement varl sp retlbl s il =
  try match s with
  (* *) 
  | ReturnStat None ->
     (il
	 |% [%asm "addq %i,%rsp" sp]
	 |% [%asm "popq %rbp"]
	 |% [%asm "retq"]
     )
  with Match_failure(_) -> raise (Code_gen_failure_statment s)
       
let generate_asm_top varl il = function
  | FunDec(_) -> (* *) failwith("TO DO")
  | VarDec(_) -> il
    (* les variables globals sont déjà geré dans le fichier compilo.ml.
       On ne fait donc rien ici. *)
    
