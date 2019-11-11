open CLessType
open Tools
open ASMType

let rec generate_asm_expression varl sp e il =
  try match e with
  (* *) 
  | Const i -> il |% pi "movq %i, %rax" i
  | Set(s,e1) -> (generate_asm_expression varl sp e1 il)
			|% (pa "movq %rax, %a" (List.assoc s varl))
  | Var s -> il |% (pa 
			"movq %a, %rax" 
			(List.assoc s varl)
		    )
  | BOperator(e1, op, e2) -> 
      let il2 = (generate_asm_expression varl sp e1
		  (
		    (generate_asm_expression varl sp e2 il)
		      |% p "pushq %rax"
		  )
		) in  
      (match op with
        | Add -> il2 |% p "addq (%rsp), %rax"
        | Mult -> il2 |% p "imulq (%rsp), %rax"
		| Sub -> il2 |% p "subq (%rsp), %rax"
        | _ -> il )
      |% p "addq $8, %rsp"
  with Match_failure(_) -> raise (Code_gen_failure_expression e)
              
let rec generate_asm_statement varl sp retlbl s il =
  try match s with
  (* *) 
  | Expr(e) -> generate_asm_expression varl sp e il
  | IfStat (e, s1, s2) -> let lbl_else_if = fresh_lbl "else_if" in
			  let lbl_end_if = fresh_lbl "end_if" in
			  (
			    generate_asm_statement varl sp retlbl s2
			      (
				(generate_asm_statement varl sp retlbl s1
				    (
				      (generate_asm_expression varl sp e il)
					|% p "testq %rax, %rax"
					|% p ("jz "^lbl_else_if)
				      )
				  |% p ("jmp "^lbl_end_if)
				  |% p (lbl_else_if^":")
				)
			    )
			    |% p (lbl_end_if^":")
			  )
  | BlockStat(_, []) -> il
  | BlockStat([], s :: t) -> (generate_asm_statement varl sp retlbl (BlockStat([],t))
				(generate_asm_statement varl sp retlbl s il)
			    )
  | BlockStat(v :: t,sl) -> (generate_asm_statement 
						      ((v, (parse_arg "-%i(%rsp)" (sp+8)))::varl)
						      (sp+8)
						      retlbl
						      (BlockStat(t,sl))
						      (il |% p "subq $8, %rsp")
						    )
  
  | ReturnStat Some(e) -> 
      (generate_asm_statement varl sp retlbl (ReturnStat None) 
        (generate_asm_expression varl sp e il)
      )
  | ReturnStat None ->
     (il
	 |% pi "addq %i,%rsp" sp
	 |% p  "popq %rbp"
	 |% p  "retq"
     )
  with Match_failure(_) -> raise (Code_gen_failure_statment s)
       
let generate_asm_top varl il = function
  | FunDec(label,_,statement) -> (generate_asm_statement varl 0 label statement ( il 
                                                      |% p (label^":")
                                                      |% p "pushq %rbp"
                                                      |% p "movq %rsp, %rbp"
                                                    ))
  | VarDec(_) -> il
    (* les variables globals sont déjà geré dans le fichier compilo.ml.
       On ne fait donc rien ici. *)
    
