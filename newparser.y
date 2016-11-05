%{
    // Parser for astree project
    //New parser.l
}%



%token TOK_ROOT TOK_IDENT TOK_FIELD TOK_TYPEID
%token TOK_POS TOK_NEG TOK_CALL TOK_NEW
%token TOK_STRUCT TOK_ARRAY TOK_VOID 



%start program

%%
program : program structdef 
    | program function
    | program statement
    | program
    | program error ';' 
    | program error '}'
    ;

%%

structdef: TOK_STRUCT TOK_IDENT '{' '}'
        | TOK_STRUCT TOK_IDENT '{' structrepeat'}'
        ;
         
structrepeat: structrepeat fielddecl ';'
        |fielddecl;
        |
        ;

fielddecl:basetype TOK_IDENT
        |basetype TOK_ARRAY TOK_IDENT
        ;

basetype:TOK_VOID
        |TOK_INT
        |TOK_STRING
        |TOK_IDENT
        ;

function: identdecl '(' ')' block
        | identdecl '(' identdecl ')' block
        | identdecl '(' functionrepeat ')' block
        ;

functionrepeat: frunctionrepeat ',' identdecl 
        | ',' identdecl
        ;

identdecl: basetype TOK_IDENT
        | basetype TOK_ARRAY TOK_IDENT
        :

block: ';'
        |'{' '}'
        |'{' blockrepeat '}'
        ;

blockrepeat: blockrepeat statement
        | statement
        ;






