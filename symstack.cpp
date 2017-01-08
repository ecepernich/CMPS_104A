// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 5: .oil file

//PDF part 3.2 This will help to build the symbol table 
//nested hashtable?

#include "astree.h"
#include "symstack.h"
#include "symtable.h"
#include <iostream>
#include <unordered_map>


void symstack::enter_block()
{
    next_block++;
    symbol_stack.push_back(nullptr); // null pointer at end of vector
}

void symstack::leave_block()
{
    symbol_stack.pop_back(); //pop next_block
    //next_block--; //move back in block# ???? D
}

void symstack::define_ident(astree* node)
{
    if (symbol_stack.back()==nullptr){ // if t
        symbol_stack.back()=new symbol_table;
        }
        insert_symbol(symbol_stack.back(), node);
}

symbol* symstack::search_ident(astree* node)
{
    for (auto symbol_table:symbol_stack) //ranged-based loop a
    {
        if (symbol_table==nullptr)
        { 
         return nullptr;
        }else{
            symbol* s =search_symbol(symbol_table, node);
            // some search function (not this one)
            if (s != nullptr)
            {
                return s;
            }
        }
    }
    return nullptr;

}
