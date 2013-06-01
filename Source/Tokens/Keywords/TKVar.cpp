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
//  The Original Code is the yavascript development system - TKVar.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKVar.h"

#include "../../Message.h"
#include "../../Generator.h"
#include "../../StringCast.h"

#include "../TLiteral.h"

Token &
	TKVar::
	STD(SyntaxHandler & sh)
{
	// Call the handler and pass
	// the first token.
	Token &
		pass = sh.GetCurrent();
	sh.Advance();
	if (!DoVar(sh, &pass))
	{
		Message::Send(Message::IMPLICIT_EOS);
	}
	return *this;
}

bool
	TKVar::
	DoVar(SyntaxHandler & sh, Token * token)
{
	// This function does the actual
	// code for a var statement.
	// It's done in this way to allow
	// for easy parsing of for
	// statements.  They require
	// look-ahead which means they
	// need more tokens than usual
	// before knowing wether to call
	// var, by which time it's too
	// late for most statements.
	bool
		first = false;
	TokenType::E_TYPE
		type,
		last = TokenType::TT__NONE;
	for ( ; ; )
	{
		type = token->GetType();
		// var
		// Hack for jquery (as technically
		// 'undefined' is a variable).
		if (TokenType::IsSymbol(type) || TokenType::IsReserved(type))
		{
			// Got a symbol to set
			if (first)
			{
				sh.Advance();
			}
			// var a
			// Get what follows the symbol
			Token &
				ass = sh.GetCurrent();
			type = ass.GetType();
			// Add to the current symbol scope
			m_sSymbols.AddSymbol(TL::G(*token).GetString(), true);
			if (TokenType::IsAssignment(type))
			{
				// var a =
				if (type != TokenType::TO_ASSIGN)
				{
					// var a +=
					Message::Send(Message::INVALID_VAR_ASSIGNMENT);
				}
				// Add the assignment anyway
				// So we get the correct results
				// (or as close as possible).
				Add(ass);
				ass.Add(*token);
				sh.Advance();
				ass.Add(sh.Expression());
				type = sh.GetCurrent().GetType();
			}
			else
			{
				Add(*token);
			}
		}
		else
		{
			if (first)
			{
				if (last == TokenType::TO_COMMA || !sh.SkippedLine())
				{
					Message::Send(Message::EXPECTED_IDENTIFIER, SC::L(type));
				}
			}
			else
			{
				Message::Send(Message::EMPTY_VAR_LIST);
			}
			return type == TokenType::TT_EOS;
		}
		if (type != TokenType::TO_COMMA)
		{
			// NOT:
			// var a,
			if (type == TokenType::TT_EOS)
			{
				// var a;
				sh.EoS();
				return true;
			}
			else if (type == TokenType::TT__END || type == TokenType::TT__EOF)
			{
				return false;
			}
			else if (sh.SkippedLine())
			{
				// var a
				Message::Send(Message::IMPLICIT_EOS);
				return true;
			}
		}
		sh.Advance(TokenType::TO_COMMA);
		// Have been round the loop
		// at least once.
		first = true;
		token = &sh.GetCurrent();
		last = type;
	}
}

std::ostream &
	TKVar::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKVar::
	Release(std::ostream & s) const
{
	// Always need a space
	s << "var ";
	Token::Itter
		it = *this;
	bool
		comma = false;
	// Loop through all the entries
	while (it.HasNext())
	{
		Token &
			cur = it.Next();
		if (comma)
		{
			s << ',';
		}
		else
		{
			comma = true;
		}
		// Output this thing
		cur.Release(s);
	}
	return s;
}
