//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

#include <unordered_map>
#include <vector>
#include <bitset>
#include <utility>


//taken from pdf 2.2
struct symbol;
using symbol_table = unordered_map<const string*, symbol*>;
using symbol_entry =pair<const string*, symbol*>;
//each entry in the table is a pair<const string*,symbol*>
struct symbol {
        attr_bitset attributes;
        symbol_table* fields;
        location lloc;
        size_t block_nr;
        vector<symbol*>* parameters;
};

symbol* new_sym(astree* node);	
void insert_symbol(symbol_table* symbtab, astree* node);
search_symbol(symbol_table* symtab, astree* node);
