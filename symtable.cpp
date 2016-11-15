//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//implementing figure 2 in PDF
//1.We want to insert symbol into table
//2. search symbol table
//3. get type name for symbol from typecheck
//
#include "symtable.h"
#include "astree.h"
#include "typcheck.h"

symbol* new_sym(astree* node){
        symbol* sym = new symbol();
        sym->attributes = node->attributes;
	sym->fields = node->fields;
        sym->filenr = node->filenr;
        sym->linenr = node->linenr;
        sym->offset = node->offset;
        //would parameters be null?
        sym->parameters = node->parameters;
        sym->block_nr = node->block_nr;
        return sym;


//need insert function 




//need lookup function 
   
