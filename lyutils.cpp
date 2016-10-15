head	1.8;
access;
symbols;
locks;
comment	@// @;


1.8
date	2016.10.06.23.13.39;	author -;	state -;
branches;
next	1.7;

1.7
date	2016.09.28.21.47.31;	author -;	state -;
branches;
next	1.6;

1.6
date	2016.04.07.20.04.52;	author -;	state -;
branches;
next	1.5;

1.5
date	2015.04.10.02.34.17;	author -;	state -;
branches;
next	1.4;

1.4
date	2015.04.10.02.31.47;	author -;	state -;
branches;
next	1.3;

1.3
date	2015.04.10.00.45.26;	author -;	state -;
branches;
next	1.2;

1.2
date	2014.11.17.23.46.47;	author -;	state -;
branches;
next	1.1;

1.1
date	2014.10.04.01.22.05;	author -;	state -;
branches;
next	;


desc
@@


1.8
log
@-
@
text
@// $Id: lyutils.cpp,v 1.7 2016-09-28 14:47:31-07 - - $

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlib.h"
#include "lyutils.h"
#include "yylex.h"

bool lexer::interactive = true;
location lexer::lloc = {0, 1, 0};
size_t lexer::last_yyleng = 0;
vector<string> lexer::filenames;

astree* parser::root = nullptr;

const string* lexer::filename (int filenr) {
   return &lexer::filenames.at(filenr);
}

void lexer::newfilename (const string& filename) {
   lexer::lloc.filenr = lexer::filenames.size();
   lexer::filenames.push_back (filename);
}

void lexer::advance() {
   if (not interactive) {
      if (lexer::lloc.offset == 0) {
         printf (";%2zd.%3zd: ",
                 lexer::lloc.filenr, lexer::lloc.linenr);
      }
      printf ("%s", yytext);
   }
   lexer::lloc.offset += last_yyleng;
   last_yyleng = yyleng;
}

void lexer::newline() {
   ++lexer::lloc.linenr;
   lexer::lloc.offset = 0;
}

void lexer::badchar (unsigned char bad) {
   char buffer[16];
   snprintf (buffer, sizeof buffer,
             isgraph (bad) ? "%c" : "\\%03o", bad);
   errllocprintf (lexer::lloc, "invalid source character (%s)\n",
                  buffer);
}


void lexer::badtoken (char* lexeme) {
   errllocprintf (lexer::lloc, "invalid token (%s)\n", lexeme);
}

void lexer::include() {
   size_t linenr;
   static char filename[0x1000];
   assert (sizeof filename > strlen (yytext));
   int scan_rc = sscanf (yytext, "# %zd \"%[^\"]\"", &linenr, filename);
   if (scan_rc != 2) {
      errprintf ("%s: invalid directive, ignored\n", yytext);
   }else {
      if (yy_flex_debug) {
         fprintf (stderr, "--included # %zd \"%s\"\n",
                  linenr, filename);
      }
      lexer::lloc.linenr = linenr - 1;
      lexer::newfilename (filename);
   }
}

void yyerror (const char* message) {
   assert (not lexer::filenames.empty());
   errllocprintf (lexer::lloc, "%s\n", message);
}

@


1.7
log
@-
@
text
@d1 1
a1 1
// $Id: lyutils.cpp,v 1.1 2016-08-18 14:59:46-07 - - $
d9 1
a9 1
#include "syslib.h"
@


1.6
log
@-
@
text
@d1 1
a1 4

#include <vector>
#include <string>
using namespace std;
d9 1
d11 1
a11 7
#include "auxlib.h"

astree* yyparse_astree = NULL;
int scan_linenr = 1;
int scan_offset = 0;
bool scan_echo = false;
vector<string> included_filenames;
d13 4
a16 3
const string* lexer_filename (int filenr) {
   return &included_filenames.at(filenr);
}
d18 1
a18 3
void lexer_newfilename (const char* filename) {
   included_filenames.push_back (filename);
}
d20 2
a21 3
void lexer_newline (void) {
   ++scan_linenr;
   scan_offset = 0;
d24 3
a26 2
void lexer_setecho (bool echoflag) {
   scan_echo = echoflag;
d29 6
a34 4

void lexer_useraction (void) {
   if (scan_echo) {
      if (scan_offset == 0) printf (";%5d: ", scan_linenr);
d37 2
a38 1
   scan_offset += yyleng;
d41 3
a43 5
void yyerror (const char* message) {
   assert (not included_filenames.empty());
   errprintf ("%:%s: %d: %s\n",
              included_filenames.back().c_str(),
              scan_linenr, message);
d46 6
a51 6
void lexer_badchar (unsigned char bad) {
   char char_rep[16];
   sprintf (char_rep, isgraph (bad) ? "%c" : "\\%03o", bad);
   errprintf ("%:%s: %d: invalid source character (%s)\n",
              included_filenames.back().c_str(),
              scan_linenr, char_rep);
d54 3
a56 4
void lexer_badtoken (char* lexeme) {
   errprintf ("%:%s: %d: invalid token (%s)\n",
              included_filenames.back().c_str(),
              scan_linenr, lexeme);
d59 5
a63 19
int yylval_token (int symbol) {
   int offset = scan_offset - yyleng;
   yylval = new astree (symbol, included_filenames.size() - 1,
                        scan_linenr, offset, yytext);
   return symbol;
}

astree* new_parseroot (void) {
   yyparse_astree = new astree (TOK_ROOT, 0, 0, 0, "");
   return yyparse_astree;
}


void lexer_include (void) {
   lexer_newline();
   char filename[strlen (yytext) + 1];
   int linenr;
   int scan_rc = sscanf (yytext, "# %d \"%[^\"]\"",
                         &linenr, filename);
d65 1
a65 2
      errprintf ("%: %d: [%s]: invalid directive, ignored\n",
                 scan_rc, yytext);
d67 6
a72 5
      printf (";# %d \"%s\"\n", linenr, filename);
      lexer_newfilename (filename);
      scan_linenr = linenr - 1;
      DEBUGF ('m', "filename=%s, scan_linenr=%d\n",
              included_filenames.back().c_str(), scan_linenr);
d74 5
@


1.5
log
@-
@
text
@a98 2
RCSC("$Id: lyutils.cpp,v 1.4 2015-04-09 19:31:47-07 - - $")

@


1.4
log
@-
@
text
@d76 1
a76 1
   yyparse_astree = new astree (ROOT, 0, 0, 0, "");
d99 1
a99 1
RCSC("$Id: lyutils.cpp,v 1.3 2015-04-09 17:45:26-07 - - $")
@


1.3
log
@-
@
text
@d70 1
a70 1
   yylval = new_astree (symbol, included_filenames.size() - 1,
d76 1
a76 1
   yyparse_astree = new_astree (ROOT, 0, 0, 0, "");
d99 1
a99 1
RCSC("$Id: lyutils.cpp,v 1.2 2014-11-17 15:46:47-08 - - $")
@


1.2
log
@-
@
text
@d21 1
a21 1
const string* scanner_filename (int filenr) {
d25 1
a25 1
void scanner_newfilename (const char* filename) {
d29 1
a29 1
void scanner_newline (void) {
d34 1
a34 1
void scanner_setecho (bool echoflag) {
d39 1
a39 1
void scanner_useraction (void) {
d54 1
a54 1
void scanner_badchar (unsigned char bad) {
d62 1
a62 1
void scanner_badtoken (char* lexeme) {
d81 2
a82 2
void scanner_include (void) {
   scanner_newline();
d92 1
a92 1
      scanner_newfilename (filename);
d99 1
a99 1
RCSC("$Id: lyutils.cpp,v 1.1 2014-10-03 18:22:05-07 - - $")
@


1.1
log
@-
@
text
@d76 1
a76 1
   yyparse_astree = new_astree (ROOT, 0, 0, 0, "<<ROOT>>");
d99 1
a99 1
RCSC("$Id: lyutils.cc,v 1.3 2013-10-11 18:56:52-07 - - $")
@
