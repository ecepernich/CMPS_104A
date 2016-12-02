// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 5: .oil file

// $Id: lyutils.h,v 1.6 2016-10-06 16:13:39-07 - - $

#ifndef __UTILS_H__
#define __UTILS_H__

// Lex and Yacc interface utility.

#include <string>
#include <vector>
using namespace std;

#include <stdio.h>

#include "astree.h"
#include "auxlib.h"

#define YYEOF 0

extern FILE* yyin; //called in main
extern FILE* tokfile; //from main
extern FILE* strfile; //from main
extern char* yytext; 
extern int yy_flex_debug;
extern int yydebug;
extern size_t yyleng; 
#define YYEOF 0

int yylex();
int yylex_destroy();
int yyparse();
void yyerror (const char* message);
int yylval_token(int symbol); //helper funct

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


struct parser {
   static astree* root;
   static const char* get_tname (int symbol);
}; //get_tname used in lyutils.cpp llyval

#define YYSTYPE astree*
#include "yyparse.h"

//also in parser.y
const char *get_yytname (int symbol);
astree* new_parseroot(void);

#endif

