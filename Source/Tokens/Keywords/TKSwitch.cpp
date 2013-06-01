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
//  The Original Code is the yavascript development system - TKSwitch.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKSwitch.h"

#include "../../Message.h"
#include "../../StringCast.h"

Token &
	TKSwitch::
	STD(SyntaxHandler & sh)
{
	Conditional(sh);
	Statement(sh);
	return *this;
}

bool
	TKSwitch::
	Statement(SyntaxHandler & sh)
{
	// Switches must have braces
	TokenType::E_TYPE
		type = sh.Advance(TokenType::TO_BRACE_O).GetType();
	if (type == TokenType::TO_BRACE_C)
	{
		Message::Send(Message::EMPTY_SWITCH);
		sh.Advance(TokenType::TO_BRACE_C);
		return false;
	}
	else if (type == TokenType::TT_EOS)
	{
		Message::Send(Message::EMPTY_SWITCH);
		sh.EoS();
		return false;
	}
	bool
		def = false;
	for ( ; ; )
	{
		switch (type)
		{
			case TokenType::TO_BRACE_C:
				// Could warn them here if
				// they don't have a default
				// statement, but we won't.
				/*if (!def)
				{
					Message::Send(Message::NO_DEFAULT);
				}*/
				sh.Advance(TokenType::TO_BRACE_C);
				return true;
			case TokenType::TT__END:
			case TokenType::TT__EOF:
				Message::Send(Message::UNEXPECTED_EOF);
				return false;
			case TokenType::TK_case:
				// Add the case statement
				Add(DoCase(sh));
				break;
			case TokenType::TK_default:
				// Check for multiple defaults
				if (def)
				{
					Message::Send(Message::MULTI_DEFAULT);
					// Get rid of the second default
					delete &DoDefault(sh);
				}
				else
				{
					// Add the default statement
					Add(DoDefault(sh));
					// Mark as done default
					def = true;
				}
				break;
			default:
				Message::Send(Message::UNEXPECTED_TOKEN, SC::L(type));
				break;
		}
		type = sh.GetCurrent().GetType();
	}
}

Token &
	TKSwitch::
	DoCase(SyntaxHandler & sh)
{
	Token &
		token = sh.GetCurrent();
	Add(token);
	// Check for a case value
	if (sh.Advance().GetType() == TokenType::TO_COLON)
	{
		Message::Send(Message::EXPECTED_EXPRESSION);
	}
	else
	{
		token.Add(sh.Expression());
	}
	sh.Advance(TokenType::TO_COLON);
	// Add the statements to be executed
	DoStatements(sh, token);
	return token;
}

Token &
	TKSwitch::
	DoDefault(SyntaxHandler & sh)
{
	// Get the "default" token
	Token &
		token = sh.GetCurrent();
	Add(token);
	// Skip it and the colon
	sh.Advance();
	sh.Advance(TokenType::TO_COLON);
	// Add the statements to be executed
	DoStatements(sh, token);
	return token;
}

void
	TKSwitch::
	DoStatements(SyntaxHandler & sh, Token & token)
{
	// Collect all the statments
	// to be executed together.
	// Doesn't matter if this is
	// a "case" or "default",
	// they both work the same.
	TokenType::E_TYPE
		type;
	for ( ; ; )
	{
		type = sh.GetCurrent().GetType();
		switch (type)
		{
			// Collected in a switch
			// for simplicity.
			case TokenType::TK_case:
			case TokenType::TK_default:
			case TokenType::TO_BRACE_C:
			case TokenType::TT__END:
			case TokenType::TT__EOF:
				// Handle these above;
				return;
		}
		// Add the statements to the
		// current case/default.
		token.Add(sh.Statement());
	}
}

std::ostream &
	TKSwitch::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKSwitch::
	Release(std::ostream & s) const
{
	DoLabel(s);
	s << "switch(";
	// Thing to switch on
	GetFirstChild().Release(s);
	s << "){";
	Token::Itter
		cases = *this;
	// Skip the switch conditional
	cases.Next();
	bool
		semicolon = false;
	while (cases.HasNext())
	{
		// Don't put a semicolon
		// after the very last
		// statement in this
		// switch.
		if (semicolon)
		{
			s << ';';
		}
		semicolon = false;
		Token &
			cur = cases.Next();
		Token::Itter
			entries = cur;
		if (cur.GetType() == TokenType::TK_case)
		{
			s << "case";
			DoSpacePar(entries.Next(), s);
			s << ':';
		}
		else if (cur.GetType() == TokenType::TK_default)
		{
			s << "default:";
		}
		else
		{
			continue;
		}
		while (entries.HasNext())
		{
			if (semicolon)
			{
				s << ';';
			}
			Token &
				ent = entries.Next();
			ent.Release(s);
			if (ent.IsStatement())
			{
				// Some statements
				// need semicolons
				semicolon = ent.RequireSemicolon();
			}
			else
			{
				// All expressions
				// need semicolons
				semicolon = true;
			}
		}
	}
	s << '}';
	return s;
}
