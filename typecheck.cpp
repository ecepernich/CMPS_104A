//Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 4: .sym file

//implementing figure 1 grammar




//upcoming switch statement for something

//declare child vars

	astree* left=nullptr;
	astree* right=nullptr;

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
		case TOK_ROOT:

		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case ';':

		case TOK_RETURN:
		case TOK_PARAM:


		case TOK_NEW:
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
			node->attr[attr_char]=1;
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
	