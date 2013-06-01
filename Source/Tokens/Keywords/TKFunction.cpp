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
//  The Original Code is the yavascript development system - TKFunction.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKFunction.h"

#include "../TLiteral.h"

#include "../../LocalScope.h"
#include "../../Message.h"
#include "../../StringCast.h"

#include <exception>
#include <iostream>

std::ostream &
	TKFunction::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

bool
	TKFunction::
	RequireSemicolon() const
{
	// Don't need them on statements
	return GetChildCount() != 3;
}

std::ostream &
	TKFunction::
	Release(std::ostream & s) const
{
	// Add keyword
	s << "function";
	int
		c = GetChildCount();
	if (c == 3)
	{
		// Should be an identifier
		// so will need a space.
		s << ' ';
		// Add function name
		GetFirstChild().Release(s);
	}
	// Add parameters
	s << '(';
	bool
		comma = false;
	Token::Itter
		itter = GetChild(c - 2);
	while (itter.HasNext())
	{
		if (comma)
		{
			s << ',';
		}
		else
		{
			comma = true;
		}
		itter.Next().Release(s);
	}
	s << ')';
	// Add stuff
	if (GetChild(c - 1).GetType() == TokenType::TO_BRACE_O)
	{
		GetChild(c - 1).Release(s);
	}
	else
	{
		// Functions must have braces
		// Well, they should do, at
		// least FireFox doesn't
		// require them, others may
		// not too, but Internet
		// Explorer does.  Technically
		// IE is correct FF is wrong!
		s << '{';
		GetChild(c - 1).Release(s);
		// No trailing semicolon
		s << '}';
	}
	return s;
}

Token &
	TKFunction::
	STD(SyntaxHandler & sh)
{
	m_stmt = true;
	// TODO: Determine the different
	// function types.
	// function a() {}
	// is a valid statement AND
	// an expression.
	// function () {} is only an
	// expression.
	// This is a statement function
	// HasEffect is very useful
	// for that.
	Token &
		ret = NUD(sh);
	if (sh.GetCurrent().GetType() == TokenType::TO_BRACKET_O)
	{
		Message::Send(Message::INVALID_CALL);
	}
	// Functions may or may not have semicolons
	// they are pretty much the only thing
	// that missing them from is acceptable for.
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	if (
		type == TokenType::TT_EOS ||
		(!sh.SkippedLine() &&
		type != TokenType::TT__END &&
		type != TokenType::TT__EOF))
	{
		sh.EoS();
	}
	return ret;
}

bool
	TKFunction::
	IsStatement() const
{
	// Currently the only place
	// the return value of
	// IsStatement is variable.
	// When it's called initially
	// the return is true because
	// "function" can be parsed as
	// a statement or an expression.
	// when it's called subsequently
	// how it was initially declared
	// determines wether it's a
	// statement function or an
	// expression function.
	if  (GetChildCount())
	{
		// Has children -
		// already parsed as
		// an expression or
		// statement.
		return m_stmt;
	}
	// Done this way so that:
	// a = function(){}()
	// Is valid syntax, while:
	// function(){}()
	// isn't
	return true;
}

Token &
	TKFunction::
	NUD(SyntaxHandler & sh)
{
	Token *
		cur = &sh.GetCurrent();
	TokenType::E_TYPE
		type = cur->GetType();
	if (TokenType::IsSymbol(type) || TokenType::IsReserved(type))
	{
		// Function declaration
		// function a() {}
		// Add this function to the
		// current scope (not the
		// scope of this function)
		m_sSymbols.AddSymbol(TL::G(*cur).GetString(), true, true);
		Add(*cur);
		cur = &sh.Advance();
	}
	// Create a new local scope
	LocalScope *
		scope;
	try
	{
		scope = new LocalScope(&m_sSymbols.GetCurrent());
		m_scope = scope;
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	// Set as the current scope
	m_sSymbols.AddScope(*scope);
	if (cur->GetType() != TokenType::TO_BRACKET_O)
	{
		Message::Send(Message::EXPECTED_TOKEN, "(");
	}
	type = sh.Advance().GetType();
	// Add the parameter list
	Add(*cur);
	// Do parameters
	if (type != TokenType::TO_BRACKET_C)
	{
		// Has parameters
		for ( ; ; )
		{
			if (type == TokenType::TT__END || type == TokenType::TT__EOF)
			{
				Message::Send(Message::UNEXPECTED_EOF);
				return *this;
			}
			else if (TokenType::IsSymbol(type) || TokenType::IsReserved(type))
			{
				// Parameter
				// Add the parameter
				cur->Add(sh.GetCurrent());
				// Add the parameter to
				// the current scope
				m_sSymbols.AddSymbol(dynamic_cast<TLiteral *>(&sh.GetCurrent())->GetString(), true);
				// Check the next character
				type = sh.Advance().GetType();
				if (type == TokenType::TO_BRACKET_C)
				{
					// Valid list end
					break;
				}
				else if (type == TokenType::TT__END || type == TokenType::TT__EOF)
				{
					Message::Send(Message::UNEXPECTED_EOF);
					return *this;
				}
			}
			else
			{
				// Anything else
				Message::Send(Message::EXPECTED_IDENTIFIER);
				if (type == TokenType::TO_BRACKET_C)
				{
					// function (,)
					break;
				}
				sh.Advance();
			}
			type = sh.Advance(TokenType::TO_COMMA).GetType();
		}
	}
	// End the parameter list
	sh.Advance(TokenType::TO_BRACKET_C);
	Add(sh.Statement(true));
	m_sSymbols.EndScope();
	return *this;
}
