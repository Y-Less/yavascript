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
//  The Original Code is the yavascript development system - TokenFactory_Operator.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Tokens/Operators/OpList.h"

#include "Message.h"
#include "StringCast.h"

Token &
	TokenFactory::
	DoOperator(unsigned char ch)
{
	// State of symbol determination
	E_STATE
		state = ES__NONE;
	// Current determined type
	TokenType::E_TYPE
		type = TokenType::TT__NONE;
	for ( ; ; )
	{
		switch (state)
		{
			case ES__NONE: // ES_NONE
				switch (ch)
				{
					case '!':
						state = ES_21; // ES_!
						type = TokenType::TO_NOT;
						break;
					case '%':
						state = ES_25; // ES_%
						type = TokenType::TO_MOD;
						break;
					case '&':
						state = ES_26; // ES_&
						type = TokenType::TO_BAND;
						break;
					case '(':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BRACKET_O;
						break;
					case ')':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BRACKET_C;
						break;
					case '*':
						state = ES_2A; // ES_*
						type = TokenType::TO_MUL;
						break;
					case '+':
						state = ES_2B; // ES_+
						type = TokenType::TO_ADD;
						break;
					case ',':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_COMMA;
						break;
					case '-':
						state = ES_2D; // ES_-
						type = TokenType::TO_SUB;
						break;
					case '.':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_DOT;
						break;
					case '/':
						state = ES_2F; // ES_/
						type = TokenType::TO_DIV;
						break;
					case ':':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_COLON;
						break;
					case '<':
						state = ES_3C; // ES_<
						type = TokenType::TO_LT;
						break;
					case '=':
						state = ES_3D; // ES_=
						type = TokenType::TO_ASSIGN;
						break;
					case '>':
						state = ES_3E; // ES_>
						type = TokenType::TO_GT;
						break;
					case '?':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_QUESTION;
						break;
					case '[':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_SQUARE_O;
						break;
					case ']':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_SQUARE_C;
						break;
					case '^':
						state = ES_5E; // ES_^
						type = TokenType::TO_XOR;
						break;
					case '{':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BRACE_O;
						break;
					case '|':
						state = ES_7C; // ES_|
						type = TokenType::TO_BOR;
						break;
					case '}':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BRACE_C;
						break;
					case '~':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_INV;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_21: // ES_!
				switch (ch)
				{
					case '=':
						state = ES_213D; // ES_!=
						type = TokenType::TO_NOT_CMP;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_213D: // ES_!=
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_NOT_EQUIV;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_25: // ES_%
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_MOD_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_26: // ES_&
				switch (ch)
				{
					case '&':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_LAND;
						break;
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BAND_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_2A: // ES_*
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_MUL_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_2B: // ES_+
				switch (ch)
				{
					case '+':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_INC;
						break;
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_ADD_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_2D: // ES_-
				switch (ch)
				{
					case '-':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_DEC;
						break;
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_SUB_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_2F: // ES_/
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_DIV_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3C: // ES_<
				switch (ch)
				{
					case '<':
						state = ES_3C3C; // ES_<<
						type = TokenType::TO_LS;
						break;
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_LTE;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3C3C: // ES_<<
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_LS_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3D: // ES_=
				switch (ch)
				{
					case '=':
						state = ES_3D3D; // ES_==
						type = TokenType::TO_COMPARE;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3D3D: // ES_==
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_EQUIV;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3E: // ES_>
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_GTE;
						break;
					case '>':
						state = ES_3E3E; // ES_>>
						type = TokenType::TO_RS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3E3E: // ES_>>
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_RS_ASS;
						break;
					case '>':
						state = ES_3E3E3E; // ES_>>>
						type = TokenType::TO_RSU;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_3E3E3E: // ES_>>>
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_RSU_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_5E: // ES_^
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_XOR_ASS;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			case ES_7C: // ES_|
				switch (ch)
				{
					case '=':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_BOR_ASS;
						break;
					case '|':
						state = ES__DONE; // Mark as done
						type = TokenType::TO_LOR;
						break;
					default:
						state = ES__UNKNOWN; // Mark as unknown
						break;
				}
				break;
			default:
				state = ES__UNKNOWN;
				break;
		}
		if (state == ES__UNKNOWN)
		{
			// Unget the last read token -
			// the one that didn't fit, e.g:
			// 
			// a+=-b;
			// 
			// Will be read as "+=-", "+=" will
			// be identified, but then "+=-" is
			// unknown, so put it back and stick
			// to the longest we could identify.
			// 
			// Note that the system KNOWS that
			// nothing can come after "+=" so it
			// will be "DONE" after those two, but
			// it was just a simple example (most
			// of the things that will get to here
			// will be syntax errors).
			if (type == TokenType::TT__NONE)
			{
				// Invalid token
				// Handle non-ASCII characters
				Message::Send(Message::INVALID_CHARACTER, SC::L(ch));
				// Ignore it and get the next character
				return GetNext();
			}
			m_sCur->unget();
			// Found a valid token
			return Create(type);
		}
		else if (state == ES__DONE)
		{
			// Definately have a token
			// otherwise it would be "unknown"
			return Create(type);
		}
		// We need to do this AFTER the
		// escape condition but NOT on the
		// first iteration, so it can't go
		// at the start of the loop
		ch = Read();
	}
}

Token *
	TokenFactory::
	CreateOperator(const TokenType::E_TYPE type)
{
	switch (type)
	{
		// Operators
		case TokenType::TO_NOT:			// !
			return new TONot();
		case TokenType::TO_NOT_CMP:		// !=
			return new TONotCmp();
		case TokenType::TO_NOT_EQUIV:	// !==
			return new TONotEquiv();
		case TokenType::TO_MOD:			// %
			return new TOMod();
		case TokenType::TO_MOD_ASS:		// %=
			return new TOModAss();
		case TokenType::TO_BAND:			// &
			return new TOBand();
		case TokenType::TO_LAND:			// &&
			return new TOLand();
		case TokenType::TO_BAND_ASS:		// &=
			return new TOBandAss();
		case TokenType::TO_BRACKET_O:	// (
			return new TOBracketO();
		case TokenType::TO_BRACKET_C:	// )
			return new TOBracketC();
		case TokenType::TO_MUL:			// *
			return new TOMul();
		case TokenType::TO_MUL_ASS:		// *=
			return new TOMulAss();
		case TokenType::TO_ADD:			// +
			return new TOAdd();
		case TokenType::TO_INC:			// ++
		case TokenType::TO_INC_PRE:		// ++val
		case TokenType::TO_INC_POST:		// val++
			return new TOInc();
		case TokenType::TO_ADD_ASS:		// +=
			return new TOAddAss();
		case TokenType::TO_COMMA:		// ,
			return new TOComma();
		case TokenType::TO_SUB:			// -
			return new TOSub();
		case TokenType::TO_DEC:			// --
		case TokenType::TO_DEC_PRE:		// --val
		case TokenType::TO_DEC_POST:		// val--
			return new TODec();
		case TokenType::TO_SUB_ASS:		// -=
			return new TOSubAss();
		case TokenType::TO_DOT:			// .
			return new TODot();
		case TokenType::TO_DIV:			// /
			return new TODiv();
		case TokenType::TO_DIV_ASS:		// /=
			return new TODivAss();
		case TokenType::TO_COLON:		// :
			return new TOColon();
		case TokenType::TO_LT:			// <
			return new TOLT();
		case TokenType::TO_LS:			// <<
			return new TOLS();
		case TokenType::TO_LS_ASS:		// <<=
			return new TOLSAss();
		case TokenType::TO_LTE:			// <=
			return new TOLTE();
		case TokenType::TO_ASSIGN:		// =
			return new TOAssign();
		case TokenType::TO_COMPARE:		// ==
			return new TOCompare();
		case TokenType::TO_EQUIV:		// ===
			return new TOEquiv();
		case TokenType::TO_GT:			// >
			return new TOGT();
		case TokenType::TO_GTE:			// >=
			return new TOGTE();
		case TokenType::TO_RS:			// >>
			return new TORS();
		case TokenType::TO_RS_ASS:		// >>=
			return new TORSAss();
		case TokenType::TO_RSU:			// >>>
			return new TORSU();
		case TokenType::TO_RSU_ASS:		// >>>=
			return new TORSUAss();
		case TokenType::TO_QUESTION:		// ?
			return new TOQuestion();
		case TokenType::TO_SQUARE_O:		// [
			return new TOSquareO();
		case TokenType::TO_SQUARE_C:		// ]
			return new TOSquareC();
		case TokenType::TO_XOR:			// ^
			return new TOXor();
		case TokenType::TO_XOR_ASS:		// ^=
			return new TOXorAss();
		case TokenType::TO_BRACE_O:		// {
			return new TOBraceO();
		case TokenType::TO_BOR:			// |
			return new TOBor();
		case TokenType::TO_BOR_ASS:		// |=
			return new TOBorAss();
		case TokenType::TO_LOR:			// ||
			return new TOLor();
		case TokenType::TO_BRACE_C:		// }
			return new TOBraceC();
		case TokenType::TO_INV:			// ~
			return new TOInv();
		default:
			// TODO: Warning
			Message::Send(Message::UNKNOWN_TYPE_CREATION, SC::L(type));
			return new TOperator(type);
	}
	//return new TOperator(type);
}
