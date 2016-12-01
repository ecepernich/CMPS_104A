#include "emit.h"

int stringcon_nr=1;
int intcon_nr=1;
int charcon_nr=1;

void emit_header(FILE* oilfile)  //DONE
{
    fprintf(oilfile,"#define __OCLIB_C__\n");
    fprintf(oilfile, "#include \"oclib.oh\"\n\n");
}

void emit_structdef(FILE* oilfile, astree* root)
{
    emit_structdecl(oilfile, root);
    for (astree* child: root->children) 
    {
      emit_structdecl(oilfile, child);
    }
}
void emit_structdecl(FILE* oilfile, astree* node)
{
    if (node->symbol==TOK_STRUCT)
    {
        astree* left=nullptr;
        astree* right=nullptr;
        if (node->children.size()>=1)
        {
            left=node->children[0];
        }
        if (node->children.size()>=2)
        {
            right=node->children[1];
        }       
    }
}

void emit_stringdef(FILE* oilfile, astree* node)
{
    emit_stringcon(oilfile, node);
    for (astree* child: node->children) 
    {
      emit_stringdef(oilfile, child);
    }
}

void emit_vardef(FILE* oilfile, astree* node)
{
    emit_vardecl(oilfile, node);
    for (astree* child: node->children) 
    {
      emit_vardecl(oilfile, child);
    }
}

void emit_vardecl(FILE* oilfile, astree* node)
{
    if (node->symbol==TOK_VARDECL)
    {
        astree* left=nullptr;
        astree* left2=nullptr;
        if (node->children.size()>=1)
        {
            left=node->children[0];
            if (left->children.size()>=1)
            {
                left2=left->children[0];
                fprintf(oilfile, "%s __%s;\n", left->lexinfo->c_str(), 
                                               left2->lexinfo->c_str());
            }
        }
    }
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
    if (node->symbol==TOK_STRINGCON)
    {
        std::string varname = "s";
        varname += std::to_string(stringcon_nr);
        node->emit_code=varname.c_str();

        fprintf(oilfile, "char* %s = %s \n", node->emit_code, 
                                             node->lexinfo->c_str());
        stringcon_nr++;
    }
}
void emit_intcon(FILE* oilfile, astree* node)
{
    string varname = "a";
    varname += std::to_string(intcon_nr);
    node->emit_code=varname.c_str();

    fprintf(oilfile, "int* %s = %s\n ", node->emit_code, 
                                        node->lexinfo->c_str());
    intcon_nr++;
}
void emit_charcon(FILE* oilfile, astree* node)
{
    string varname = "c";
    varname += std::to_string(charcon_nr);
    node->emit_code=varname.c_str();

    fprintf(oilfile, "char** %s = %s", node->emit_code, 
                                      node->lexinfo->c_str());
    charcon_nr++;
}

// FUNCTION METHODS
void emit_function_name(FILE* oilfile, astree* node) //DONE
{
    astree* left=node->children[0];
    fprintf(oilfile, "\t__%s",left->lexinfo->c_str());
}
void emit_params(FILE* oilfile, astree* node)
{
    fprintf(oilfile, "(");
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
    fprintf(oilfile, ") \n");
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
    fprintf(oilfile, "\nvoid __ocmain(void)\n{ \n");
    for (astree* child: root->children) 
    {
      emit(oilfile, child);
    }
    emit(oilfile, root);
    fprintf(oilfile, "}\n");
}

void emit_program(FILE* oilfile, astree* node)
{
    emit_structdef(oilfile, node);
    emit_stringdef(oilfile, node);
    emit_vardef(oilfile, node);
    //emit_function(oilfile, node);
}

void emit_everything(FILE* oilfile, astree* root)
{
    emit_header(oilfile); //DONE
    emit_program(oilfile, root);
    emit_main(oilfile, root);
}

