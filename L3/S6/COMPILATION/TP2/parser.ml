type token =
  | INT of (int)
  | TRUE
  | FALSE
  | EQUAL
  | DIF
  | INF
  | INFOREQ
  | NOT
  | AND
  | OR
  | PLUS
  | MINUS
  | TIMES
  | DIV
  | MOD
  | LPAR
  | RPAR
  | TERM

open Parsing;;
let _ = parse_error;;
# 2 "parser.mly"

open Ast
type axiome = Expr of expr | Cond of cond

let cstCond c = Cond(c)
let cstExpr e = Expr(e)

# 32 "parser.ml"
let yytransl_const = [|
  258 (* TRUE *);
  259 (* FALSE *);
  260 (* EQUAL *);
  261 (* DIF *);
  262 (* INF *);
  263 (* INFOREQ *);
  264 (* NOT *);
  265 (* AND *);
  266 (* OR *);
  267 (* PLUS *);
  268 (* MINUS *);
  269 (* TIMES *);
  270 (* DIV *);
  271 (* MOD *);
  272 (* LPAR *);
  273 (* RPAR *);
  274 (* TERM *);
    0|]

let yytransl_block = [|
  257 (* INT *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\001\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\002\000\002\000\002\000\002\000\
\002\000\002\000\002\000\002\000\000\000"

let yylen = "\002\000\
\002\000\002\000\002\000\001\000\001\000\002\000\003\000\003\000\
\003\000\003\000\003\000\003\000\001\000\003\000\003\000\003\000\
\003\000\003\000\003\000\002\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\013\000\004\000\005\000\000\000\000\000\000\000\
\000\000\021\000\000\000\000\000\000\000\006\000\020\000\000\000\
\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\002\000\000\000\000\000\003\000\014\000\000\000\
\000\000\000\000\000\000\000\000\000\000\017\000\018\000\019\000\
\007\000\008\000"

let yydgoto = "\002\000\
\010\000\013\000\012\000"

let yysindex = "\004\000\
\027\255\000\000\000\000\000\000\000\000\030\255\000\255\000\255\
\027\255\000\000\043\255\249\254\082\255\000\000\000\000\099\255\
\000\000\000\255\000\255\000\255\000\255\000\255\000\255\000\255\
\000\255\000\255\000\000\030\255\030\255\000\000\000\000\106\255\
\106\255\106\255\106\255\090\255\090\255\000\000\000\000\000\000\
\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\042\255\
\063\255\089\255\091\255\058\255\073\255\000\000\000\000\000\000\
\000\000\000\000"

let yygindex = "\000\000\
\001\000\255\255\254\255"

let yytablesize = 121
let yytable = "\011\000\
\003\000\028\000\029\000\014\000\001\000\015\000\016\000\011\000\
\000\000\017\000\030\000\007\000\000\000\000\000\000\000\008\000\
\032\000\033\000\034\000\035\000\036\000\037\000\038\000\039\000\
\040\000\041\000\042\000\003\000\004\000\005\000\003\000\004\000\
\005\000\000\000\006\000\000\000\000\000\006\000\007\000\000\000\
\000\000\007\000\008\000\000\000\009\000\008\000\018\000\019\000\
\020\000\021\000\009\000\009\000\000\000\022\000\023\000\024\000\
\025\000\026\000\000\000\009\000\027\000\015\000\015\000\015\000\
\015\000\000\000\015\000\015\000\015\000\015\000\000\000\010\000\
\010\000\000\000\015\000\015\000\016\000\016\000\016\000\016\000\
\010\000\016\000\016\000\016\000\016\000\018\000\019\000\020\000\
\021\000\016\000\016\000\000\000\022\000\023\000\024\000\025\000\
\026\000\011\000\011\000\012\000\012\000\000\000\024\000\025\000\
\026\000\000\000\011\000\000\000\012\000\022\000\023\000\024\000\
\025\000\026\000\000\000\031\000\022\000\023\000\024\000\025\000\
\026\000"

let yycheck = "\001\000\
\001\001\009\001\010\001\006\000\001\000\007\000\008\000\009\000\
\255\255\009\000\018\001\012\001\255\255\255\255\255\255\016\001\
\018\000\019\000\020\000\021\000\022\000\023\000\024\000\025\000\
\026\000\028\000\029\000\001\001\002\001\003\001\001\001\002\001\
\003\001\255\255\008\001\255\255\255\255\008\001\012\001\255\255\
\255\255\012\001\016\001\255\255\018\001\016\001\004\001\005\001\
\006\001\007\001\009\001\010\001\255\255\011\001\012\001\013\001\
\014\001\015\001\255\255\018\001\018\001\004\001\005\001\006\001\
\007\001\255\255\009\001\010\001\011\001\012\001\255\255\009\001\
\010\001\255\255\017\001\018\001\004\001\005\001\006\001\007\001\
\018\001\009\001\010\001\011\001\012\001\004\001\005\001\006\001\
\007\001\017\001\018\001\255\255\011\001\012\001\013\001\014\001\
\015\001\009\001\010\001\009\001\010\001\255\255\013\001\014\001\
\015\001\255\255\018\001\255\255\018\001\011\001\012\001\013\001\
\014\001\015\001\255\255\017\001\011\001\012\001\013\001\014\001\
\015\001"

let yynames_const = "\
  TRUE\000\
  FALSE\000\
  EQUAL\000\
  DIF\000\
  INF\000\
  INFOREQ\000\
  NOT\000\
  AND\000\
  OR\000\
  PLUS\000\
  MINUS\000\
  TIMES\000\
  DIV\000\
  MOD\000\
  LPAR\000\
  RPAR\000\
  TERM\000\
  "

let yynames_block = "\
  INT\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : axiome) in
    Obj.repr(
# 35 "parser.mly"
                            ( _2 )
# 165 "parser.ml"
               : axiome))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 36 "parser.mly"
                            ( cstExpr _1 )
# 172 "parser.ml"
               : axiome))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'cond) in
    Obj.repr(
# 37 "parser.mly"
                            ( cstCond _1 )
# 179 "parser.ml"
               : axiome))
; (fun __caml_parser_env ->
    Obj.repr(
# 41 "parser.mly"
                                  ( mBool true       )
# 185 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    Obj.repr(
# 42 "parser.mly"
                                  ( mBool false      )
# 191 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'cond) in
    Obj.repr(
# 43 "parser.mly"
                                  ( mNot _2          )
# 198 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'cond) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'cond) in
    Obj.repr(
# 44 "parser.mly"
                                  ( mAnd _1 _3       )
# 206 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'cond) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'cond) in
    Obj.repr(
# 45 "parser.mly"
                                  ( mOr _1 _3        )
# 214 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 46 "parser.mly"
                                  ( eq _1 _3         )
# 222 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 47 "parser.mly"
                                  ( dif _1 _3        )
# 230 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 48 "parser.mly"
                                  ( inf _1 _3        )
# 238 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 49 "parser.mly"
                                  ( inforeq _1 _3    )
# 246 "parser.ml"
               : 'cond))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 53 "parser.mly"
                                  ( cst _1           )
# 253 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 54 "parser.mly"
                                  ( par _2           )
# 260 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 55 "parser.mly"
                                  ( add _1 _3        )
# 268 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 56 "parser.mly"
                                  ( add _1 (neg _3)  )
# 276 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 57 "parser.mly"
                                  ( mul _1 _3        )
# 284 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 58 "parser.mly"
                                  ( div _1 _3        )
# 292 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 59 "parser.mly"
                                  ( mMod _1 _3       )
# 300 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 60 "parser.mly"
                                  ( neg _2           )
# 307 "parser.ml"
               : 'expr))
(* Entry ansyn *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let ansyn (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : axiome)
