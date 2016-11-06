%{
    // Elizabeth Cepernich
    // Leah Langford
    // CMPS 104A Fall 2016
    // November 7, 2016

    #include "astree.h"
    #include "lyutils.h"
}%

//things from flex go here? 
%
%
%
%
%
%

%token TOK_ROOT TOK_IDENT TOK_FIELD TOK_TYPEID
%token TOK_POS TOK_NEG TOK_CALL TOK_NEW
%token TOK_STRUCT TOK_ARRAY TOK_VOID 



//precedences (delete this line, comments don't work)
%right TOK_IF TOK_ELSE
%right '='
%left TOK_EQ TOK_NE TOK_GT TOK_LT TOK_GE TOK_LE
%left '+' '-'
%left '*' '/' '%'
%right TOK_POS TOK_NEG '!' TOK_NEW
%left TOK_ARRAY TOK_FIELD TOK_FUNCTION


%start program

%%
program       : program structdef 
              | program function
              | program statement
              | program error ';' 
              | program error '}'
              |
              ;

structdef     : TOK_STRUCT TOK_IDENT '{' '}'
              | TOK_STRUCT TOK_IDENT '{' structrepeat '}'
              ;
         
structrepeat  : structrepeat fielddecl ';'
              | fielddecl ';'
              |
              ;

fielddecl     : basetype TOK_IDENT
              | basetype TOK_ARRAY TOK_IDENT
              ;

basetype      : TOK_VOID
              | TOK_INT
              | TOK_STRING
              | TOK_IDENT
              ;

function      : identdecl '(' ')' block
              | identdecl '(' identdecl ')' block
              | identdecl '(' functionrepeat ')' block
              ;

functionrepeat : frunctionrepeat ',' identdecl 
               | identdecl
               ;

identdecl      : basetype TOK_IDENT
               | basetype TOK_ARRAY TOK_IDENT
               ;

block          : ';'
               |'{' '}'
               |'{' blockrepeat '}'
               ;

blockrepeat    : blockrepeat statement
               | statement
               ;

statement      : block
               | vardecl
               | while
               | ifelse
               | return
               | expr ';'
               ;

vardecl        : identdecl '=' expr ';'
               ;

while          : TOK_WHILE '('expr ')' statement
               ;

ifesle         : TOK_IF '(' expr ')' statement
               | TOK_IF '(' expr ')' statement TOK_ELSE statement
               ;

return         : TOK_RETURN ';'
               | TOK_RETURN expr ';'
               ;

expr           : binoperation
               | unoperation
               | allocator
               | call
               | '(' expr ')'
               | variable
               | constant
               ;

binoperation   : expr '+' expr
               | expr '-' expr
               | expr '*' expr
               | expr '/' expr
               | expr '%' expr
               | expr '=' expr
               | expr TOK_EQ expr
               | expr TOK_NE expr
               | expr TOK_GT expr
               | expr TOK_LT expr
               | expr TOK_GE expr
               | expr TOK_LE expr
               ;

unoperation    : '+' expr
               | '-' expr
               | '!' expr
               | TOK_NEW expr
            
allocator      : TOK_NEW TOK_IDENT '(' ')'
               | TOK_NEW TOK_STRING '(' ')'
               | TOK_NEW basetype '[' expr ']'
               ;

call           : TOK_IDENT '(' ')'
               | TOK_IDENT '(' expr ')'
               | TOK_IDENT '(' callrepeat ')'

callrepeat     : callrepeat ',' expr
               | expr
               ;

variable       : TOK_IDENT
               | expr '[' expr ']'
               | expr '.' TOK_IDENT
               ;

constant       : TOK_INT
               | TOK_CHAR
               | TOK_STRING
               | TOK_NULL
               ;


