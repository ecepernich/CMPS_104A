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
#include <bitset>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "astree.h"

symbol* new_symbol(astree* node)
{
        symbol* sym = new symbol();
        sym->attr = node->attr;
        sym->fields = nullptr;
        sym->lloc = node->lloc;
        //would parameters be null?
        sym->block_nr=node->block_nr;
        return sym;
}

//need insert function 
void insert_symbol(symbol_table* symtab, astree* node){
        symbol* sym = new_symbol(node);
        //string* lexinfo = (string *)node->lexinfo;
        symbol_entry entry = symbol_entry 
                        (const_cast<string*>(node->lexinfo), sym);
}

//need lookup function 


symbol* search_symbol(symbol_table* symtab, astree* node)
{
        string* lexinfo = (string *)node->lexinfo; 
        if(!symtab->count(lexinfo)) //if we can't
                return nullptr;
        symbol* sym = new_symbol(node); //and create a new symbol 
        symbol_entry entry = symbol_entry
                (const_cast<string*> (node->lexinfo), sym ); 
       return entry.second; //want it to return the symbol

}

