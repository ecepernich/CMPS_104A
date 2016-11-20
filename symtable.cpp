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

symbol* new_symbol(astree* node){
        symbol* sym = new symbol();
        sym->attributes = node->attributes;
	sym->fields = nullptr;
        sym->filenr = node->filenr;
        sym->linenr = node->linenr;
        sym->offset = node->offset;
        //would parameters be null?
        //sym->parameters = node->parameters; parameters is not needed cause its called in .h file
        sym->block_nr = node->block_nr;
        return sym;


//need insert function 
void insert_symbol(symbol_table* symtab, astree* node){
        symbol* sym = new_symbol(node);
	symbol_entry* entry = < node->lexinfo, sym > //lexinfo is the pointer to stringset in astree.cpp
        symtab->insert(ry);
}

//need lookup function 


symbol* search_symbol(symbol_table* symtab, astree* node){
        string* lexinfo = node->lexinfo;
        if(!symtab->count(lexinfo)) //if we can't find the symbol return null
                return nullptr;
        symbol* sym = new_symbol(node); //and create a new symbol 
        symbol_entry* entry = < node->lexinfo, sym >; //add it as an entry 
        return entry.second; //want it to return the symbol

}
        
//3. get name for symbol from typecheck
// I am not really sure what to do here 