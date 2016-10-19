/* $Id: scanner.l,v 1.0 2016-08-18 15:05:42-07 - - $ */
%{
#include "lyutils.h"
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