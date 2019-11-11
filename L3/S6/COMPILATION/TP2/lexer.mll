{
open Parser
exception Eof
}


(* Déclaration du dictionnaire (regexp -> terminal/token) *)

rule anlex = parse
  | [' ' '\t' '\n' '\r']     { anlex lexbuf (* Oubli des espacements et passages à la ligne *) }
  | "/*"                     { coms 1 lexbuf }
  | ['0'-'9']+ as lxm        { INT(int_of_string lxm) }
  | '+'                      { PLUS                   }
  | '*'                      { TIMES                  }
  | '-'                      { MINUS                  }
  | '/'                      { DIV                    }
  | "mod"                    { MOD                    }
  | '('                      { LPAR                   }
  | ')'                      { RPAR                   }
  | "true"                   { TRUE                   }
  | "false"                  { FALSE                  }
  | '='                      { EQUAL                  }
  | "<>"                     { DIF                    }
  | '<'                      { INF                    }
  | "<="                     { INFOREQ                }
  | "not"                    { NOT                    }
  | "and"                    { AND                    }
  | "or"                     { OR                     }
  | ";;"                     { TERM                   }
  | eof                      { raise Eof              }
  | _  as lxm                { (* Pour tout autre caractère : message sur la sortie erreur + oubli *)
                               Printf.eprintf "Unknown character '%c' ignored\n" lxm; flush stderr;
                               anlex lexbuf
                             }

and coms x = parse
  | "/*"  { coms  (x + 1)  lexbuf                                       }
  | "*/"  { match (x-1) with 0 -> (anlex lexbuf) | y ->( coms y lexbuf) }
  | eof   { failwith "Unexpected end of file"                           }
  | _     { (coms  x lexbuf)                                            }

  
