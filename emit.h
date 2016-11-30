#include "astree.h"
#include "symstack.h"
#include "lyutils.h"
#include "auxlib.h"
#include <string>
#include <iostream>

void emit_everything(FILE* oilfile, astree* root);
void emit_header(FILE* oilfile);
void emit_program(FILE* oilfile, astree* root);
void emit_stringdef(FILE* oilfile, astree* root);
void emit_function(FILE* oilfile, astree* node);
void emit_stringcon(FILE* oilfile, astree* node);
void emit(astree* node,FILE* oilfile);
