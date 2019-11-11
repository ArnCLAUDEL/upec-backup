let _ =

  (* Ouverture un flot de caractère ; ici à partir du fichier cmds.txt' stdin  *)  
  let source = Lexing.from_channel (open_in "cmds.txt") in 

  (* Boucle infinie interompue par une exception correspondant à la fin de fichier *)
  let rec f () =
    try
      (* Récupération d'une expression à partir de la source puis affichage de l'évaluation *)
      let e = Parser.ansyn Lexer.anlex source in
      (match e with
      | Parser.Expr(e) -> Printf.printf "%s => %i\n" (Ast.string_of_expr e) (Ast.eval e)
      | Parser.Cond(c) -> Printf.printf "%s => %b\n" (Ast.string_of_cond c) (Ast.eval_cond c));
      flush stdout;
      f ()
    with Lexer.Eof -> Printf.printf "Bye\n"
  in

  f ()

