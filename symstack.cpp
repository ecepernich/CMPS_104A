// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//PDF part 3.2 This will help to build the symbol table 
//nested hashtable?


next_block=1;

void symstack::enter_block()
{
	symbol_stack.pushback(nullptr); //add nullptr 
	symbol_stack.pushback(next_block); //add next_block
	next_block++; //move forward for block#
}

void symstack::leave_block()
{
	symbol_stack.popback(); //pop next_block
	next_block--; //move back in block# ????
}

void symstack::define_ident(astree* node)
{
	if (symbol_stack.back()==nullptr) // if there is nothing in the symtable, create a new table and add it to the symtable
	//{
		symbol_stack.back()=new symbol_table;
		insert_symbol(symbol_stack.back, node);
	//}
	//else
	//{
		//symbol_stack.pushback(tree); //??????
		//insert into symbol table
	//}
}

symbol* symstack::search_ident(astree* node)
{

	for (symbol_table:symbol_stack)
	{
		if (symbol_table==nullptr)
		{ }
		else
		{
			symbol* s=search_ident(tree->symbol);
			// some search function (not this one)
			if (s != nullptr)
			{
				return s;
			}
		}
	}
	return nullptr;

}