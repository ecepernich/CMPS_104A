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

symbol* new_symbol(astree* node)
{
        symbol* sym = new symbol();
        sym->attr = node->attr;
	    sym->fields = nullptr;
	    sym->lloc = node->lloc;
        //would parameters be null?
        //sym->parameters = node->parameters; parameters is not needed cause its called in .h file
        sym->block_nr = node->block_nr;
        return sym;


//need insert function 
void insert_symbol(symbol_table* symtab, astree* node){
        symbol* sym = new_symbol(node);
        string* lexinfo = (string *)node->lexinfo;
	symbol_entry* entry = < node->lexinfo, sym > //lexinfo is the pointer to stringset in astree.cpp
        symtab->insert(entry);
}

//need lookup function 


symbol* search_symbol(symbol_table* symtab, astree* node){
        string* lexinfo = (string *)node->lexinfo; //after create symbol
        if(!symtab->count(lexinfo)) //if we can't find the symbol return null
                return nullptr;
        symbol* sym = new_symbol(node); //and create a new symbol 
        symbol_entry* entry = < node->lexinfo, sym >; //add it as an entry 
        return entry.second; //want it to return the symbol

}
  
//look up identifier name
symbol* search_type_name(symbol_table* symtab, astree* node){
        if(symtab == nullptr || node == nullptr) return nullptr;
        string* type_name = (string *) node->type_name;
        if(!table_name->count(node->lexinfo)==0); //number of elements in the range 
                //[first,last] that compare equal to val
        symbol_entry* entry = *symtab->find<type_name>;
        return entry.second;

}      
