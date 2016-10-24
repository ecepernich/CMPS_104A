// $Id: lyutils.h,v 1.6 2016-10-06 16:13:39-07 - - $

#ifndef __UTILS_H__
#define __UTILS_H__

// Lex and Yacc interface utility.

#include <string>
#include <vector>
using namespace std;

#include <stdio.h>

#include "astree.h"
#include "string_set.h"
#include "yyparse.h"
#define YYSTYPE astree*
#include "yyparse.h"


#define YYEOF 0

extern int yy_flex_debug;
extern int yydebug;

extern FILE* yyin;     //main.cpp files
extern FILE* strfile;
extern FILE* tokfile;
extern char* yytext;   //lex info
extern int yyleng;
//extern astree* ast;

int yylex(void);
int yylex_destroy (void);
int yyparse();
void yyerror (const char* message);

struct lexer {
   static bool interactive;
   static location lloc;
   static size_t last_yyleng;
   static vector<string> filenames;
   static const string* filename (int filenr);
   static void newfilename (const string& filename);
   static void advance();
   static void newline();
   static void badchar (unsigned char bad);
   static void badtoken (char* lexeme);
   static void include();
};

int yylval_token();

struct parser {
   static astree::astree* root;
   static const char* get_tname (int symbol);
};

#endif

