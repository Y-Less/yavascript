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
//  The Original Code is the yavascript development system - TKTry.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKTry.h"

#include "../../Message.h"
#include "../../CatchScope.h"

#include "../TLiteral.h"

Token &
	TKTry::
	STD(SyntaxHandler & sh)
{
	CatchScope *
		scope = NULL;
	// This adds a a try block to the tree
	// There are three types of try blocks:
	// 
	// try-catch
	// try-finally
	// try-catch-finally
	// 
	// catches have a n identifier too
	// which nicely differentiates between
	// the various types as it means we
	// will have:
	// 
	// try (Invalid)
	// try-finally
	// try-ident-catch
	// try-ident-catch-finally
	// 
	// This means we can easilly tell what
	// type it is simply by the number
	// of children.
	Add(sh.Statement(true));
	if (sh.GetCurrent().GetType() == TokenType::TK_catch)
	{
		// try-catch
		sh.Advance(TokenType::TK_catch);
		if (sh.GetCurrent().GetType() == TokenType::TO_BRACKET_O)
		{
			Token &
				ident = sh.Advance(TokenType::TO_BRACKET_O);
			if (ident.IsSymbol() || ident.IsReserved())
			{
				Add(ident);
				sh.Advance();
				try
				{
					scope = new CatchScope(&m_sSymbols.GetCurrent(), TL::G(ident).GetString());
					m_sSymbols.AddScope(*scope);
					m_scope = scope;
				}
				catch (std::exception e)
				{
					Message::Send(Message::OUT_OF_MEMORY);
				}
				TokenType::E_TYPE
					type = sh.GetCurrent().GetType();
				if (type != TokenType::TO_BRACKET_C)
				{
					sh.Advance(type);
					Message::Send(Message::EXPECTED_IDENTIFIER);
					delete &sh.Expression();
				}
			}
			else
			{
				Message::Send(Message::EXPECTED_TOKEN, "identifier");
				if (ident.GetType() != TokenType::TO_BRACKET_C)
				{
					delete &sh.Expression();
				}
			}
			sh.Advance(TokenType::TO_BRACKET_C);
		}
		else
		{
			sh.Advance(TokenType::TO_BRACKET_O);
		}
		Add(sh.Statement(true));
		if (scope)
		{
			m_sSymbols.EndScope();
		}
		if (sh.GetCurrent().GetType() == TokenType::TK_finally)
		{
			// try-catch-finally
			sh.Advance(TokenType::TK_finally);
			Add(sh.Statement(true));
		}
	}
	else
	{
		if (sh.GetCurrent().GetType() == TokenType::TK_finally)
		{
			// try-finally
			sh.Advance(TokenType::TK_finally);
			Add(sh.Statement(true));
		}
		else
		{
			// try
			// No catch or finally
			Message::Send(Message::INVALID_TRY);
		}
	}
	return *this;
}

std::ostream &
	TKTry::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKTry::
	Release(std::ostream & s) const
{
	DoLabel(s);
	// try must have braces
	switch (GetChildCount())
	{
		case 2:
		{
			// try-finally
			s << "try";
			Token &
				what = GetFirstChild();
			// Add braces
			if (what.GetType() == TokenType::TO_BRACE_O)
			{
				what.Release(s);
			}
			else
			{
				s << '{';
				what.Release(s);
				s << '}';
			}
			s << "finally";
			Token &
				final = GetChild(1);
			// Add braces
			if (final.GetType() == TokenType::TO_BRACE_O)
			{
				final.Release(s);
			}
			else
			{
				s << '{';
				final.Release(s);
				s << '}';
			}
			break;
		}
		case 3:
		{
			// try-catch
			s << "try";
			Token &
				what = GetFirstChild();
			// Add braces
			if (what.GetType() == TokenType::TO_BRACE_O)
			{
				what.Release(s);
			}
			else
			{
				s << '{';
				what.Release(s);
				s << '}';
			}
			s << "catch(";
			GetChild(1).Release(s);
			s << ')';
			Token &
				fail = GetChild(2);
			// Add braces
			if (fail.GetType() == TokenType::TO_BRACE_O)
			{
				fail.Release(s);
			}
			else
			{
				s << '{';
				fail.Release(s);
				s << '}';
			}
			break;
		}
		case 4:
		{
			// try-catch-finally
			s << "try";
			Token &
				what = GetFirstChild();
			// Add braces
			if (what.GetType() == TokenType::TO_BRACE_O)
			{
				what.Release(s);
			}
			else
			{
				s << '{';
				what.Release(s);
				s << '}';
			}
			s << "catch(";
			GetChild(1).Release(s);
			s << ')';
			Token &
				fail = GetChild(2);
			// Add braces
			if (fail.GetType() == TokenType::TO_BRACE_O)
			{
				fail.Release(s);
			}
			else
			{
				s << '{';
				fail.Release(s);
				s << '}';
			}
			s << "finally";
			Token &
				final = GetChild(3);
			// Add braces
			if (final.GetType() == TokenType::TO_BRACE_O)
			{
				final.Release(s);
			}
			else
			{
				s << '{';
				final.Release(s);
				s << '}';
			}
			break;
		}
	}
	return s;
}
