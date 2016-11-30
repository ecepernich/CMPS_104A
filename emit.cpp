#include "emit.h"

void emit_everything(oilfile, astree* root)
{
	emit_header(oilfile);
	emit_program(oilfile);

}

void emit_header(FILE* oilfile)
{
	fprintf(oilfile,"define __OCLIB_C__\n");
	fprintf(oilfile, "#include \"oclib.oh\"\n");
}

void emit_program(FILE* oilfile)
{

}

void emit_stringdef(FILE* oilfile)
{

}

void emit_function(FILE* oilfile)
{

}

void emit_function_name(astree* node, FILE* oilfile){
	astree* left = node->children[0];
	fprintf(oilfile, "__%s", lexinfo-c_str());
}

void emit_stringcon(FILE* oilfile)
{
	//expected result:
	//char* s1 = "Hello World!\n"
	emit_code = "s" + node -> blocknr
	node->emit_code = "s" + node-> blocknr

	fprintf(oilfile, "char*%s=%s", node->emit_code, node->lexinfo-c_str());

	//push s1 into vector(string) queue_stringcon?

}

void emit(astree* node,FILE* oilfile)
{
	switch(node->symbol){
		case TOK_PROTOTYPE:
		     break;

		case TOK_STRINGCON:
		     {emit_stringcon(oilfile, node)
		      break;
		      }
		case TOK_CALL:
            //expected result:__puts(s1)

                
 }
}
