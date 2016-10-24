%{

#include "lyutils.h"
#include "auxlib.h"
#define YY_USER_ACTION { lexer::useraction(); }

%}


%option 8bit
%option debug
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option warn
%option verbose


LETTER    [A-Za-z]
DIGIT     [0-9]
IDENT     ({LETTER}({LETTER}|{DIGIT})*)
CHAR      ('([^\\'\n]|\\[\\'"0nt])')
STRING    (\"([^\\"\n]|\\[\\'"0nt])*\")
NUMBER    ({DIGIT}+)

NOTIDENT     ({DIGIT}({LETTER}|{DIGIT})*)
BADCHAR      ('([^\\'\n]|\\.)'?) 
BADSTRING    (\"([^\\"\n]|\\.)*(\")?)

%%

"char"    { return yylval_token(TOK_CHAR);}
"else"    { return yylval_token(TOK_ELSE);}
"if"      { return yylval_token(TOK_IF);}
"int"     { return yylval_token(TOK_INT);}
"new"     { return yylval_token(TOK_NEW);}
"null"    { return yylval_token(TOK_NULL);}
"return"  { return yylval_token(TOK_RETURN);}
"string"  { return yylval_token(TOK_STRING);}
"struct"  { return yylval_token(TOK_STRUCT);}
"void"    { return yylval_token(TOK_VOID);}
"while"   { return yylval_token(TOK_WHILE);}


"!="    { return yylval_token(TOK_NE);}
"!"    { return yylval_token('!'); }
"%"    { return yylval_token('%'); }
"("    { return yylval_token('('); }
")"    { return yylval_token(')'); }
"*"    { return yylval_token('*'); }
"+"    { return yylval_token('+'); }
","    { return yylval_token(','); }
"-"    { return yylval_token('-'); }
"."    { return yylval_token('.'); }
"/"    { return yylval_token('/'); }
";"    { return yylval_token(';'); }
"<="    { return yylval_token(TOK_LE); }
"<"    { return yylval_token(TOK_LT); }
"=="    { return yylval_token(TOK_EQ); }
"="    { return yylval_token('='); }
">="    { return yylval_token(TOK_GE); }
">"    { return yylval_token(TOK_GT); }
"["    { return yylval_token('['); }
"[]"    { return yylval_token(TOK_ARRAY); }
"]"    { return yylval_token(']'); }
"{"    { return yylval_token('{'); }
"}"    { return yylval_token('}'); }

"#".*    { scanner_include(); }
[\t]+    {  }
\n       { scanner_newline(); }


{IDENT}    { return yylval_token(TOK_IDENT); }
{NUMBER}    { return yylval_token(TOK_INTCON); }
{CHAR}    { return yylval_token(TOK_CHARCON); }
{STRING}    { return yylval_token(TOK_STRINGCON); }

{NOTIDENT}    { lexer::badtoken(yytext); }
{BADCHAR}     { lexer::badtoken(yytext); } 
{BADSTRING}   { lexer::badtoken(yytext); }
.             { lexer::badchar(*yytext); }

%%
