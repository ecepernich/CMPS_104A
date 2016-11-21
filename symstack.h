// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file
//
// PDF 3.2

//struct symstack





extern size_t next_block;

class symstack
{
//public:         //sublimetext autogenerated these
	//symstack();
	//~symstack();
	vector <symbol_table> symbol_stack;
	void enter_block();
	void leave_block();
	void define_ident(astree* node);
	symbol* search_ident(astree* node);
};
