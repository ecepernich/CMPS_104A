// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 5: .oil file

//helper print function
#include "astree.h"
#include "auxlib.h"
#include "symstack.h"
#include "symtable.h"
#include "typecheck.h"
#include "lyutils.h"

astree* current_struct=nullptr;
astree* current_field=nullptr;

void printhelper(FILE* symfile, astree* node)
{
    astree* left=nullptr;   
    if (node->children.size()>=1)
    {
        left=node->children[0];
        fprintf (symfile, "%s (%zd.%zd.%zd) ",
        left->lexinfo->c_str(), node->lloc.filenr, node->lloc.linenr, 
        node->lloc.offset);
    }
    else
    {
        fprintf (symfile, "%s (%zd.%zd.%zd) {%zu} ",
        node->lexinfo->c_str(), node->lloc.filenr, node->lloc.linenr, 
        node->lloc.offset, node->block_nr);
    }
    if (node->attr[ATTR_struct]) { fprintf(symfile, "struct \"%s\" ",
                        current_struct->lexinfo->c_str()); }
    if (node->attr[ATTR_field]) { fprintf(symfile, "field {%s} ",
                        current_field->lexinfo->c_str()); }
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
    for (size_t i=0;i<ATTR_function;i++)
    {
        if (left->attr[i]==1 && right->attr[i]==1)
        {
            return true;
        }
    }
    return false;
}


//upcoming switch statement for something

void typecheck_function(FILE* symfile, astree* node, 
            symstack* symbol_stack, symbol_table* symbol_table)
{

    //int block_nr=0;
    astree* left=nullptr;
    astree* right=nullptr;

    if(node->children.size() >= 1)
    {
        left=node->children[0];
    }
    if(node->children.size() >= 2)
    {
        right=node->children[1];
    }

    symbol* s;

    // children size check?

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
        case TOK_PARAMLIST:  {

            break;
        }

        case TOK_NEW: {
            for (size_t i=0;i<ATTR_bitset_size;i++)
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
            if (left!=nullptr)
            {
                left->attr[ATTR_field]=1;
                for (size_t i=0;i<ATTR_function;i++)
                {
                    if (left->attr[i]) 
                    { 
                        node->attr[i]=1; 
                    }
                }
            }
            break; 
        }
         //////////////////////////////////////////////////////
        case TOK_INT: {
            if (left!=nullptr)
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

            astree* middle=nullptr;

            node->children[1]->children[0];
            if (node->children[1]->children.size()>=1)
            {
                middle=node->children[1]->children[0];
                middle->block_nr=middle->block_nr+1;
            }
            else { middle=nullptr; }

            while(middle!=nullptr)
            {
                left=middle->children[0];
                left->attr[ATTR_param]=1;
                left->attr[ATTR_variable]=1;
                left->attr[ATTR_lval]=1;
                fprintf(symfile,"\t");
                left->block_nr=middle->block_nr;
                printhelper(symfile, left);
                if (middle->children.size()>=2)
                {
                    middle=middle->children[1];
                    middle->block_nr=left->block_nr;

                }
                else { middle=nullptr; }
            }

            if (node->symbol==TOK_PROTOTYPE)
            {
                break;
            }
            else
            {
                break;
            }


            break;
        }
        case TOK_CALL: {


            node->attr[ATTR_function]=1; ////2g
            //node-attr=node->children[0]->sym->attr;
            //node->attr[ATTR_vreg]=1;
            //node->attr.flip(ATTR_function);
            //node->typename=node->children[0]->sym0>ttname


            //output: puts (loc) {0} void function 
            //          s (loc) {0} string const lval variable param

            //finding symbols???
            break;
        }
        case TOK_CHAR:    break;
        case TOK_VOID: {
            left->attr[ATTR_void]=1;
            break;
        }
        case TOK_STRING: {
            if (left!=nullptr)
            {
                left->attr[ATTR_string]=1;
                for (size_t i=0;i<ATTR_function;i++)
                {
                    if (left->attr[i]) { node->attr[i]=1; }
                }
            }
            break;
        }
        case TOK_ARRAY: {
            left->attr[ATTR_array]=1;
            if(left->children.size()>=1)
            {
                left->children[0]->attr[ATTR_array]=1;;
            }
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
        case TOK_INDEX: {
            node->attr[ATTR_vaddr]=1;
            node->attr[ATTR_lval]=1;
            break; 
        }
        case TOK_IDENT:  {
            s=symbol_stack->search_ident(node);
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
            current_struct=left;
            current_field=left;

            node->attr[ATTR_struct]=1;
            left->attr[ATTR_struct]=1;
            printhelper(symfile, left);

            insert_symbol(symbol_table, left);
            s=search_symbol(symbol_table, left);

            right=node->children[1];
            while(right!=nullptr)
            {
                astree* leftchild=nullptr;
                if(right->children.size()>=1)
                {
                    leftchild=right->children[0];
                    fprintf(symfile, "\t");
                    printhelper(symfile, leftchild);
                }
                if(right->children.size()>=2)
                {
                    right=right->children[1];
                }
                else
                {
                    right=nullptr;
                }
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
            if (left==nullptr)
            {
                break;
            }
            else if (right==nullptr) //typecheck +/- int
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
            if (left==nullptr)
            {
                break;
            }
            else if (!left->attr[ATTR_int])
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
            if (node->children.size()>=1)
            {
                left=node->children[0];
            }
            else { left=nullptr; }
            if (node->children.size()>=2)
            {
                right=node->children[1];
            }
            else { right=nullptr; }
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
        case TOK_GT:
        case TOK_GE:
        case TOK_LT:
        case TOK_LE:  {
            if (node->children.size()>=1)
            {
                left=node->children[0];
            }
            else { left=nullptr; }
            if (node->children.size()>=2)
            {
                right=node->children[1];
            }
            else { right=nullptr; }
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
            errprintf("Not a valid TOK.\n");
            break;
        }
    }
}


void typecheck(FILE* symfile, astree* parseroot, 
            symstack* symbol_stack, symbol_table* symbol_table)
{
    for (astree* child: parseroot->children) 
    {
      typecheck(symfile, child, symbol_stack, symbol_table);
    }
    typecheck_function(symfile, parseroot, symbol_stack, symbol_table);
}

