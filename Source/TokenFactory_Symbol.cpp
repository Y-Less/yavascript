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
//  The Original Code is the yavascript development system - TokenFactory_Symbol.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Tokens/Keywords/KeyList.h"
#include "Tokens/Globals/GlobList.h"
#include "Tokens/Reserves/ResList.h"

#include "Message.h"
#include "StringCast.h"
#include "Compiler.h"

#include <iostream>

// 
// This function uses a vast state machine to determine
// what symbol has been entered.  The simplest way to
// explain it is as a map (as that's essentially what it
// is).  Assume the following keywords:
// 
// if
// in
// for
// 
//                                   |
//                  ---------------START---------------
//                  |                      |          |
//      ------------i---------        -----f-----   OTHER
//      |           |        |        |         |     |
//   ---n---     ---f---   OTHER   ---or---   OTHER SYMBOL
//   |     |     |     |           |      |     |
// SPACE OTHER SPACE OTHER       SPACE  OTHER SYMBOL
//   |     |     |     |           |      |
// "in" SYMBOL "if" SYMBOL       "for" SYMBOL
// 
// Each tree node is a state in the table below, it's just
// a lot larger.  This allows us to assess symbols as the
// stream is read in without the need for backtracking in
// the case of keywords.  Minor backtracking is required
// for symbols as their length is unknown in advance.
// 
// If a symbol starts with a known keyword (e.g. "inf")
// then a warning is given that it may be a typo:
// 
// inf (a == 2)
// 
// It may not, but the warning is disabled by default.
// 

Token &
	TokenFactory::
	DoSymbol(unsigned char ch)
{
	// Get the position of the start of the symbol
	std::streampos
		pos = m_sCur->tellg();
	pos -= 1;
	// State of symbol determination
	E_STATE
		state = ES__NONE;
	// Current symbol type
	TokenType::E_TYPE
		type = TokenType::TT_SYMBOL;
	do
	{
		switch (state)
		{
			case ES__NONE: // ES_NONE
				switch (ch)
				{
					case 'A':
						if (CheckLetters("rray")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Array;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'B':
						if (CheckLetters("oolean")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Boolean;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'D':
						if (CheckLetters("ate")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Date;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'E':
						state = ES_E; // ES_E
						break;
					case 'F':
						if (CheckLetters("unction")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Function;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'M':
						if (CheckLetters("ath")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Math;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'N':
						if (CheckLetters("umber")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Number;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'O':
						if (CheckLetters("bject")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Object;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'R':
						state = ES_R; // ES_R
						break;
					case 'S':
						state = ES_S; // ES_S
						break;
					case 'T':
						if (CheckLetters("ypeError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_TypeError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'U':
						if (CheckLetters("RIError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_URIError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'a':
						if (CheckLetters("bstract")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_abstract;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'b':
						state = ES_b; // ES_b
						break;
					case 'c':
						state = ES_c; // ES_c
						break;
					case 'd':
						state = ES_d; // ES_d
						break;
					case 'e':
						state = ES_e; // ES_e
						break;
					case 'f':
						state = ES_f; // ES_f
						break;
					case 'g':
						if (CheckLetters("oto")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_goto;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'i':
						state = ES_i; // ES_i
						break;
					case 'l':
						if (CheckLetters("ong")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_long;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'n':
						state = ES_n; // ES_n
						break;
					case 'p':
						state = ES_p; // ES_p
						break;
					case 'r':
						if (CheckLetters("eturn")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_return;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 's':
						state = ES_s; // ES_s
						break;
					case 't':
						state = ES_t; // ES_t
						break;
					case 'u':
						if (CheckLetters("ndefined")) // Can only be this or unknown
						{
							// "undefined" is not a keyword but
							// is often used as one, we'll treat it
							// as one but warn them of the problems
							state = ES__DONE; // Mark as done
							type = TokenType::TK_undefined;
							Message::Send(Message::USED_UNDEFINED);
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'v':
						state = ES_v; // ES_v
						break;
					case 'w':
						state = ES_w; // ES_w
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_E: // ES_E
				switch (ch)
				{
					case 'r':
						if (CheckLetters("ror")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_Error;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'v':
						if (CheckLetters("alError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_EvalError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_R: // ES_R
				switch (ch)
				{
					case 'a':
						if (CheckLetters("ngeError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_RangeError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'e':
						state = ES_Re; // ES_Re
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_Re: // ES_Re
				switch (ch)
				{
					case 'f':
						if (CheckLetters("erenceError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_ReferenceError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'g':
						if (CheckLetters("Exp")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_RegExp;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_S: // ES_S
				switch (ch)
				{
					case 't':
						if (CheckLetters("ring")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_String;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'y':
						if (CheckLetters("ntaxError")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TG_SyntaxError;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_b: // ES_b
				switch (ch)
				{
					case 'o':
						if (CheckLetters("olean")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_boolean;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'r':
						if (CheckLetters("eak")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_break;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'y':
						if (CheckLetters("te")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_byte;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_c: // ES_c
				switch (ch)
				{
					case 'a':
						state = ES_ca; // ES_ca
						break;
					case 'h':
						if (CheckLetters("ar")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_char;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'l':
						if (CheckLetters("ass")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_class;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'o':
						if (CheckLetters("n")) // All possible symbols have these symbols
						{
							state = ES_con; // ES_con
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_ca: // ES_ca
				switch (ch)
				{
					case 's':
						if (CheckLetters("e")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_case;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 't':
						if (CheckLetters("ch")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_catch;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_con: // ES_con
				switch (ch)
				{
					case 's':
						if (CheckLetters("t")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_const;
							// SOME browsers implement this (at least FF)
							// but others don't (at least IE)
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 't':
						if (CheckLetters("inue")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_continue;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_d: // ES_d
				switch (ch)
				{
					case 'e':
						state = ES_de; // ES_de
						break;
					case 'o':
						state = ES_do; // ES_do
						type = TokenType::TK_do;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_de: // ES_de
				switch (ch)
				{
					case 'b':
						if (CheckLetters("ugger")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_debugger;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'f':
						if (CheckLetters("ault")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_default;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'l':
						if (CheckLetters("ete")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_delete;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_do: // ES_do
				switch (ch)
				{
					case 'u':
						if (CheckLetters("ble")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_double;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_e: // ES_e
				switch (ch)
				{
					case 'l':
						if (CheckLetters("se")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_else;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'n':
						if (CheckLetters("um")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_enum;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'v':
						if (CheckLetters("al")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_eval;
							// Bad Bad Bad
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'x':
						state = ES_ex; // ES_ex
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_ex: // ES_ex
				switch (ch)
				{
					case 'p':
						if (CheckLetters("ort")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_export;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 't':
						if (CheckLetters("ends")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_extends;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_f: // ES_f
				switch (ch)
				{
					case 'a':
						if (CheckLetters("lse")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_false;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'i':
						if (CheckLetters("nal")) // All possible symbols have these symbols
						{
							state = ES_final; // ES_final
							type = TokenType::TR_final;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'l':
						if (CheckLetters("oat")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_float;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'o':
						if (CheckLetters("r")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_for;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'u':
						if (CheckLetters("nction")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_function;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_final: // ES_final
				switch (ch)
				{
					case 'l':
						if (CheckLetters("y")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_finally;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_i: // ES_i
				switch (ch)
				{
					case 'f':
						state = ES__DONE; // Mark as done
						type = TokenType::TK_if;
						break;
					case 'm':
						if (CheckLetters("p")) // All possible symbols have these symbols
						{
							state = ES_imp; // ES_imp
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'n':
						state = ES_in; // ES_in
						type = TokenType::TK_in;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_imp: // ES_imp
				switch (ch)
				{
					case 'l':
						if (CheckLetters("ements")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_implements;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'o':
						if (CheckLetters("rt")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_import;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_in: // ES_in
				switch (ch)
				{
					case 's':
						if (CheckLetters("tanceof")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_instanceof;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 't':
						state = ES_int; // ES_int
						type = TokenType::TR_int;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_int: // ES_int
				switch (ch)
				{
					case 'e':
						if (CheckLetters("rface")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_interface;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_n: // ES_n
				switch (ch)
				{
					case 'a':
						if (CheckLetters("tive")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_native;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'e':
						if (CheckLetters("w")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_new;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'u':
						if (CheckLetters("ll")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_null;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_p: // ES_p
				switch (ch)
				{
					case 'a':
						if (CheckLetters("ckage")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_package;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'r':
						state = ES_pr; // ES_pr
						break;
					case 'u':
						if (CheckLetters("blic")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_public;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_pr: // ES_pr
				switch (ch)
				{
					case 'i':
						if (CheckLetters("vate")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_private;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'o':
						if (CheckLetters("tected")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_protected;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_s: // ES_s
				switch (ch)
				{
					case 'h':
						if (CheckLetters("ort")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_short;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 't':
						if (CheckLetters("atic")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_static;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'u':
						if (CheckLetters("per")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_super;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'w':
						if (CheckLetters("itch")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_switch;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'y':
						if (CheckLetters("nchronized")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_synchronized;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_t: // ES_t
				switch (ch)
				{
					case 'h':
						state = ES_th; // ES_th
						break;
					case 'r':
						state = ES_tr; // ES_tr
						break;
					case 'y':
						if (CheckLetters("peof")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_typeof;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_th: // ES_th
				switch (ch)
				{
					case 'i':
						if (CheckLetters("s")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							//type = TokenType::TT_THIS; // Special case, "this" keyword
							//value.keyword = SymbolType::EK_this; // Only needed for the check below
							type = TokenType::TK_this;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'r':
						if (CheckLetters("ow")) // All possible symbols have these symbols
						{
							state = ES_throw; // ES_throw
							type = TokenType::TK_throw;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_throw: // ES_throw
				switch (ch)
				{
					case 's':
						state = ES__DONE; // Mark as done
						type = TokenType::TR_throws;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_tr: // ES_tr
				switch (ch)
				{
					case 'a':
						if (CheckLetters("nsient")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_transient;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'u':
						if (CheckLetters("e")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_true;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'y':
						state = ES__DONE; // Mark as done
						type = TokenType::TK_try;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_v: // ES_v
				switch (ch)
				{
					case 'a':
						if (CheckLetters("r")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_var;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'o':
						state = ES_vo; // ES_vo
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_vo: // ES_vo
				switch (ch)
				{
					case 'i':
						if (CheckLetters("d")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_void;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'l':
						if (CheckLetters("atile")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TR_volatile;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_w: // ES_w
				switch (ch)
				{
					case 'h':
						if (CheckLetters("ile")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_while;
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					case 'i':
						if (CheckLetters("th")) // Can only be this or unknown
						{
							state = ES__DONE; // Mark as done
							type = TokenType::TK_with;
							// Bad Bad Bad
						}
						else
						{
							state = ES__UNKNOWN; // Mark as unknown
						}
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES__DONE:
				// If it's done that means there's no longer known
				// word that it can be, so if we get another char
				// then it's a custom symbol that starts out the
				// same as a regular symbol
				Message::Send(Message::POSSIBLY_AMBIGUOUS);
				state = ES__UNKNOWN;
				break;
			case ES__UNKNOWN:
				// Do nothing, we're just collecting data
				break;
			default:
				Message::Send(Message::UNKNOWN_STATE);
				state = ES__UNKNOWN;
				break;
		}
		ch = Read();
		// Check IsSym and IsDec as now they're both
		// valid symbol characters
	}
	while (IsSym(ch) || IsDec(ch));
	if (state == ES__UNKNOWN || type == TokenType::TT_SYMBOL)
	{
		// Technically not "unknown"
		// Just a new custom symbol
		// Found a new token
		std::streampos
			len;
		if (!ch)
		{
			// At the end of the file
			m_sCur->clear();
			len = 1;
		}
		else
		{
			len = 0;
		}
		len += m_sCur->tellg();
		len -= pos;
		// Include NULL in allocation
		// Use alloca because we only need this
		// temporarilly and it's easy to handle
		// no need to remember to delete the
		// memory on function exit or exception
		char *
			c = (char *)alloca(len);
		if (c)
		{
			// Get the start of the symbol and read
			m_sCur->seekg(pos);
			len -= 1;
			m_sCur->read(c, len);
			c[len] = '\0';
			Preprocessor &
				pp = Compiler::Get().GetPreprocessor();
			// Check if this is a macro
			if (pp.Defined(c))
			{
				// Yes
				m_altIn.push(pp.Get(c));
				return GetNext();
			}
			if (m_sCur->bad())
			{
				// Error reading
				Message::Send(Message::INPUT_STREAM_ERROR);
			}
			else
			{
				// Read, save token
				return Create(c, TokenType::TT_SYMBOL);
			}
		}
		else
		{
			m_sCur->unget();
			Message::Send(Message::OUT_OF_MEMORY);
		}
		// Something went wrong
		// Compile should fail
		return Create(TokenType::TT__NONE);
	}
	else
	{
		// Found an existing known token
		if (TokenType::IsReserved(type) && type != TokenType::TK_undefined)
		{
			// Using a reserved word, may conflict in future
			Message::Send(Message::USED_RESERVE, SC::L(type));
		}
		// Return a character to the stream
		m_sCur->unget();
		return Create(type);
	}
}

Token *
	TokenFactory::
	CreateKeyword(const TokenType::E_TYPE type)
{
	switch (type)
	{
		case TokenType::TK_break:
			return new TKBreak();
		case TokenType::TK_case:
			return new TKCase();
		case TokenType::TK_catch:
			return new TKCatch();
		case TokenType::TK_continue:
			return new TKContinue();
		case TokenType::TK_default:
			return new TKDefault();
		case TokenType::TK_delete:
			return new TKDelete();
		case TokenType::TK_do:
			return new TKDo();
		case TokenType::TK_else:
			return new TKElse();
		case TokenType::TK_eval:
			return new TKEval();
		case TokenType::TK_false:
			return new TKFalse();
		case TokenType::TK_finally:
			return new TKFinally();
		case TokenType::TK_for:
			return new TKFor();
		case TokenType::TK_function:
			return new TKFunction();
		case TokenType::TK_if:
			return new TKIf();
		case TokenType::TK_in:
			return new TKIn();
		case TokenType::TK_instanceof:
			return new TKInstanceof();
		case TokenType::TK_new:
			return new TKNew();
		case TokenType::TK_null:
			return new TKNull();
		case TokenType::TK_return:
			return new TKReturn();
		case TokenType::TK_switch:
			return new TKSwitch();
		case TokenType::TK_this:
			return new TKThis();
		case TokenType::TK_throw:
			return new TKThrow();
		case TokenType::TK_true:
			return new TKTrue();
		case TokenType::TK_try:
			return new TKTry();
		case TokenType::TK_typeof:
			return new TKTypeof();
		case TokenType::TK_undefined:
			return new TKUndefined();
		case TokenType::TK_var:
			return new TKVar();
		case TokenType::TK_void:
			return new TKVoid();
		case TokenType::TK_while:
			return new TKWhile();
		case TokenType::TK_with:
			return new TKWith();
		default:
			// TODO: Warning
			return new TKeyword(type);
	}
}

Token *
	TokenFactory::
	CreateReserve(const TokenType::E_TYPE type)
{
	switch (type)
	{
		case TokenType::TR_abstract:
			return new TRAbstract();
		case TokenType::TR_boolean:
			return new TRBoolean();
		case TokenType::TR_byte:
			return new TRByte();
		case TokenType::TR_char:
			return new TRChar();
		case TokenType::TR_class:
			return new TRClass();
		case TokenType::TR_const:
			return new TRConst();
		case TokenType::TR_debugger:
			return new TRDebugger();
		case TokenType::TR_double:
			return new TRDouble();
		case TokenType::TR_enum:
			return new TREnum();
		case TokenType::TR_export:
			return new TRExport();
		case TokenType::TR_extends:
			return new TRExtends();
		case TokenType::TR_final:
			return new TRFinal();
		case TokenType::TR_float:
			return new TRFloat();
		case TokenType::TR_goto:
			return new TRGoto();
		case TokenType::TR_implements:
			return new TRImplements();
		case TokenType::TR_import:
			return new TRImport();
		case TokenType::TR_int:
			return new TRInt();
		case TokenType::TR_interface:
			return new TRInterface();
		case TokenType::TR_long:
			return new TRLong();
		case TokenType::TR_native:
			return new TRNative();
		case TokenType::TR_package:
			return new TRPackage();
		case TokenType::TR_private:
			return new TRPrivate();
		case TokenType::TR_protected:
			return new TRProtected();
		case TokenType::TR_public:
			return new TRPublic();
		case TokenType::TR_short:
			return new TRShort();
		case TokenType::TR_static:
			return new TRStatic();
		case TokenType::TR_super:
			return new TRSuper();
		case TokenType::TR_synchronized:
			return new TRSynchronized();
		case TokenType::TR_throws:
			return new TRThrows();
		case TokenType::TR_transient:
			return new TRTransient();
		case TokenType::TR_volatile:
			return new TRVolatile();
		default:
			// TODO: Warning
			return new TReserve(type);
	}
}

Token *
	TokenFactory::
	CreateGlobal(const TokenType::E_TYPE type)
{
	switch (type)
	{
		case TokenType::TG_Array:
			return new TGArray();
		case TokenType::TG_Boolean:
			return new TGBoolean();
		case TokenType::TG_Date:
			return new TGDate();
		case TokenType::TG_Error:
			return new TGError();
		case TokenType::TG_EvalError:
			return new TGEvalError();
		case TokenType::TG_Function:
			return new TGFunction();
		case TokenType::TG_Math:
			return new TGMath();
		case TokenType::TG_Number:
			return new TGNumber();
		case TokenType::TG_Object:
			return new TGObject();
		case TokenType::TG_RangeError:
			return new TGRangeError();
		case TokenType::TG_ReferenceError:
			return new TGReferenceError();
		case TokenType::TG_RegExp:
			return new TGRegExp();
		case TokenType::TG_String:
			return new TGString();
		case TokenType::TG_SyntaxError:
			return new TGSyntaxError();
		case TokenType::TG_TypeError:
			return new TGTypeError();
		case TokenType::TG_URIError:
			return new TGURIError();
		default:
			// TODO: Warning
			return new TGlobal(type);
	}
}
