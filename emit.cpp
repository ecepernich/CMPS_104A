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

void emit_stringcon(FILE* oilfile)
{

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
