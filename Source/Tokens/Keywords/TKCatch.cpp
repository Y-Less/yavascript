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
//  The Original Code is the yavascript development system - TKCatch.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKCatch.h"

#include "../../Message.h"
#include "../../Generator.h"
#include "../../CatchScope.h"

#include "../TLiteral.h"

Token &
	TKCatch::
	STD(SyntaxHandler & sh)
{
	CatchScope *
		scope = NULL;
	// If this is called it's bad
	// The "try" handler should cover this
	// this being called means there was
	// no "try" before.
	Message::Send(Message::UNMATCHED_CATCH);
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
	Dispose();
	if (scope)
	{
		m_sSymbols.EndScope();
	}
	return Generator::Null();
}
