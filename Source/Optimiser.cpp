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
//  The Original Code is the yavascript development system - Optimiser.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Optimiser.h"

#include "Generator.h"
#include "Message.h"

#include "Tokens/Keywords/TKVar.h"
#include "Tokens/Keywords/TKFunction.h"
#include "Tokens/Operators/TONot.h"
#include "Tokens/Operators/TOComma.h"
#include "Tokens/Operators/TOBracketO.h"

#include <iostream>

// This function is the
// entry point for all
// optimisations.
Token &
	Optimiser::
	Do(Token & tree)
{
	Token
		* in = NULL,
		* ret = &tree;
	// Optimise a single scope
	// Should keep calling this
	// 
	// {
	//     return;
	//     alert('hi');
	// }
	// alert('there');
	// 
	// Will generate:
	// 
	// return;
	// alert('there');
	// 
	// Recalling the function will
	// optimise out the other alert.
	do
	{
		delete in;
		in = ret;
		ret = &Generator::File();
	}
	while (DoGroup(*in, *ret));
	delete in;
	return *ret;
}

bool
	Optimiser::
	DoGroup(Token & scope, Token & group)
{
	// Has the return been
	// modified from the input
	bool
		mod = false;
	Token::Itter
		itter = scope;
	Token &
		temp = Generator::Group();
	// Loop through the tokens
	// in the current scope
	while (itter.HasNext())
	{
		Token &
			cur = itter.Next();
		if (!IsVoid(cur))
		{
			// Drop void statements
			// by that I mean comletely
			// void ones...
			switch (cur.GetType())
			{
				case TokenType::TT__NONE:
				case TokenType::TT__EOF:			// End of file
				case TokenType::TT__END:			// Marks the complete end of the stream
					// Drop it
					// i.e. don't do anything
					mod = true;
					break;
				case TokenType::TT__FILE:			// Container for files
					// Add all the contents to this group
					DoGroup(cur, temp);
					mod = true;
					break;
				case TokenType::TT_EOL:				// End of line
				case TokenType::TT_EOS:				// End of statement
					mod = true;
					break;
				case TokenType::TT_NUMBER:			// Number
				case TokenType::TT_STRING:			// String (of some form)
				case TokenType::TT_OPERATOR:		// Operator
				case TokenType::TT_SYMBOL:			// Symbol
				case TokenType::TT_REGEX:			// Regular expression
				case TokenType::TT_KEYWORD:			// Keywords
				case TokenType::TT_RESERVE:			// Reserved words
				case TokenType::TT_GLOBAL:			// Global objects
				case TokenType::TT_PREPROC:			// Pre-processor commands
					// Nothing should have these types
					// Either it is a symbol/string etc,
					// in which case it's an empty
					// expression and can be ignored,
					// or it's actually of type
					// TT_OPERATOR or another one
					// which should never be
					// instantiated, either way it
					// should be dropped.
					mod = true;
					break;
				case TokenType::TO_NOT:			// !
				case TokenType::TO_INV:			// ~
					temp.Add(cur.Pop());
					mod = true;
					break;
				case TokenType::TO_NOT_CMP:		// !=
				case TokenType::TO_NOT_EQUIV:	// !==
				case TokenType::TO_MOD:			// %
				case TokenType::TO_BAND:		// &
				case TokenType::TO_LAND:		// &&
				case TokenType::TO_MUL:			// *
				case TokenType::TO_ADD:			// +
				case TokenType::TO_INC:			// ++
				case TokenType::TO_INC_PRE:		// ++val
				case TokenType::TO_INC_POST:	// val++
				case TokenType::TO_COMMA:		// ,
				case TokenType::TO_SUB:			// -
				case TokenType::TO_DEC:			// --
				case TokenType::TO_DEC_PRE:		// --val
				case TokenType::TO_DEC_POST:	// val--
				case TokenType::TO_DOT:			// .
				case TokenType::TO_DIV:			// /
				case TokenType::TO_LT:			// <
				case TokenType::TO_LS:			// <<
				case TokenType::TO_LTE:			// <=
				case TokenType::TO_COMPARE:		// ==
				case TokenType::TO_EQUIV:		// ===
				case TokenType::TO_GT:			// >
				case TokenType::TO_GTE:			// >=
				case TokenType::TO_RS:			// >>
				case TokenType::TO_RSU:			// >>>
				case TokenType::TO_QUESTION:	// ?
				case TokenType::TO_SQUARE_O:	// [
				case TokenType::TO_XOR:			// ^
				case TokenType::TO_BOR:			// |
				case TokenType::TO_LOR:			// ||
					// Should check children
					// These on their own are (mostly)
					// empty expressions, but:
					// a + b = c;
					// has a complete expression embedded
					temp.Add(cur);
					break;
				case TokenType::TO_BRACE_O:		// {
					// Random group
					DoGroup(cur, temp);
					mod = true;
					break;
				case TokenType::TO_COLON:		// :
				case TokenType::TO_BRACKET_O:	// (
				case TokenType::TO_BRACKET_C:	// )
				case TokenType::TO_SQUARE_C:	// ]
				case TokenType::TO_BRACE_C:		// }
					// Should not exist in the tree
					mod = true;
					break;
				case TokenType::TO_MOD_ASS:		// %=
				case TokenType::TO_BAND_ASS:	// &=
				case TokenType::TO_MUL_ASS:		// *=
				case TokenType::TO_ADD_ASS:		// +=
				case TokenType::TO_SUB_ASS:		// -=
				case TokenType::TO_DIV_ASS:		// /=
				case TokenType::TO_LS_ASS:		// <<=
				case TokenType::TO_RS_ASS:		// >>=
				case TokenType::TO_RSU_ASS:		// >>>=
				case TokenType::TO_XOR_ASS:		// ^=
				case TokenType::TO_BOR_ASS:		// |=
				case TokenType::TO_ASSIGN:		// =
					temp.Add(cur);
					break;
				/*case TokenType::TO_ASSIGN:		// =
				{
					// Convert:
					// a = function () {};
					// To:
					// function a() {}
					Token &
						func = cur.GetChild(1);
					if (func.GetType() == TokenType::TK_function)
					{
						if (func.GetChildCount() == 3)
						{
							// Already efficient
							// var a = function b() {};
							// Optimise the function's code
							Token
								* in = &func.GetChild(2);
							if (in->GetType() == TokenType::TO_BRACE_O)
							{
								Token
									* ret = &Generator::Group();
								// Do the initial check
								// this is to determine
								// mod status
								if (DoGroup(*in, *ret))
								{
									mod = true;
									// Continue as in Do()
									do
									{
										delete in;
										in = ret;
										ret = &Generator::Group();
									}
									while (DoGroup(*in, *ret));
								}
								// ~Token handles Remove()
								delete in;
								func.Add(*ret);
							}
						}
						else
						{
							// See above
							Token
								* in = &func.GetChild(1);
							if (in->GetType() == TokenType::TO_BRACE_O)
							{
								Token
									* ret = &Generator::Group();
								if (DoGroup(*in, *ret))
								{
									mod = true;
									do
									{
										delete in;
										in = ret;
										ret = &Generator::Group();
									}
									while (DoGroup(*in, *ret));
								}
								delete in;
								func.Add(*ret);
							}
							if (
								cur.GetFirstChild().IsSymbol() ||
								cur.GetFirstChild().IsReserved())
							{
								// Add the symbol as
								// the function name
								func.AddHead(cur.Pop());
								// Add the function statement
								temp.Add(cur.Pop());
								// Mark as a statement
								dynamic_cast<TKFunction *>(&func)->SetStatement();
								// Modified
								mod = true;
								break;
							}
						}
					}
					// Add the regular assignment
					temp.Add(cur);
					break;
				}*/
				case TokenType::TK_break:
				case TokenType::TK_continue:
				case TokenType::TK_return:
					// End scope
					// Anything after these can't
					// get run.
					temp.Add(cur);
					if (itter.HasNext())
					{
						// Dropped tokens from the end
						mod = true;
					}
					goto after;
				// LOADS of things can
				// be done in most of
				// these.
				case TokenType::TK_if:
					switch (cur.GetChildCount())
					{
						case 2:
						{
							// if
							// Stick the expression on the end
							cur.Add(cur.Pop());
							Token &
								val = cur.Pop();
							if (val.GetType() == TokenType::TO_BRACE_O || val.GetType() == TokenType::TT__FILE)
							{
								Token &
									g = Generator::Group();
								if (DoGroup(val, g))
								{
									mod = true;
								}
								delete &val;
								switch (g.GetChildCount())
								{
									case 0:
										delete &g;
										mod = true;
										break;
									case 1:
										cur.Add(g.Pop());
										temp.Add(cur);
										mod = true;
										delete &g;
										break;
									default:
										cur.Add(g);
										temp.Add(cur);
										break;
								}
							}
							else
							{
								cur.Add(val);
								temp.Add(cur);
							}
							break;
						}
						case 3:
						{
							// if-else
							Token &
								iexpr = cur.Pop();
							{
								// if
								Token &
									val = cur.Pop();
								if (val.GetType() == TokenType::TO_BRACE_O || val.GetType() == TokenType::TT__FILE)
								{
									Token &
										g = Generator::Group();
									if (DoGroup(val, g))
									{
										mod = true;
									}
									delete &val;
									switch (g.GetChildCount())
									{
										case 0:
										{
											Token *
												ret = NULL;
											try
											{
												ret = new TONot();
												// Invert the expression
												ret->Add(iexpr);
												cur.Add(*ret);
											}
											catch (std::exception e)
											{
												Message::Send(Message::OUT_OF_MEMORY);
											}
											delete &g;
											break;
										}
										case 1:
											cur.Add(iexpr);
											cur.Add(g.Pop());
											delete &g;
											break;
										default:
											// Add the expression
											// and the true statement
											cur.Add(iexpr);
											cur.Add(g);
											break;
									}
								}
								else
								{
									cur.Add(iexpr);
									cur.Add(val);
								}
							}
							{
								// else
								Token &
									val = cur.Pop();
								if (cur.GetChildCount())
								{
									if (val.GetType() == TokenType::TO_BRACE_O || val.GetType() == TokenType::TT__FILE)
									{
										Token &
											g = Generator::Group();
										if (DoGroup(val, g))
										{
											mod = true;
										}
										delete &val;
										switch (g.GetChildCount())
										{
											case 0:
												if (cur.GetChildCount() != 1)
												{
													temp.Add(cur);
												}
												delete &g;
												break;
											case 1:
												cur.Add(g.Pop());
												temp.Add(cur);
												delete &g;
												break;
											default:
												cur.Add(g);
												temp.Add(cur);
												break;
										}
									}
									else
									{
										cur.Add(val);
										temp.Add(cur);
									}
								}
								else
								{
									delete &val;
								}
							}
							break;
						}
						default:
							// nothing
							mod = true;
							break;
					}
					break;
				case TokenType::TK_var:
				{
					// Should combine vars together
					// Break out functions
					Token::Itter
						vitter = cur;
					while (vitter.HasNext())
					{
						Token &
							set = vitter.Next();
						// Convert
						// var a = function () {};
						// To:
						// function a() {}
						if (set.GetType() == TokenType::TO_ASSIGN)
						{
							Token &
								func = set.GetChild(1);
							if (func.GetType() == TokenType::TK_function)
							{
								// Add the symbol as
								// the function name
								func.AddHead(set.Pop());
								// Add the function statement
								// as it's own entry in the tree
								temp.Add(set.Pop());
								// Mark as a statement
								dynamic_cast<TKFunction *>(&func)->SetStatement();
								// Modified
								mod = true;
								// Remove what's left of
								// this assignment
								// Remove is safe in itterators
								cur.Remove(set);
								delete &set;
							}
						}
					}
					if (cur.HasChildren())
					{
						temp.Add(cur);
					}
					break;
				}
				case TokenType::TK_function:
				case TokenType::TK_for:
				{
					int
						count = cur.GetChildCount() - 1;
					// Should be 3 for a valid function statement
					Token
						* in = &cur.GetChild(count);
					if (in->GetType() == TokenType::TO_BRACE_O)
					{
						Token
							* ret = &Generator::Group();
						// Do the initial check
						// this is to determine
						// mod status
						if (DoGroup(*in, *ret))
						{
							mod = true;
							// Continue as in Do()
							do
							{
								delete in;
								in = ret;
								ret = &Generator::Group();
							}
							while (DoGroup(*in, *ret));
						}
						// ~Token handles Remove()
						delete in;
						if (ret->GetChildCount() == 1)
						{
							// For functions the output
							// will resolve the brace
							// requirement.
							cur.Add(ret->Pop());
							delete ret;
						}
						else
						{
							cur.Add(*ret);
						}
					}
					temp.Add(cur);
					break;
				}
				case TokenType::TK_delete:
				case TokenType::TK_do:
				case TokenType::TK_eval:
				case TokenType::TK_new:
				case TokenType::TK_switch:
				case TokenType::TK_throw:
				case TokenType::TK_try:
				case TokenType::TK_while:
				case TokenType::TK_with:
					temp.Add(cur);
					break;
				case TokenType::TK_void:
					// It's a complete statement
					// the value isn't used.
					temp.Add(cur.Pop());
					mod = true;
					break;
				case TokenType::TK_catch:
				case TokenType::TK_case:
				case TokenType::TK_else:
				case TokenType::TK_default:
				case TokenType::TK_finally:
				case TokenType::TK_in:
				case TokenType::TK_instanceof:
				case TokenType::TK_this:
				case TokenType::TK_typeof:
				case TokenType::TK_false:
				case TokenType::TK_null:
				case TokenType::TK_true:
					// Drop
					// These are all either wrong
					// or empty expressions
					mod = true;
					break;
				case TokenType::TC_ARRAY:
				case TokenType::TC_OBJECT:
					// Empty expression
					mod = true;
					break;
				case TokenType::TC_FUNC_CALL:
					// Can probably optimise this
					if (cur.GetFirstChild().GetType() == TokenType::TK_function)
					{
						Token *
							ret = NULL;
						try
						{
							ret = new TOBracketO();
						}
						catch (std::exception e)
						{
							Message::Send(Message::OUT_OF_MEMORY);
						}
						ret->Add(cur.GetFirstChild());
						cur.AddHead(*ret);
						mod = true;
					}
					temp.Add(cur);
					break;
			}
		}
	}
	after:
	// Do something based on
	// the number of tokens kept
	// from this group scope
	switch (temp.GetChildCount())
	{
		case 1:
			group.Add(temp.Pop());
			// Fallthrough
		case 0:
			delete &temp;
			return mod;
		default:
			Token::Itter
				expr = temp;
			bool
				statement = false;
			while (expr.HasNext())
			{
				// Got a statement in the
				// current things
				if (expr.Next().IsStatement())
				{
					statement = true;
					break;
				}
			}
			if (statement)
			{
				// Add all the items we added
				// to the temp group to the
				// main group.
				// Can't (easilly) optimise.
				// No point joining what
				// expressions there are as
				// there will still be the
				// brace overhead.
				while (temp.HasChildren())
				{
					group.Add(temp.Pop());
				}
			}
			else
			{
				Token *
					cur = &Comma();
				group.Add(*cur);
				mod = true;
				for ( ; ; )
				{
					// No statements, add everything
					// into a comma expression.
					switch (temp.GetChildCount())
					{
						case 2:
							cur->Add(temp.Pop());
							break;
						case 1:
							cur->Add(temp.Pop());
							// Fallthrough
						case 0:
							delete &temp;
							return mod;
						default:
							cur->Add(temp.Pop());
							Token &
								tmp = Comma();
							cur->Add(tmp);
							cur = &tmp;
					}
				}
			}
	}
	delete &temp;
	return mod;
}

Token &
	Optimiser::
	VarBlock()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TKVar();
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Optimiser::
	Comma()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TOComma();
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

bool
	Optimiser::
	IsVoid(Token & token)
{
	if (token.GetType() == TokenType::TK_void)
	{
		if (token.GetChildCount() == 1)
		{
			if (token.GetFirstChild().GetType() == TokenType::TT_NUMBER)
			{
				// One of the placeholders
				// we inserted.
				return true;
			}
		}
	}
	return false;
}
