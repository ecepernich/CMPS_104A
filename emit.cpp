#include "emit.h"

void emit_everything(oilfile, astree* root)
{
	emit_header(oilfile);
	
}

void emit_header(oilfile)
{
	fprintf(oilfile,"define __OCLIB_C__\n");
	fprintf(oilfile, "#include \"oclib.oh\"\n");
}

void emit_program()
{

}

void emit_stringdef()
{

}

void emit_function()
{

}

void emit_stringcon()
{

}

void emit()
{
	
}