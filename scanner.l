/* $Id: scanner.l,v 1.0 2016-08-18 15:05:42-07 - - $ */

%{
#include "lyutils.h"
#include "auxlib.h"
/*#define YY_USER_ACTION {lexer::advance()*/ //have to change this around
#define  



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

CHAR 		(char)
ELSE 		(else)
IF 			(if)
INT 		(int)
NEW 		(new)
NULL 		(null)
RETURN 		(return)
STRING 		(string)
STRUCT 		(struct)


{CHAR}		{ return yylval_token(TOK_CHAR);}
{ELSE}		{ return yylval_token(TOK_ELSE);}
{IF}		{ return yylval_token(TOK_IF);}
{INT}		{ return yylval_token(TOK_INT);}
{NEW}		{ return yylval_token(TOK_NEW);}
{NULL}		{ return yylval_token(TOK_NULL);}
{RETURN}	{ return yylval_token(TOK_RETURN);}
{STRING}	{ return yylval_token(TOK_STRING);}
{STRUCT}	{ return yylval_token(TOK_STRUCT);}
{VOID}		{ return yylval_token(TOK_VOID);}
{WHILE}		{ return yylval_token(TOK_WHILE);}


"!="		{ return yylval_token(TOK_NE);}
'!"			{ return yylval_token('!'); }
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
"<"			{ return yylval_token('<'); }
"=="		{ return yylval_token(TOK_EQ); }
"="			{ return yylval_token('='); }
">="		{ return yylval_token(TOK_GE); }
">"			{ return yylval_token('>'); }
"["			{ return yylval_token('['); }
"[]"		{ return yylval_token(TOK_ARRAY); }
"]"			{ return yylval_token(']'); }
"{"			{ return yylval_token('{'); }
"}"			{ return yylval_token('}'); }