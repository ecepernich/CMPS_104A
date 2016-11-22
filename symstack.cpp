// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//PDF part 3.2 This will help to build the symbol table 
//nested hashtable?

#include "symstack.h"
#include "astree.h"
#include <iostream>
#include <unordered_map>


void symstack::enter_block()
{
	next_block++;
	symbol_stack.push_back(nullptr); //adds null pointer at end of vector
}

void symstack::leave_block()
{
	symbol_stack.popback(); //pop next_block
	//next_block--; //move back in block# ???? Don't think we habe to move back a block 
}

void symstack::define_ident(astree* node)
{
	if (symbol_stack.back()==nullptr){ // if there is nothing in the symtable, create a new table and add it to the symtable
		symbol_stack.back()=new symbol_table;
        }
		insert_symbol(symbol_stack.back(), node);
}

symbol* symstack::search_ident(astree* node)
{
	for (auto symbol_table:symbol_stack) //ranged-based loop aka executes a loop over a range
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