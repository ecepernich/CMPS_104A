//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//helper print function
#include "astree.h"
#include "auxlib.h"
#include "symstack.h"
#include "symtable.h"
#include "typecheck.h"

void printhelper(FILE* symfile, astree* node)
{
    astree* left=node->children[0];
    fprintf (symfile, "%s (%zd.%zd.%zd) \n",
            left->lexinfo->c_str(), node->lloc.filenr, node->lloc.linenr, 
            node->lloc.offset);
    if (node->attr[ATTR_struct]) { fprintf(symfile, "struct \"%s",
                        current_struct>lexinfo.c_str(),"\" "); }
    if (node->attr[ATTR_field]) { fprintf(symfile, "field {%s"+
                        current_field->lexinfo.c_str(),"} "); }
    if (node->attr[ATTR_function]) { fprintf(symfile, "function "); }
    if (node->attr[ATTR_void]) { fprintf(symfile, "void "); }
    if (node->attr[ATTR_int]) { fprintf(symfile, "int "); }
    if (node->attr[ATTR_null]) { fprintf(symfile, "null "); }
    if (node->attr[ATTR_string]) { fprintf(symfile, "string "); }
    if (node->attr[ATTR_const]) { fprintf(symfile, "const "); }
    if (node->attr[ATTR_array]) { fprintf(symfile, "array "); }
    if (node->attr[ATTR_typeid]) { fprintf(symfile, "type_id "); }
    if (node->attr[ATTR_vreg]) { fprintf(symfile, "vreg "); }
    if (node->attr[ATTR_vaddr]) { fprintf(symfile, "vaddr "); }
    if (node->attr[ATTR_variable]) { fprintf(symfile, "variable "); }
    if (node->attr[ATTR_lval]) { fprintf(symfile, "lval "); }
    if (node->attr[ATTR_param]) { fprintf(symfile, "param "); }
    fprintf(symfile, "\n");
}

bool primcheck(astree* left, astree* right)
{
    for (size_t i=0;i<attr_function;i++)
    {
        if (left->attr[i]==1 && right->attr[i]==1)
        {
            return true;
        }
    }
    return false;
}

astree* current_struct=nullptr;
astree* current_field=nullptr;

//upcoming switch statement for something

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
            for (size_t i=0;i<attr_bitset_size;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            break;
        }
        case TOK_TYPEID: {
            node->attr[ATTR_typeid]=1;
            break; 
        }
        case TOK_DECLID: {
            symbol_stack->define_ident(node);
            break;
        }
        case TOK_FIELD: {
            node->attr[ATTR_field]=1;
            left=node->children[0];
            if (left!=nullptr)
            {
                left->attr[ATTR_field]=1;
                for (size_t i=0;i<attr_function;i++)
                {
                    if (left->attr[i]) { node->attr[i]=1; }
                }
            }
            break; 
        }
         //////////////////////////////////////////////////////
        case TOK_INT: {
            left=node->children[0];
            if (left==nullptr)
                {break;}
            else
            {
                left->attr[ATTR_int]=1;
                for (size_t i=0;i<ATTR_function;i++)
                {
                    if (left->attr[i]) { node->attr[i]=1; }
                }
            }
            break;
        }
        case TOK_FUNCTION:
        case TOK_PROTOTYPE: {
            left=node->children[0];
            astree* left2=left->children[0];
            current_field=left;

            node->attr[ATTR_function]=1;
            left->attr[ATTR_function]=1;
            left2->attr[ATTR_function]=1;
            printhelper(symfile, left2);

            middle=node->children[1]->children[0];
            while(right!=nullptr)
            {
                left=middle->children[0];
                left->attr[ATTR_param]=1;
                left->attr[ATTR_variable]=1;
                left->attr[ATTR_lval]=1;
                printhelper(symfile, left);
                middle=middle->children[1];
            }

            if (node->symbol==TOK_PROTOTYPE)
            {
                break;
            }
            else
            {

            }


            break;
        }

        case TOK_CALL: {      ///////////////////////////////////////////////////////


            node->attr[ATTR_call]=1; ////2g
            node-attr=node->children[0]->sym->attr;
            node->attr[ATTR_vreg]=1;
            node->attr.flip(ATTR_function);
            node->typename=node->children[0]->sym0>ttname


            //output: puts (loc) {0} void function 
            //          s (loc) {0} string const lval variable param

            //finding symbols???
            break;
        }
        case TOK_CHAR:    break;
        case TOK_BOOL:    break;
        case TOK_VOID: {
            left=node->children[0];
            left->attr[ATTR_void]=1;
            break;
        }
        case TOK_STRING: {
            left=node->children[0];
            left->attr[ATTR_string]=1;
            for (size_t i=0;i<ATTR_function;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            break;
        }
        case TOK_ARRAY: {
            left=node->children[0];
            left->attr[ATTR_array]=1;
            astree* leftleft=nullptr;
            if (left->children[0]!=nullptr)
            {
                leftleft=left->children[0];
            }
            leftleft->attr[ATTR_array]=1;
            break;
        }
        case TOK_NEWARRAY: {
            left=node->children[0];
            for (size_t i=0;i<ATTR_function;i++)
            {
                if (left->attr[i]) { node->attr[i]=1; }
            }
            node->attr[ATTR_array]=1;
            node->attr[ATTR_vreg]=1;

            break;
        }
        case TOK_VOID: {
            left=node->children[0];
            left->attr[ATTR_void]=1;
        }
        case TOK_INDEX: {
            node->attr[ATTR_vaddr]=1;
            node->attr[ATTR_lval]=1;
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

            node->attr[ATTR_struct]=1;
            left->attr[ATTR_struct]=1;
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
            node->attr[ATTR_int]=1;
            node->attr[ATTR_vreg]=1;
            left=node->children[0];
            right=node->children[1];
            if (left==nullptr)
            {
                break;
            }
            if (right==nullptr) //typecheck +/- int
            {
                if (!left->attr[ATTR_int])
                {
                    errprintf("Error: not type int.\n");
                }
                else
                {
                    node->attr[ATTR_vreg]=1;
                    node->attr[ATTR_int]=1;
                }
            }
            else //typecheck int +/- int
            {
                if (!left->attr[ATTR_int] || !right->attr[ATTR_int])
                {
                    errprintf("Error: not type int & int.\n");
                }
            }
            break; 
        }
        case '*':
        case '/':
        case '%': {
            node->attr[ATTR_int]=1;
            node->attr[ATTR_vreg]=1;
            left=node->children[0];
            right=node->children[1];
            if (right==nullptr || left==nullptr) //typecheck 2 ints
            {
                errprintf("Error: one or more types missing.\n");
            }
            else //typecheck int *///% int
            {
                if (!left->attr[ATTR_int] || !right->attr[ATTR_int])
                {
                    errprintf("Error: not type int & int.\n");
                }
            }
            break;
        }
        case '!': {
            left=node->children[0];
            if (left==nullptr)
            {
                break;
            }
            if (!left->attr[ATTR_int])
            {
                errprintf("Error: not type int.\n");
            }
            else
            {
                node->attr[ATTR_vreg]=1;
                node->attr[ATTR_int]=1;
            }
            break;
        }
        case '=': {
            left=node->children[0];
            right=node->children[1];
            break;
        }
        case TOK_EQ:
        case TOK_NE: {
            left=node->children[0];
            right=node->children[1];
            if (primcheck(left, right))
            {
                //node->attr[attr_bool]=1;
                node->attr[ATTR_vreg]=1;                
            }
            elseif ()
            else
            {
                errprintf("Types do not match.\n");
            }
            break;
        }
        case TOK_GT:
        case TOK_GE:
        case TOK_LT:
        case TOK_LE:  {
            left=node->children[0];
            right=node->children[1];
            if (primcheck(left, right))
            {
                //node->attr[attr_bool]=1;
                node->attr[ATTR_vreg]=1;                
            }
            else
            {
                errprintf("Types do not match.\n");
            }
            break;
        }

        case TOK_INTCON: {
            node->attr[ATTR_int]=1;
            node->attr[ATTR_const]=1;
            break;
        }
        case TOK_CHARCON: {
            node->attr[ATTR_int]=1;
            node->attr[ATTR_const]=1;
            break;
        }
        case TOK_STRINGCON: {
            node->attr[ATTR_string]=1;
            node->attr[ATTR_const]=1;
            break;
        }
        case TOK_NULL: {
            node->attr[ATTR_null]=1;
            node->attr[ATTR_const]=1;
            break;
        }
        default:
        {
            break;
        }
    }
}


void typecheck(FILE* symfile, astree* parseroot, symstack* symbol_stack, symtable* symbol_table)
{
    for (astree* child: parseroot->children) 
    {
      typecheck(symfile, child, symbol_stack, symbol_table);
    }
    typecheck_function(symfile, parseroot, symbol_stack, symbol_table);
}
