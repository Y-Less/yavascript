// ========================================================================= 
//  The contents of this file are subject to the Mozilla Public License      
//  Version 1.1 (the "License"); you may not use this file except in         
//  compliance with the License. You may obtain a copy of the License at     
//  http://www.mozilla.org/MPL/                                              
//                                                                           
//  Software distributed under the License is distributed on an "AS IS"      
//  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the  
//  License for the specific language governing rights and limitations       
//  under the License.                                                       
//                                                                           
//  The Original Code is the yavascript development system - TokenType.h.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <ostream>

class TokenType
{
public:
	enum E_TYPE
	{
		// Imaginary ones (ones which
		// don't exist in the stream
		// but are important)
		TT__NONE = 0,		// No known type
		// Initialise the first one as convention
		// not because it's needed, it's just
		// nice and explicit
		TT__EOF,			// End of file
		TT__END,			// Marks the complete end of the stream
		TT__FILE,			// Container for files
		
		// Standard types
		TT__TYPE_START,
			TT_EOL,				// End of line
			TT_EOS,				// End of statement
			TT_NUMBER,			// Number
			TT_STRING,			// String (of some form)
			TT_OPERATOR,		// Operator
			TT_SYMBOL,			// Symbol
			TT_REGEX,			// Regular expression
			TT_KEYWORD,			// Keywords
			TT_RESERVE,			// Reserved words
			TT_GLOBAL,			// Global objects
			TT_PREPROC,			// Pre-processor commands
		TT__TYPE_END,
		
		TT__OP_START,
			// Operators
			TO_NOT,			// !
			TO_NOT_CMP,		// !=
			TO_NOT_EQUIV,	// !==
			TO_MOD,			// %
			TO_BAND,		// &
			TO_LAND,		// &&
			TO_BRACKET_O,	// (
			TO_BRACKET_C,	// )
			TO_MUL,			// *
			TO_ADD,			// +
			TO_INC,			// ++
			TO_INC_PRE,		// ++val
			TO_INC_POST,	// val++
			TO_COMMA,		// ,
			TO_SUB,			// -
			TO_DEC,			// --
			TO_DEC_PRE,		// --val
			TO_DEC_POST,	// val--
			TO_DOT,			// .
			TO_DIV,			// /
			TO_COLON,		// :
			TO_LT,			// <
			TO_LS,			// <<
			TO_LTE,			// <=
			TO_COMPARE,		// ==
			TO_EQUIV,		// ===
			TO_GT,			// >
			TO_GTE,			// >=
			TO_RS,			// >>
			TO_RSU,			// >>>
			TO_QUESTION,	// ?
			TO_SQUARE_O,	// [
			TO_SQUARE_C,	// ]
			TO_XOR,			// ^
			TO_BRACE_O,		// {
			TO_BOR,			// |
			TO_LOR,			// ||
			TO_BRACE_C,		// }
			TO_INV,			// ~
			TT__ASS_START,
				TO_MOD_ASS,		// %=
				TO_BAND_ASS,	// &=
				TO_MUL_ASS,		// *=
				TO_ADD_ASS,		// +=
				TO_SUB_ASS,		// -=
				TO_DIV_ASS,		// /=
				TO_LS_ASS,		// <<=
				TO_ASSIGN,		// =
				TO_RS_ASS,		// >>=
				TO_RSU_ASS,		// >>>=
				TO_XOR_ASS,		// ^=
				TO_BOR_ASS,		// |=
			TT__ASS_END,
		TT__OP_END,
		
		// Keywords
		TT__KEY_START,
			TK_break,
			TK_case,
			TK_catch,
			TK_continue,
			TK_default,
			TK_delete,
			TK_do,
			TK_else,
			TK_eval,
			TK_finally,
			TK_for,
			TK_function,
			TK_if,
			TK_in,
			TK_instanceof,
			TK_new,
			TK_return,
			TK_switch,
			TK_this,
			TK_throw,
			TK_try,
			TK_typeof,
			TK_var,
			TK_void,
			TK_while,
			TK_with,
			TT__CONST_START,
				// Constant keywords
				TK_false,
				TK_null,
				TK_true,
			TT__CONST_END,
		// Reserved words
		TT__RES_START,
			// This is classed as
			// both a keyword and
			// a reserved word internally.
			TK_undefined,
		TT__KEY_END,
		
			TR_abstract,
			TR_boolean,
			TR_byte,
			TR_char,
			TR_class,
			TR_const,
			TR_debugger,
			TR_double,
			TR_enum,
			TR_export,
			TR_extends,
			TR_final,
			TR_float,
			TR_goto,
			TR_implements,
			TR_import,
			TR_int,
			TR_interface,
			TR_long,
			TR_native,
			TR_package,
			TR_private,
			TR_protected,
			TR_public,
			TR_short,
			TR_static,
			TR_super,
			TR_synchronized,
			TR_throws,
			TR_transient,
			TR_volatile,
		TT__RES_END,
		
		// Global objects
		TT__GLOB_START,
			TG_Array,
			TG_Boolean,
			TG_Date,
			TG_Error,
			TG_EvalError,
			TG_Function,
			TG_Math,
			TG_Number,
			TG_Object,
			TG_RangeError,
			TG_ReferenceError,
			TG_RegExp,
			TG_String,
			TG_SyntaxError,
			TG_TypeError,
			TG_URIError,
		TT__GLOB_END,
		
		// Additional CIL Types
		TT__CIL_START,
			TC_FUNC_CALL,
			TC_ARRAY,
			TC_OBJECT,
		TT__CIL_END,
		
		// ==============================
		//  If you add new types, please
		//  keep them in the designated
		//  sections for ease of coding
		// ==============================
		
		// Number of token types
		TT__MAX,
	};
	
	static bool
		IsRegex(const E_TYPE t)
	{
		return t == TT_REGEX;
	};
	
	// Check if the given token is a global token
	static bool
		IsGlobal(const E_TYPE t)
	{
		return t > TT__GLOB_START && t < TT__GLOB_END;
	};
	
	// Check if the given token is a keyword token
	static bool
		IsKeyword(const E_TYPE t)
	{
		return t > TT__KEY_START && t < TT__KEY_END;
	};
	
	// Check if the given token is a reserved token
	static bool
		IsReserved(const E_TYPE t)
	{
		return t > TT__RES_START && t < TT__RES_END;
	};
	
	// Check if the given token is an operator token
	static bool
		IsOperator(const E_TYPE t)
	{
		return t > TT__OP_START && t < TT__OP_END;
	};
	
	// Check if the given token is a symbol token
	static bool
		IsSymbol(const E_TYPE t)
	{
		return t == TT_SYMBOL;
	};
	
	static bool
		IsString(const E_TYPE t)
	{
		return t == TT_STRING;
	};
	
	static bool
		IsNumber(const E_TYPE t)
	{
		return t == TT_NUMBER;
	};
	
	static bool
		IsConstant(const E_TYPE t)
	{
		return t > TT__CONST_START && t < TT__CONST_END;
	};
	
	static bool
		IsAssignment(const E_TYPE t)
	{
		return t > TT__ASS_START && t < TT__ASS_END;
	};
	
	static bool
		IsCIL(const E_TYPE t)
	{
		return t > TT__CIL_START && t < TT__CIL_END;
	};
	
	friend std::ostream &
		operator<<(std::ostream &s, const E_TYPE t)
	{
		// Output a literal version of this token
		// Means we can just do, for example:
		// std::cout << TokenType::TT_REGEX;
		switch (t)
		{
			case TT__NONE:
			case TT__EOF:			// End of file
			case TT__END:			// Marks the complete end of the stream
				return s.flush();
			
			case TT__MAX:
				// Problem, this should never be
				// made to be printed!
				// TODO: Error!
				return s;
			
			// Standard types
			case TT_EOL:				// End of line
				return s << '\n';
			case TT_EOS:				// End of statement
				return s << ';';
			case TT_NUMBER:			// Number
				return s << "NUMBER";
			case TT_STRING:			// String (of some form)
				return s << "STRING";
			case TT_SYMBOL:			// Symbol
				return s << "SYMBOL";
			case TT_REGEX:			// Regular expression
				return s << "REGULAR EXPRESSION";
			
			// Operators
			case TO_NOT:			// !
				return s << '!';
			case TO_NOT_CMP:		// !=
				return s << "!=";
			case TO_NOT_EQUIV:		// !==
				return s << "!==";
			case TO_MOD:			// %
				return s << '%';
			case TO_MOD_ASS:		// %=
				return s << "%=";
			case TO_BAND:			// &
				return s << '&';
			case TO_LAND:			// &&
				return s << "&&";
			case TO_BAND_ASS:		// &=
				return s << "&=";
			case TO_BRACKET_O:		// (
				return s << '(';
			case TO_BRACKET_C:		// )
				return s << ')';
			case TO_MUL:			// *
				return s << '*';
			case TO_MUL_ASS:		// *=
				return s << "*=";
			case TO_ADD:			// +
				return s << '+';
			case TO_INC:			// ++
			case TO_INC_PRE:		// ++val
			case TO_INC_POST:		// val++
				return s << "++";
			case TO_ADD_ASS:		// +=
				return s << "+=";
			case TO_COMMA:		// ,
				return s << ',';
			case TO_SUB:			// -
				return s << '-';
			case TO_DEC:			// --
			case TO_DEC_PRE:		// --val
			case TO_DEC_POST:		// val--
				return s << "--";
			case TO_SUB_ASS:		// -=
				return s << "-=";
			case TO_DOT:			// .
				return s << '.';
			case TO_DIV:			// /
				return s << '/';
			case TO_DIV_ASS:		// /=
				return s << "/=";
			case TO_COLON:			// :
				return s << ':';
			case TO_LT:			// <
				return s << '<';
			case TO_LS:			// <<
				return s << "<<";
			case TO_LS_ASS:		// <<=
				return s << "<<=";
			case TO_LTE:			// <=
				return s << "<=";
			case TO_ASSIGN:		// =
				return s << '=';
			case TO_COMPARE:		// ==
				return s << "==";
			case TO_EQUIV:		// ===
				return s << "===";
			case TO_GT:			// >
				return s << '>';
			case TO_GTE:			// >=
				return s << ">=";
			case TO_RS:			// >>
				return s << ">>";
			case TO_RS_ASS:		// >>=
				return s << ">>=";
			case TO_RSU:			// >>>
				return s << ">>>";
			case TO_RSU_ASS:		// >>>=
				return s << ">>>=";
			case TO_QUESTION:		// ?
				return s << '?';
			case TO_SQUARE_O:		// [
				return s << '[';
			case TO_SQUARE_C:		// ]
				return s << ']';
			case TO_XOR:			// ^
				return s << '^';
			case TO_XOR_ASS:		// ^=
				return s << "^=";
			case TO_BRACE_O:		// {
				return s << '{';
			case TO_BOR:			// |
				return s << '|';
			case TO_BOR_ASS:		// |=
				return s << "|=";
			case TO_LOR:			// ||
				return s << "||";
			case TO_BRACE_C:		// }
				return s << '}';
			case TO_INV:			// ~
				return s << '~';
			
			// Keywords
			case TK_break:
				return s << "break";
			case TK_case:
				return s << "case";
			case TK_catch:
				return s << "catch";
			case TK_continue:
				return s << "continue";
			case TK_default:
				return s << "default";
			case TK_delete:
				return s << "delete";
			case TK_do:
				return s << "do";
			case TK_else:
				return s << "else";
			case TK_eval:
				return s << "eval";
			case TK_false:
				return s << "false";
			case TK_finally:
				return s << "finally";
			case TK_for:
				return s << "for";
			case TK_function:
				return s << "function";
			case TK_if:
				return s << "if";
			case TK_in:
				return s << "in";
			case TK_instanceof:
				return s << "instanceof";
			case TK_new:
				return s << "new";
			case TK_null:
				return s << "null";
			case TK_return:
				return s << "return";
			case TK_switch:
				return s << "switch";
			case TK_this:
				return s << "this";
			case TK_throw:
				return s << "throw";
			case TK_true:
				return s << "true";
			case TK_try:
				return s << "try";
			case TK_typeof:
				return s << "typeof";
			case TK_undefined:
				return s << "undefined";
			case TK_var:
				return s << "var";
			case TK_void:
				return s << "void";
			case TK_while:
				return s << "while";
			case TK_with:
				return s << "with";
			
			// Reserved words
			case TR_abstract:
				return s << "abstract";
			case TR_boolean:
				return s << "boolean";
			case TR_byte:
				return s << "byte";
			case TR_char:
				return s << "char";
			case TR_class:
				return s << "class";
			case TR_const:
				return s << "const";
			case TR_debugger:
				return s << "debugger";
			case TR_double:
				return s << "double";
			case TR_enum:
				return s << "enum";
			case TR_export:
				return s << "export";
			case TR_extends:
				return s << "extends";
			case TR_final:
				return s << "final";
			case TR_float:
				return s << "float";
			case TR_goto:
				return s << "goto";
			case TR_implements:
				return s << "implements";
			case TR_import:
				return s << "import";
			case TR_int:
				return s << "int";
			case TR_interface:
				return s << "interface";
			case TR_long:
				return s << "long";
			case TR_native:
				return s << "native";
			case TR_package:
				return s << "package";
			case TR_private:
				return s << "private";
			case TR_protected:
				return s << "protected";
			case TR_public:
				return s << "public";
			case TR_short:
				return s << "short";
			case TR_static:
				return s << "static";
			case TR_super:
				return s << "super";
			case TR_synchronized:
				return s << "synchronized";
			case TR_throws:
				return s << "throws";
			case TR_transient:
				return s << "transient";
			case TR_volatile:
				return s << "volatile";
			
			// Global objects
			case TG_Array:
				return s << "Array";
			case TG_Boolean:
				return s << "Boolean";
			case TG_Date:
				return s << "Date";
			case TG_Error:
				return s << "Error";
			case TG_EvalError:
				return s << "EvalError";
			case TG_Function:
				return s << "Function";
			case TG_Math:
				return s << "Math";
			case TG_Number:
				return s << "Number";
			case TG_Object:
				return s << "Object";
			case TG_RangeError:
				return s << "RangeError";
			case TG_ReferenceError:
				return s << "ReferenceError";
			case TG_RegExp:
				return s << "RegExp";
			case TG_String:
				return s << "String";
			case TG_SyntaxError:
				return s << "SyntaxError";
			case TG_TypeError:
				return s << "TypeError";
			case TG_URIError:
				return s << "URIError";
			default:
				return s;
		}
	};
};
