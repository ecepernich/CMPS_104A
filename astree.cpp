// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 3: .ast file

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "string_set.h"
#include "lyutils.h"

astree::astree (int symbol_, const location& lloc_, const char* info) {
   symbol = symbol_;
   lloc = lloc_;
   lexinfo = string_set::intern (info);
   // vector defaults to empty -- no children
   attr=0;
   block_nr=0;
}

astree::~astree() {
   while (not children.empty()) {
      astree* child = children.back();
      children.pop_back();
      delete child;
   }
   if (yydebug) {
      fprintf (stderr, "Deleting astree (");
      astree::dump (stderr, this);
      fprintf (stderr, ")\n");
   }
}

astree* astree::adopt (astree* child1, astree* child2, astree* child3) {
   if (child1 != nullptr) children.push_back (child1);
   if (child2 != nullptr) children.push_back (child2);
   if (child3 != nullptr) children.push_back (child3);
   return this;
}

astree* astree::adopt_sym(astree* child, int symbol_) {
   symbol = symbol_;
   return adopt (child);
}


void astree::dump_node (FILE* outfile) {
   fprintf (outfile, "%p->{%s %zd.%zd.%zd \"%s\":",
            this, parser::get_tname (symbol),
            lloc.filenr, lloc.linenr, lloc.offset,
            lexinfo->c_str());
   for (size_t child = 0; child < children.size(); ++child) {
      fprintf (outfile, " %p", children.at(child));
   }
}

void astree::dump_tree (FILE* outfile, astree* tree, int depth) {
  
   astree::print(outfile, tree, depth);
   fprintf (outfile, "\n");
   fflush (NULL);
}


void astree::dump (FILE* outfile, astree* tree) {
   if (tree == nullptr) fprintf (outfile, "nullptr");
                   else tree->dump_tree(outfile, tree, 0);
}

void astree::print (FILE* outfile, astree* tree, int depth) {
   //fprintf (outfile, "|   %*s", depth * 2, "");
   for (int i=0;i<depth;i++)
   {
      fprintf(outfile, "|   ");
   } 
   fprintf (outfile, "%s \"%s\" (%zd.%zd.%zd) ",
            parser::get_tname (tree->symbol), tree->lexinfo->c_str(),
            tree->lloc.filenr, tree->lloc.linenr, tree->lloc.offset);
   print_attr(tree, outfile);
   fprintf("\n");
   for (astree* child: tree->children) {
      astree::print (outfile, child, depth + 1);
   }
}

void print_attr(astree* node, FILE* outfile)
{
   if(node->attr[attr_void])     fprintf(outfile, "void ");
   if(node->attr[attr_int])      fprintf(outfile, "int ");
   if(node->attr[attr_null])     fprintf(outfile, "null ");
   if(node->attr[attr_string])   fprintf(outfile, "string ");
   if(node->attr[attr_struct])   fprintf(outfile, "struct ");
   if(node->attr[attr_array])    fprintf(outfile, "array ");
   if(node->attr[attr_function]) fprintf(outfile, "function ");
   if(node->attr[attr_variable]) fprintf(outfile, "variable ");
   if(node->attr[attr_field])    fprintf(outfile, "field ");
   if(node->attr[attr_typeid])   fprintf(outfile, "typeid ");
   if(node->attr[attr_param])    fprintf(outfile, "param ");
   if(node->attr[attr_lval])     fprintf(outfile, "lval ");
   if(node->attr[attr_const])    fprintf(outfile, "const ");
   if(node->attr[attr_vreg])     fprintf(outfile, "vreg ");
   if(node->attr[attr_vaddr])    fprintf(outfile, "vaddr ");
   if(node->attr_bitset_size)    fprintf(outfile, "bitset_size ");
}


astree* makefunction(astree* identdecl, astree* paramlist, astree* block)
{
   astree* f=new astree(TOK_FUNCTION, identdecl->lloc,"");
   return f->adopt(identdect, paramlist, block);
}

astree* makeprototype(astree* identdecl, astree* paramlist)
{
   astree* f=new astree(TOK_PROTOTYPE, identdecl->lloc,"");
   return f->adopt(identdect, paramlist);
}


void destroy (astree* tree1, astree* tree2) {
   if (tree1 != nullptr) delete tree1;
   if (tree2 != nullptr) delete tree2;
}

void errllocprintf (const location& lloc, const char* format,
                    const char* arg) {
   static char buffer[0x1000];
   assert (sizeof buffer > strlen (format) + strlen (arg));
   snprintf (buffer, sizeof buffer, format, arg);
   errprintf ("%s:%zd.%zd: %s", 
              lexer::filename (lloc.filenr), lloc.linenr, lloc.offset,
              buffer);
}
