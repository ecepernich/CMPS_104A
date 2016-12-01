#include "astree.h"
#include "symstack.h"
#include "lyutils.h"
#include "auxlib.h"
#include <string>
#include <iostream>

void emit_header(FILE* oilfile);

void emit_program(FILE* oilfile, astree* node);

void emit_structdef(FILE* oilfile, astree* node);
void emit_stringdef(FILE* oilfile, astree* node);
void emit_vardef(FILE* oilfile, astree* node);

void emit_function(FILE* oilfile, astree* node);


void emit_stringcon(FILE* oilfile, astree* node);
void emit_intcon(FILE* oilfile, astree* node);
void emit_charcon(FILE* oilfile, astree* node);

// FUNCTION METHODS
void emit_function_name(FILE* oilfile, astree* node);
void emit_params(astree* node, FILE* oilfile);
void emit_function_body(FILE* oilfile, astree* node);

void emit(astree* node, FILE* oilfile);

void emit_main(FILE* oilfile, astree* root);
void emit_everything(FILE* oilfile, astree* root);

