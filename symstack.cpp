// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//PDF part 3.2 This will help to build the symbol table 
//nested hashtable?


int next_block=1;

void symstack::enter_block()
{
	symbol_stack.pushback(nullptr); //add nullptr 
	symbol_stack.pushback(next_block); //add next_block
	next_block++; //move forward for block#
}

void symstack::leave_block()
{
	symbol_stack.popback(); //pop next_block
	symbol_stack.popback(); //pop nullptr
	next_block--; //move back in block#
}

void symstack::define_ident(astree* tree)
{
	if (symbol_stack.back()==nullptr)
	{
		symbol_stack.back()=new symbol_table;
	}
	//else
	//{
		symbol_stack.pushback(tree);
	//}


}

void symstack::search_ident(astree* tree)
{

	for (symbol_table:symbol_stack)
	{
		symbol_table temp=
		if (symbol_table==nullptr)
		{

		}
		else
		{

		}
	}

}