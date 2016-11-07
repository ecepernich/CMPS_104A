%{
    // Elizabeth Cepernich
    // Leah Langford
    // CMPS 104A Fall 2016
    // November 7, 2016

    #include "astree.h"
    #include "lyutils.h"
}%

%debug
%defines
%error-verbose
%token-table
%verbose


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
%left TOK_ARRAY TOK_FIELD TOK_FUNCTION '.' '['
// () is highest but has no associativity???


%start start

%%
start         : program              { parse::root=$1; }
              ;

program       : program structdef    { $$ = $1->adopt($2); }
              | program function     { $$ = $1->adopt($2); }
              | program statement    { $$ = $1->adopt($2); }
              | program error ';'    { $$ = $1; }
              | program error '}'    { $$ = $1; }
              |                      { $$ = new::parseroot() }
              ;

structdef     : TOK_STRUCT TOK_IDENT '{' '}'               { $2->convert(TOK_TYPEID);
                                                             $$ = $1->adopt($2);
                                                             destroy($3);
                                                             destroy($4); }
              | TOK_STRUCT TOK_IDENT '{' structrepeat '}'  { $2->convert(TOK_TYPEID);
                                                             $$ = $1->adopt($2,$4);
                                                             destroy($3, $5); }
              ;
         
structrepeat  : structrepeat fielddecl ';'    { $$ = $1->adopt($2); }   
              | fielddecl ';'                 { $$ = $1; }
              ;

fielddecl     : basetype TOK_IDENT              { $$ = $1->adopt_sym($2, TOK_FIELD); }
              | basetype TOK_ARRAY TOK_IDENT    { $$ = $2->adopt_sym($1, TOK_FIELD); }
              ;

basetype      : TOK_VOID          { $$ = $1; }
              | TOK_INT           { $$ = $1; }
              | TOK_STRING        { $$ = $1; }
              | TOK_TYPEID        { $$ = $1; }
              | TOK_IDENT         { $$ = $1; }
              ;

function      : identdecl '(' ')' block                  {$2->convert(TOK_PARAM);
                                                           $$ =$2;}
              | identdecl '(' identdecl ')' block        {$2->convert(TOK_PARAM);
                                                          $$=$2;}
              | identdecl '(' functionrepeat ')' block   {$2->convert(TOK_PARAM);
                                                         {$$=$2;}}
              ;

functionrepeat : frunctionrepeat ',' identdecl           {$$=$1->adopt($3);
                                                          destroy($2);}
               | identdecl                               {$$=$1;}
               ;

identdecl      : basetype TOK_IDENT               { $2->convert(TOK_DECLID); 
                                                    $$ = $1->adopt($2); }
               | basetype TOK_ARRAY TOK_IDENT     { $3->convert(TOK_DECLID); 
                                                    $$ = $2->adopt($1, $3); }
               ;

block          : ';'                  { $$ = $1->convert($TOK_BLOCK); }
               |'{' '}'               { destroy($2); 
                                        $$ = $1->convert(TOK_BLOCK); }
               |'{' blockrepeat '}'   { destroy($3);
                                        $1->convert(TOK_BLOCK);
                                        $$=$1->adopt($2); }
               ;

blockrepeat    : blockrepeat statement   { $$ = $1->adopt($2); }
               | statement               { $$ = $1; }
               ;

statement      : block           { $$ = $1; }
               | vardecl         { $$ = $1; }
               | while           { $$ = $1; }
               | ifelse          { $$ = $1; }
               | return          { $$ = $1; }
               | expr ';'        { $$ = $1; 
                                   destroy($2); }
               ;

vardecl        : identdecl '=' expr ';'    { destroy($4);
                                             $2->convert(TOK_VARDECL);
                                             $$ = $2->adopt($1, $3); }
               ;

while          : TOK_WHILE '('expr ')' statement    { $$ = $1->adopt($3, $5); 
                                                      destroy($2, $4); }
               ;

ifelse         : TOK_IF '(' expr ')' statement { $1->adopt($3, $5);
                                                 destroy($2, $4); }
               | TOK_IF '(' expr ')' statement TOK_ELSE statement { 
                       convert($1, TOK_IFELSE);
                       $$ = $1->adopt($3, $5, $7);
                       destroy($2,$4);
                       destroy($6); }
               ;

return         : TOK_RETURN ';'          { convert($1, TOK_RETURNVOID);
                                           $$ = $1; }
               | TOK_RETURN expr ';'     { $1->adopt($2);
                                           $$ = $1; }
               ;

expr           : binoperation       { $$ = $1; }
               | unoperation        { $$ = $1; }
               | allocator          { $$ = $1; }
               | call               { $$ = $1; }
               | '(' expr ')'       { $$ = $2;
                                      destroy($1, $3); }
               | variable           { $$ = $1; }
               | constant           { $$ = $1; }
               ;

binoperation   : expr '+' expr        { $$ = $2->adopt($1, $3); }
               | expr '-' expr        { $$ = $2->adopt($1, $3); }
               | expr '*' expr        { $$ = $2->adopt($1, $3); }
               | expr '/' expr        { $$ = $2->adopt($1, $3); }
               | expr '%' expr        { $$ = $2->adopt($1, $3); }
               | expr '=' expr        { $$ = $2->adopt($1, $3); }
               | expr TOK_EQ expr     { $$ = $2->adopt($1, $3); }
               | expr TOK_NE expr     { $$ = $2->adopt($1, $3); }
               | expr TOK_GT expr     { $$ = $2->adopt($1, $3); }
               | expr TOK_LT expr     { $$ = $2->adopt($1, $3); } 
               | expr TOK_GE expr     { $$ = $2->adopt($1, $3); }
               | expr TOK_LE expr     { $$ = $2->adopt($1, $3); }
               ;

unoperation    : '+' expr             { $1->convert(TOK_POS); 
                                        $$ = $1->adopt($2); }
               | '-' expr             { $1->convert(TOK_NEG); 
                                        $$ = $1->adopt($2); }
               | '!' expr             { $$ = $1->adopt($2); }
               | TOK_NEW expr         { $$ = $1->adopt($2); }
            
allocator      : TOK_NEW TOK_IDENT '(' ')'        { $2->convert(TOK_TYPEID); 
                                                    $$ = $1->adopt($2); }
               | TOK_NEW TOK_STRING '(' expr ')'  { $4->convert(TOK_NEWSTRING); 
                                                    $$ = $1->adopt($2, $4); 
                                                    destroy($3, $5); }
               | TOK_NEW basetype '[' expr ']'    { $4->convert(TOK_NEWARRAY); 
                                                    $$ = $1->adopt($2, $4); 
                                                    destroy($3, $5); }
               ;

call           : TOK_IDENT '(' ')'             { $2->convert(TOK_VOID); 
                                                 destroy($3);
                                                 $$ = $1->adopt($2); }
               | TOK_IDENT '(' callrepeat ')'  { $2->convert(TOK_CALL);
                                                 destroy($4);
                                                 $$ = $2->adopt($1, $3); }
               ;

callrepeat     : callrepeat ',' expr        { $$ = $1->adopt($2); 
                                              destroy($3); }
               | expr                       { $$ = $1; }
               ;

variable       : TOK_IDENT                { $$ = $1; }
               | expr '[' expr ']'        { $2->convert(TOK_INDEX); 
                                            $$ = $2->adopt($1, $3); }
               | expr '.' TOK_IDENT       { $3->convert(TOK_FIELD); 
                                            $$ = $2->adopt($1, $3); }
               ;

constant       : TOK_INT        { $$ = $1; }
               | TOK_CHAR       { $$ = $1; }
               | TOK_STRING     { $$ = $1; }
               | TOK_NULL       { $$ = $1; }
               ;


