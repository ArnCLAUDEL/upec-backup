%{

open Ast
type axiome = Expr of expr | Cond of cond

let cstCond c = Cond(c)
let cstExpr e = Expr(e)

%}

/* Déclaration des terminaux */
%token <int> INT
%token TRUE FALSE
%token EQUAL DIF INF INFOREQ NOT AND OR
%token PLUS MINUS TIMES DIV MOD 
%token LPAR RPAR
%token TERM

/* Précédences (priorité + associativité) des terminaux */
%left AND OR
%nonassoc EQUAL DIF INF INFOREQ
%left PLUS MINUS
%left TIMES DIV MOD
%nonassoc UMINUS NOT

/* Déclaration du non-terminal axiome (ici, ansyn) et du type de son attribut */
%type <axiome> ansyn
%start ansyn

%%

/* Déclaration de la grammaire avec les actions sémantiques */

ansyn:
  | TERM ansyn              { $2 }
  | expr TERM               { cstExpr $1 }
  | cond TERM               { cstCond $1 }
;

cond:
  | TRUE                          { mBool true       }  
  | FALSE                         { mBool false      }  
  | NOT cond                      { mNot $2          }  
  | cond AND cond                 { mAnd $1 $3       }
  | cond OR cond                  { mOr $1 $3        }
  | expr EQUAL expr               { eq $1 $3         }
  | expr DIF expr                 { dif $1 $3        }
  | expr INF expr                 { inf $1 $3        }
  | expr INFOREQ expr             { inforeq $1 $3    }
;

expr:
  | INT                           { cst $1           }
  | LPAR expr RPAR                { par $2           }
  | expr PLUS expr                { add $1 $3        }
  | expr MINUS expr               { add $1 (neg $3)  }
  | expr TIMES expr               { mul $1 $3        }
  | expr DIV expr                 { div $1 $3        }
  | expr MOD expr                 { mMod $1 $3       }
  | MINUS expr %prec UMINUS       { neg $2           }
;
