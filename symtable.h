//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

#include <unordered_map>
#include <vector>
#include <bitset>
#include <utility>


//taken from pdf 2.2
enum {  ATTR_void, ATTR_int, ATTR_null, ATTR_string, ATTR_struct, ATTR_array, 
        ATTR_function, ATTR_variable, ATTR_field, ATTR_typeid, ATTR_param, ATTR_lval
        ATTR_vreg, ATTR_vaddr, ATTR_bitset_size,
};
using attr_bitset = bitset<ATTR_bitset_size>;

struct symbol;
using symbol_table = unordered_map<const string*, symbol*>;
using symbol_entry =pair<const string*, symbol*>;
//each entry in the table is a pair<const string*,symbol*>
struct symbol {
        attr_bitset attributes;
        symbol_table* fields;
        size_t filenr, linenr, offset;
        size_t block_nr;
        vector<symbol*>* parameters;
};

symbol* new_sym(astree* node);	
