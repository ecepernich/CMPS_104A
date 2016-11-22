//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file


#include "auxlib.h"
#include "lyutils.h"
#include "symstack.h"

void typecheck(FILE* symfile, astree* node, symstack* symbol_stack, 
	symbol_table* symbol_table);
