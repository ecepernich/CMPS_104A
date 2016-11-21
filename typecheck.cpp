//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//helper print function
#include "astree.h"
#include "auxlib.h"
#include "symstack.h"
#include "symtable.h"

void printhelper(FILE* symfile, astree* node)
{
    astree* left=node->children[0];
    fprintf (symfile, "%s (%zd.%zd.%zd) \n",
            left->lexinfo->c_str(), node->lloc.filenr, node->lloc.linenr, 
            node->lloc.offset);
    if (node->attr[attr_struct]) { fprintf(symfile, "struct \"%s",
                        current_struct>lexinfo.c_str(),"\" "); }
    if (node->attr[attr_field]) { fprintf(symfile, "field {%s"+
                        current_field->lexinfo.c_str(),"} "); }
    if (node->attr[attr_function]) { fprintf(symfile, "function "); }
    if (node->attr[attr_void]) { fprintf(symfile, "void "); }
    if (node->attr[attr_int]) { fprintf(symfile, "int "); }
    if (node->attr[attr_null]) { fprintf(symfile, "null "); }
    if (node->attr[attr_string]) { fprintf(symfile, "string "); }
    if (node->attr[attr_const]) { fprintf(symfile, "const "); }
    if (node->attr[attr_array]) { fprintf(symfile, "array "); }
    if (node->attr[attr_typeid]) { fprintf(symfile, "type_id "); }
    if (node->attr[attr_vreg]) { fprintf(symfile, "vreg "); }
    if (node->attr[attr_vaddr]) { fprintf(symfile, "vaddr "); }
    if (node->attr[attr_variable]) { fprintf(symfile, "variable "); }
    if (node->attr[attr_lval]) { fprintf(symfile, "lval "); }
    if (node->attr[attr_param]) { fprintf(symfile, "param "); }
    fprintf(symfile, "\n");
}

astree* current_struct=nullptr;
astree* current_field=nullptr;

//upcoming switch statement for something


//declare child vars
void typecheck_function(FILE* symfile, astree* node, symstack* symbol_stack, symtable* symbol_table)
{

    int block_nr=0;
    astree* left=nullptr;
    astree* right=nullptr;
    symbol* s;

    // children size check?
    if (node->children[0]!=nullptr)
    {
        left=node->children[0];
    }
    if (node->children[1]!=nullptr)
    {
        right=node->children[1];
    }
    switch(node->symbol)
    {
        case TOK_ROOT: break;
        case '(':      break;
        case ')':      break;
        case '{':      break;
        case '}':      break;
        case '[':      break;
        case ']':      break;
        case ';':      break;

        case TOK_RETURN: break;
        case TOK_RETURNVOID: break;
        case TOK_PARAM:  {

            break;
        }

        case TOK_NEW: {
            left=node->children[0];
            for (size_t i=0;i<15;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            break;
        }
        case TOK_TYPEID: {
            node->attr[attr_typeid]=1;
            break; 
        }
        case TOK_DECLID: {
            symbol_stack->define_ident(node);
            break;
        }
        case TOK_FIELD: {
            node->attr[attr_field]=1;
            left=node->children[0];
            if (left!=nullptr)
            {
                left->attr[attr_field]=1;
                for (size_t i=0;i<attr_function;i++)
                {
                    if (left->attr[i]) { node->attr[i]=1; }
                }
            }
            break; 
        }
        case TOK_FUNCTION: //////////////////////////////////////////////////////
        case TOK_INT: {
            left=node->children[0];
            if (left==nullptr)
                {break;}
            else
            {
                left->attr[attr_int]=1;
                for (size_t i=0;i<attr_function;i++)
                {
                    if (left->attr[i]) { node->attr[i]=1; }
                }
            }
            break;
        }
        case TOK_PROTOTYPE: {
            left=node->children[0];
            astree* left2=left->children[0];
            current_field=left;

            node->attr[attr_function]=1;
            left->attr[attr_function]=1;
            left2->attr[attr_function]=1;
            printhelper(symfile, left2);

            right=node->children[1]->children[0];
            while(right!=nullptr)
            {
                left=right->children[0];
                left->attr[attr_param]=1;
                left->attr[attr_variable]=1;
                left->attr[attr_lval]=1;
                printhelper(symfile, left);
                right=right->children[1];
            }
            break;
        }

        case TOK_CALL: {      ///////////////////////////////////////////////////////

            //finding symbols???
            break;
        }
        case TOK_CHAR:    break;
        case TOK_BOOL:    break;
        case TOK_VOID: {
            left=node->children[0];
            left->attr[attr_void]=1;
            break;
        }
        case TOK_STRING: {
            left=node->children[0];
            left->attr[attr_string]=1;
            for (size_t i=0;i<attr_function;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            break;
        }
        case TOK_ARRAY: {
            left=node->children[0];
            left->attr[attr_array]=1;
            astree* leftleft=nullptr;
            if (left->children[0]!=nullptr)
            {
                leftleft=left->children[0];
            }
            leftleft->attr[attr_array]=1;
            break;
        }
        case TOK_NEWARRAY: {
            left=node->children[0];
            for (size_t i=0;i<attr_function;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            node->attr[attr_array]=1;
            node->attr[attr_vreg]=1;

            break;
        }
        case TOK_VOID: {
            left=node->children[0];
            left->attr[attr_void]=1;
        }
        case TOK_INDEX: {
            node->attr[attr_vaddr]=1;
            node->attr[attr_lval]=1;
            break; 
        }
        case TOK_IDENT:  {
            s=lookup_ident(node);
            if (s==nullptr)
            {
                s=search_symbol(symbol_table, node);
            }
            if (s==nullptr)
            {
                errprintf("Undefined identifier \n");
            }
            else
            {
                node->attr=s->attr;
            }
            break;
        }
        case TOK_STRUCT: {
            current_struct=node;

            left=node->children[0];

            node->attr[attr_struct]=1;
            left->attr[attr_struct]=1;
            printhelper(symfile, left);

            insert_symbol(struct_table, left);
            s=search_symbol(struct_table, left);
            s->fields=new symbol_table;

            right=node->children[1];
            while(right!=nullptr)
            {
                astree* leftchild=right->children[0];
                printhelper(leftchild);
                right=right->children[1];
            }
            break;
        }
        case TOK_IF:       break;
        case TOK_IFELSE:   break;
        case TOK_WHILE:    break;
        case '+':
        case '-': {
            node->attr[attr_int]=1;
            node->attr[attr_vreg]=1;
            left=node->children[0];
            right=node->children[1];
            if (left==nullptr)
            {
                break;
            }
            if (right==nullptr) //typecheck +/- int
            {
                if (!left->attr[attr_int])
                {
                    errprintf("Error: not type int.\n");
                }
            }
            else //typecheck int +/- int
            {
                if (!left->attr[attr_int] || !right->attr[attr_int])
                {
                    errprintf("Error: not type int & int.\n");
                }
            }
            break; 
        }
        case '*':
        case '/':
        case '%': {
            node->attr[attr_int]=1;
            node->attr[attr_vreg]=1;
            left=node->children[0];
            right=node->children[1];
            if (right==nullptr || left==nullptr) //typecheck 2 ints
            {
                errprintf("Error: one or more types missing.\n");
            }
            else //typecheck int *///% int
            {
                if (!left->attr[attr_int] || !right->attr[attr_int])
                {
                    errprintf("Error: not type int & int.\n");
                }
            }
            break;
        }
        case '!': {
            node->attr[attr_int]=1;
            node->attr[attr_vreg]=1;
            // 1 child?
            break;
        }
        case '=':
        case TOK_EQ:
        case TOK_GT:
        case TOK_GE:
        case TOK_LT:
        case TOK_LE:

        case TOK_INTCON: {
            node->attr[attr_int]=1;
            node->attr[attr_const]=1;
            break;
        }
        case TOK_CHARCON: {
            node->attr[attr_int]=1;
            node->attr[attr_const]=1;
            break;
        }
        case TOK_STRINGCON: {
            node->attr[attr_string]=1;
            node->attr[attr_const]=1;
            break;
        }
        case TOK_NULL: {
            node->attr[attr_null]=1;
            node->attr[attr_const]=1;
            break;
        }
        default:
        {
            break;
        }
    }
}
    