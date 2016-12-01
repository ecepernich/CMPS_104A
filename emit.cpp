#include "emit.h"

int stringcon_nr=0;
int intcon_nr=0;
int charcon_nr=0;



void emit_header(FILE* oilfile)  //DONE
{
    fprintf(oilfile,"define __OCLIB_C__\n");
    fprintf(oilfile, "#include \"oclib.oh\"\n");
}

void emit_structdef(FILE* oilfile, astree* node)
{

}
void emit_stringdef(FILE* oilfile, astree* node)
{

}
void emit_vardef(FILE* oilfile, astree* node)
{

}

void emit_function(FILE* oilfile, astree* node)
{
    if (node->children.size()>=1)
    {
        emit_function_name(oilfile, node);
    }
    if (node->children.size()>=2)
    {
        emit_params(oilfile, node);
    }
    if (node->children.size()>=3 && node->symbol==TOK_FUNCTION)
    {
        emit_function_body(oilfile, node);
    }
}


void emit_stringcon(FILE* oilfile, astree* node)
{
    //expected result:
    //char* s1 = "Hello World!\n"
    stringcon_nr++;
    string varname = "s";
    cout << varname << stringcon_nr << endl;
    node->emit_code=varname.c_str();

    fprintf(oilfile, "char* %s = %s", node->emit_code, node->lexinfo->c_str());
}
void emit_intcon(FILE* oilfile, astree* node)
{
    //expected result:
    //char* s1 = "Hello World!\n"
    intcon_nr++;
    string varname = "a";
    cout << varname << intcon_nr << endl;
    node->emit_code=varname.c_str();

    fprintf(oilfile, "int* %s = %s", node->emit_code, node->lexinfo->c_str());
}
void emit_charcon(FILE* oilfile, astree* node)
{
    //expected result:
    //char* s1 = "Hello World!\n"
    charcon_nr++;
    string varname = "c";
    cout << varname << charcon_nr << endl;
    node->emit_code=varname.c_str();

    fprintf(oilfile, "char* %s = %s", node->emit_code, node->lexinfo->c_str());
}

// FUNCTION METHODS
void emit_function_name(FILE* oilfile, astree* node) //DONE
{
    astree* left=node->children[0];
    fprintf(oilfile, "__%s ",node->lexinfo->c_str());
}
void emit_params(FILE* oilfile, astree* node)
{
    fprintf(oilfile, " (");
    astree* paramhead = nullptr;
    if(node->children.size()>=2)
    {
        paramhead = node->children[1];
        fprintf(oilfile, "%s",paramhead->emit_code);
        int i=0;
        astree* plist=nullptr;
        if (paramhead->children.size()>=1)
        {
            while(plist!=nullptr)
            {
                fprintf(oilfile, ";\n %s",plist->emit_code);
                //maybe switch 
                i++;
                if (paramhead->children.size()>=(i+1))
                {
                    plist=paramhead->children[i];
                }
                else
                {

                    plist=nullptr;
                }
            }
        }
    }
    fprintf(oilfile, ") ");
}
void emit_function_body(FILE* oilfile, astree* node)
{
    //
}

void emit(FILE* oilfile, astree* node)
{
    switch(node->symbol)
    {
        case TOK_PROTOTYPE:
        {
            fprintf(oilfile, "We hit prototype.\n");
            break;
        }
        case TOK_STRINGCON: 
        case TOK_INTCON: 
        case TOK_CHARCON: 
        {
            break;
        }
        case TOK_FUNCTION:
        case TOK_CALL: 
        {
            emit_function(oilfile, node);
            break;
            //expected result:__puts(s1)
        }
        default:
        {
            break;
        }
    }
}

void emit_main(FILE* oilfile, astree* root)
{
    fprintf(oilfile, "void --ocmain(void)\n");
    for (astree* child: root->children) 
    {
      emit(oilfile, child);
    }
    emit(oilfile, root);
}

void emit_program(FILE* oilfile, astree* node)
{
    emit_structdef(oilfile, node);
    emit_stringdef(oilfile, node);
    emit_vardef(oilfile, node);
    emit_function(oilfile, node);
}

void emit_everything(FILE* oilfile, astree* root)
{
    emit_header(oilfile); //DONE
    emit_program(oilfile, root);
    emit_main(oilfile, root);
}
