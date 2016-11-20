//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//helper print function
void printhelper(FILE* symfile, astree* node, int block_nr)
{
	astree* left=node->children[0];
	fprintf (outfile, "%s (%zd.%zd.%zd) %d \n",
            left->lexinfo->c_str(), node->lloc.filenr, node->lloc.linenr, 
            node->lloc.offset, block_nr);
	fprintf(symfile, "%s", enumhelper(node->attr).c_str());
	fprintf(symfile, "\n");
}


//upcoming switch statement for something


//declare child vars
void typecheck_function(FILE* symfile, astree* node, symstack* symbol_stack, symtable* symbol_table)
{

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
		case '{':
		case '}':
		case '[':
		case ']':
		case ';':      break;

		case TOK_RETURN: break;
		case TOK_RETURNVOID: break;
		case TOK_PARAM:  break;


		case TOK_NEW:
		    left=node->children[0];
			for (i=0;i<15;i++)
			{
				node->attr[i]=left->attr[i];
			}
			break;
		case TOK_TYPEID: {
			node->attr[attr_typeid]=1;
			break; }
		case TOK_DECLID:
		case TOK_FIELD: {
			node->attr[attr_field]=1;
			if (left!=nullptr)
			{
				left->attr[attr_field]=1;
				//give child type to parent
			}
			break; }
		case TOK_FUNCTION:
		case TOK_PROTOTYPE: 

		case TOK_CALL: {

			//finding symbols???

		}
		case TOK_CHAR:
		case TOK_INT:
		case TOK_BOOL
		case TOK_VOID: {
			node->attr[attr_void]=1;
			//left child?
			break;
		}
		case TOK_STRING:
		case TOK_ARRAY:
		case TOK_NEWARRAY: {
			left=node->children[0];
			for (i=0;i<7;i++)
			{
				node->attr[i]=left->attr[i];
			}
			node->attr[attr_array]=1;
			node->attr[attr_vreg]=1;

			break;
		}
		case TOK_VOID:
		case TOK_INDEX: {
			node->attr[attr_vaddr]=1;
			node->attr[attr_lval]=1;
			break; }
		case TOK_IDENT:
		case TOK_STRUCT:
			left=node->children[0];
			printhelp(node);
			fprintf(symfile, node->lexinfo.c_str() + " \" "+left->lexinfo.c_str()+" \"");
			left->attr[attr_struct]=1;
			insert_symbol(struct_table, left);
			right=node->children[1];
			while(right!=nullptr)
			{
				astree* leftchild=right->children[0];
				fprintf(symfile, leftchild->lexinfo.c_str());
				fprintf(symfile, right->loc.c_str());
				fprintf(symfile, "field {"+ left->lexinfo.c_str()+"}");
				if (search_table(struct_table, right) == search_table(struct_table, left))
				{
					fprintf(symfile, "struct "+right->lexinfo.c_str());
				}
				else
				{
					fprintf(symfile, right->lexinfo.c_str());
				}
			}
			break;
		case TOK_IF:
		case TOK_IFELSE:
		case TOK_WHILE:

		case '+':
		case '-': {
			node->attr[attr_int]=1;
			node->attr[attr_vreg]=1;
			// 2 children?
			break; }

		case '*':
		case '/':
		case '%': {
			node->attr[attr_int]=1;
			node->attr[attr_vreg]=1;
			// 2 children?
		}
		case '!': {
			node->attr[attr_bool]=1;
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
		case TOK_POS:
		case TOK_NEG:

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

			break;
	}
}
	