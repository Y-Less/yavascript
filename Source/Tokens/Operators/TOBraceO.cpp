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
//  The Original Code is the yavascript development system - TOBraceO.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOBraceO.h"

#include "../../Generator.h"
#include "../../Message.h"

Token &
	TOBraceO::
	STD(SyntaxHandler & sh)
{
	// Group of statements
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	while (
		type != TokenType::TO_BRACE_C &&
		type != TokenType::TT__EOF &&
		type != TokenType::TT__END
		)
	{
		Add(sh.Statement());
		type = sh.GetCurrent().GetType();
	}
	if (GetChildCount() == 1)
	{
		// Don't need braces around
		// single statements
		// If this is for a function
		// the function handler can
		// sort that out.
		Dispose();
		// Remove and return the first
		// (only) child.  If it's not
		// removed it'll be destroyed
		// along with this token.
		return Pop();
	}
	return *this;
}

Token &
	TOBraceO::
	NUD(SyntaxHandler & sh)
{
	// Declaring an object
	// This can't be confused with STD
	// The ECMA standard defines an object
	// literal as no being allowed to be
	// the first thing in a statement.
	// However:
	// ({a:0}).a = 1;
	// is fine and possible here.
	// Don't actually need this token
	// don't want to get confused with
	// a group statement, they both have
	// variable numbers of children.
	Dispose();
	Token &
		ret = Generator::CIL(TokenType::TC_OBJECT);
	Token *
		sym = &sh.GetCurrent();
	TokenType::E_TYPE
		type = sym->GetType();
	if (sym->GetType() == TokenType::TO_BRACE_C)
	{
		sh.Advance(TokenType::TO_BRACE_C);
		return ret;
	}
	for ( ; ; )
	{
		if (
			TokenType::IsSymbol(type) ||
			TokenType::IsReserved(type) ||
			TokenType::IsNumber(type) ||
			TokenType::IsString(type))
		{
			// Fine identifier
			Token &
				colon = sh.Advance();
			if (colon.GetType() == TokenType::TO_COLON)
			{
				sh.Advance();
				// Identifier and colon
				// Add the name
				colon.Add(*sym);
				// Add the value
				type = sh.GetCurrent().GetType();
				if (type == TokenType::TO_COMMA || type == TokenType::TO_BRACE_C)
				{
					delete &colon;
					Message::Send(Message::EXPECTED_RH);
				}
				else if (type == TokenType::TT__END || type == TokenType::TT__EOF)
				{
					return ret;
				}
				else
				{
					colon.AddSymbols(sh, sh.Expression());
					// Add the group
					ret.Add(colon);
				}
			}
			else
			{
				Message::Send(Message::EXPECTED_TOKEN, ":");
			}
		}
		else
		{
			Message::Send(Message::INVALID_IDENTIFIER);
		}
		type = sh.GetCurrent().GetType();
		if (type == TokenType::TO_BRACE_C)
		{
			sh.Advance(TokenType::TO_BRACE_C);
			return ret;
		}
		else if (type == TokenType::TT__EOF || type == TokenType::TT__END)
		{
			Message::Send(Message::UNEXPECTED_EOF);
			return ret;
		}
		sym = &sh.Advance(TokenType::TO_COMMA);
		type = sym->GetType();
	}
	return ret;
}

std::ostream &
	TOBraceO::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TOBraceO::
	Release(std::ostream & s) const
{
	DoLabel(s);
	s << '{';
	Token::Itter
		t = *this;
	bool
		semi = false;
	while (t.HasNext())
	{
		if (semi)
		{
			s << ';';
		}
		Token &
			cur = t.Next();
		cur.Release(s);
		// Should put in a
		// semicolon
		if (cur.IsStatement())
		{
			// Some statements
			// need semicolons
			semi = cur.RequireSemicolon();
		}
		else
		{
			// All expressions
			// need semicolons
			semi = true;
		}
	}
	s << '}';
	return s;
}
