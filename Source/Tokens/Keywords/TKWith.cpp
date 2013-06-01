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
//  The Original Code is the yavascript development system - TKWith.cpp.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKWith.h"

#include "../../Message.h"
#include "../../WithScope.h"

#include "../TLiteral.h"

Token &
	TKWith::
	STD(SyntaxHandler & sh)
{
	Message::Send(Message::USE_WITH);
	// Get the thing we're using
	sh.Advance(TokenType::TO_BRACKET_O);
	if (sh.GetCurrent().GetType() == TokenType::TO_BRACKET_C)
	{
		// Expected an expression
		Message::Send(Message::EXPECTED_IDENTIFIER);
		// Delete the token
	}
	else
	{
		// Get the expression
		// in the brackets
		Token &
			expr = sh.Expression();
		Add(expr);
		TokenType::E_TYPE
			type = expr.GetType();
		// Check the type can be "withed"
		// i.e. check it's an identifier
		if (
			!(type == TokenType::TO_DOT ||
			type == TokenType::TO_SQUARE_O ||
			TokenType::IsSymbol(type) ||
			TokenType::IsReserved(type)))
		{
			// Nope, tell them
			Message::Send(Message::EXPECTED_LH);
		}
	}
	// Skip the close bracket
	sh.Advance(TokenType::TO_BRACKET_C);
	// Create a new with scope
	WithScope *
		scope;
	try
	{
		scope = new WithScope(&m_sSymbols.GetCurrent());
		m_scope = scope;
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	// Set as the current scope
	m_sSymbols.AddScope(*scope);
	// Add the associated statement
	Add(sh.Statement(true));
	m_sSymbols.EndScope();
	return *this;
}

std::ostream &
	TKWith::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKWith::
	Release(std::ostream & s) const
{
	DoLabel(s);
	s << "with(";
	GetFirstChild().Release(s);
	s << ')';
	GetChild(1).Release(s);
	return s;
}

bool
	TKWith::
	RequireSemicolon() const
{
	// An if only requires a semicolon
	// when it ends in an expression.
	// For example:
	// while (a) alert('hi');
	// requires a semicolon.
	// while (a) function m() {}
	// doesn't.
	Token &
		fb = GetChild(1);
	if (fb.IsStatement())
	{
		// See if the statement
		// child need a semicolon
		return fb.RequireSemicolon();
	}
	else
	{
		// All expressions should
		return true;
	}
}
