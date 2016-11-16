// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//PDF part 3.2 This will help to build the symbol table 
//nested hashtable?


int next_block=1;

void symstack::enter_block()
{
	symbol_stack.pushback(nullptr);
	symbol_stack.pushback(next_block);
	next_block++;
}

void symstack::leave_block()
{
	symbol_stack.popback(next_block);
	symbol_stack.popback(nullptr);
	next_block--;
}

void symstack::define_ident()
{



}

void symstack::search_ident()
{

	
}