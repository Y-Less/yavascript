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
//  The Original Code is the yavascript development system - TOBracketO.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOBracketO.h"

#include "../../Message.h"
#include "../../Generator.h"

#include "../TLiteral.h"

Token &
	TOBracketO::
	LED(SyntaxHandler & sh, Token & left)
{
	// Function call
	const TokenType::E_TYPE
		type = left.GetType();
	if (type == TokenType::TO_BRACKET_O)
	{
		Token &
			cont = left.Pop();
		delete &left;
		if (cont.GetType() == TokenType::TK_function)
		{
			Token &
				ret = Generator::CIL(TokenType::TC_FUNC_CALL);
			ret.Add(cont);
			Dispose();
			Parameters(sh, ret);
			return ret;
		}
		else
		{
			Message::Send(Message::EXPECTED_FUNCTION);
		}
	}
	else if (type == TokenType::TK_function)
	{
		if (left.IsStatement())
		{
			// statement function declaration
			Message::Send(Message::INVALID_CALL);
		}
		else
		{
			// expression function declaration
			Token &
				ret = Generator::CIL(TokenType::TC_FUNC_CALL);
			ret.Add(left);
			Dispose();
			Parameters(sh, ret);
			return ret;
		}
	}
	/*else if (type == TokenType::TK_new)
	{
		Token &
			c = left.GetFirstChild();
		if (c.GetType() == TokenType::TG_Function)
		{
			Token &
				ret = Generator::CIL(TokenType::TC_FUNC_CALL);
			ret.Add(c);
			Dispose();
			Parameters(sh, ret);
			return ret;
		}
		else
		{
			Message::Send(Message::EXPECTED_FUNCTION);
		}
	}*/
	else if (
		TokenType::IsSymbol(type) ||
		TokenType::IsReserved(type))
	{
		Token &
			ret = Generator::CIL(TokenType::TC_FUNC_CALL);
		// Add the symbol use
		m_sSymbols.AddSymbol(TL::G(left).GetString(), false, true);
		ret.Add(left);
		Dispose();
		Parameters(sh, ret);
		return ret;
	}
	else if (
		TokenType::IsGlobal(type) ||
		type == TokenType::TO_DOT ||
		type == TokenType::TO_SQUARE_O)
	{
		Token &
			ret = Generator::CIL(TokenType::TC_FUNC_CALL);
		ret.Add(left);
		Dispose();
		Parameters(sh, ret);
		return ret;
	}
	/*else if (TokenType::IsPreproc(type))
	{
		// Preprocessor directive
		Token &
			pars = Generator::Null();
		Add(left);
		Parameters(sh, pars);
		Add(pars);
		Dispose();
		return dynamic_cast<TPreproc *>(&left)->Evaluate(pars);
	}*/
	else
	{
		// JS syntax is annoying!
		// You can do:
		// (a || b)();
		// as a valid function call!
		// Which makes invalid calls
		// next to impossible to detect!
		Token &
			ret = Generator::CIL(TokenType::TC_FUNC_CALL);
		ret.Add(left);
		Dispose();
		Parameters(sh, ret);
		// Don't worry about it for now
		return ret;
	}
	return *this;
}

void
	TOBracketO::
	Parameters(SyntaxHandler & sh, Token & parent)
{
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	// No parameters
	if (type == TokenType::TO_BRACKET_C)
	{
		sh.SetRegex(false);
		sh.Advance(TokenType::TO_BRACKET_C);
		return;
	}
	for ( ; ; )
	{
		if (type == TokenType::TO_COMMA)
		{
			Message::Send(Message::EXPECTED_RH);
		}
		else
		{
			parent.AddSymbols(sh, sh.Expression());
			type = sh.GetCurrent().GetType();
			if (type == TokenType::TT__END || type == TokenType::TT__EOF)
			{
				return;
			}
			else if (type == TokenType::TO_BRACKET_C)
			{
				sh.SetRegex(false);
				sh.Advance(TokenType::TO_BRACKET_C);
				return;
			}
		}
		sh.Advance(TokenType::TO_COMMA);
		type = sh.GetCurrent().GetType();
	}
}

Token &
	TOBracketO::
	NUD(SyntaxHandler & sh)
{
	// So I don't forget!
	if (sh.GetCurrent().GetType() == TokenType::TO_BRACKET_C)
	{
		Message::Send(Message::INVALID_EXPRESSION);
		sh.Advance();
		return *this;
	}
	Token &
		cont = sh.Expression(0);
	sh.SetRegex(false);
	sh.Advance(TokenType::TO_BRACKET_C);
	if (cont.IsAssignment() || cont.GetType() == TokenType::TK_function)
	{
		// Keep the brackets for now
		// this avoids warnings they're
		// obviously trying to avoid
		Add(cont);
		return *this;
	}
	else
	{
		if (cont.IsSymbol() || cont.IsReserved())
		{
			m_sSymbols.AddSymbol(TL::G(cont).GetString());
		}
		// Drop the brackets
		// This is a tree
		Dispose();
		return cont;
	}
}

std::ostream &
	TOBracketO::
	Debug(std::ostream & s) const
{
	// Start
	s << '(';
	GetFirstChild().Debug(s);
	// End
	s << ')';
	return s;
}

std::ostream &
	TOBracketO::
	Release(std::ostream & s) const
{
	// Start
	s << '(';
	GetFirstChild().Release(s);
	// End
	s << ')';
	return s;
}
