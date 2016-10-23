/* $Id: scanner.l,v 1.0 2016-08-18 15:05:42-07 - - $ */

%{

#include "lyutils.h"
#include "auxlib.h"
#define YY_USER_ACTION { lexer::advance(); }
#define IGNORE {} /*ask about this */

%}


%option 8bit
%option debug
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option warn
%option verbose


LETTER		[A-Za-z]
DIGIT 		[0-9]
IDENT		({LETTER}({LETTER}|{DIGIT})*)
CHAR 		(’([^\\’\n]|\\[\\’"0nt])’)
STRING 		(\"([^\\"\n]|\\[\\’"0nt])*\")
NUMBER 		({DIGIT}+)

NOTIDENT	
BADCHAR		
BADSTRING 

%%

"#".*		{ scanner_include(); }
[\t]+		{ IGNORE (white space) }
\n 			{ scanner_newline(); }


char		{ return yylval_token(TOK_CHAR);}
else		{ return yylval_token(TOK_ELSE);}
if			{ return yylval_token(TOK_IF);}
int			{ return yylval_token(TOK_INT);}
new			{ return yylval_token(TOK_NEW);}
null		{ return yylval_token(TOK_NULL);}
return		{ return yylval_token(TOK_RETURN);}
string		{ return yylval_token(TOK_STRING);}
struct		{ return yylval_token(TOK_STRUCT);}
void		{ return yylval_token(TOK_VOID);}
while		{ return yylval_token(TOK_WHILE);}


"!="		{ return yylval_token(TOK_NE);}
"!"			{ return yylval_token('!'); }
"%"			{ return yylval_token('%'); }
"("			{ return yylval_token('('); }
")"			{ return yylval_token(')'); }
"*"			{ return yylval_token('*'); }
"+"			{ return yylval_token('+'); }
","			{ return yylval_token(','); }
"-"			{ return yylval_token('-'); }
"."			{ return yylval_token('.'); }
"/"			{ return yylval_token('/'); }
";"			{ return yylval_token(';'); }
"<="		{ return yylval_token(TOK_LE); }
"<"			{ return yylval_token(TOK_LT); }
"=="		{ return yylval_token(TOK_EQ); }
"="			{ return yylval_token('='); }
">="		{ return yylval_token(TOK_GE); }
">"			{ return yylval_token(TOK_GT); }
"["			{ return yylval_token('['); }
"[]"		{ return yylval_token(TOK_ARRAY); }
"]"			{ return yylval_token(']'); }
"{"			{ return yylval_token('{'); }
"}"			{ return yylval_token('}'); }


{IDENT}		{ return yylval_token(TOK_IDENT); }
{NUMBER}	{ return yylval_token(TOK_INTCON); }
{CHAR}		{ return yylval_token(TOK_CHARCON); }
{STRING}	{ return yylval_token(TOK_STRINGCON); }

{NOTIDENT}	{ lexer::badtoken(yytext);
              return yylval_token(TOK_IDENT); }
{BADCHAR}	{ lexer::badtoken(yytext);
              return yylval_token(TOK_CHARCON); }
{BADSTRING}	{ lexer::badtoken(yytext);
              return yylval_token(TOK_STRINGCON); }
.			{ lexer::badchar(yytext);		//ask about this too
			  return yylval_token('.'); }

%%
