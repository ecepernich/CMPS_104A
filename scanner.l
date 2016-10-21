/* $Id: scanner.l,v 1.0 2016-08-18 15:05:42-07 - - $ */

%{
#include "lyutils.h"
#include "auxlib.h"
#define YY_USER_ACTION { lexer::advance(); }



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

TOK_CHAR 		(char)
TOK_ELSE 		(else)
TOK_IF 			(if)
TOK_INT 		(int)
TOK_NEW 		(new)
TOK_NULL 		(null)
TOK_RETURN 		(return)
TOK_STRING 		(string)
TOK_STRUCT 		(struct)
 

{TOK_CHAR}		{ return yylval_token(TOK_CHAR);}
{TOK_ELSE}		{ return yylval_token(TOK_ELSE);}
{TOK_IF}		{ return yylval_token(TOK_IF);}
{TOK_INT}		{ return yylval_token(TOK_INT);}
{TOK_NEW}		{ return yylval_token(TOK_NEW);}
{TOK_NULL}		{ return yylval_token(TOK_NULL);}
{TOK_RETURN}	{ return yylval_token(TOK_RETURN);}
{TOK_STRING}	{ return yylval_token(TOK_STRING);}
{TOK_STRUCT}	{ return yylval_token(TOK_STRUCT);}
{TOK_VOID}		{ return yylval_token(TOK_VOID);}
{TOK_WHILE}		{ return yylval_token(TOK_WHILE);}


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