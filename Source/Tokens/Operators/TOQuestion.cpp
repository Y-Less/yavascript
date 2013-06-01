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
//  The Original Code is the yavascript development system - TOQuestion.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOQuestion.h"

#include "../../Message.h"

Token &
	TOQuestion::
	LED(SyntaxHandler & sh, Token & left)
{
	Add(left);
	AddSymbols(sh, sh.Expression(10));
	if (sh.GetCurrent().GetType() == TokenType::TO_COLON)
	{
		sh.Advance(TokenType::TO_COLON);
		AddSymbols(sh, sh.Expression(10));
	}
	else
	{
		Message::Send(Message::EXPECTED_TOKEN, ":");
	}
	return *this;
}

std::ostream &
	TOQuestion::
	Release(std::ostream & s) const
{
	Token
		& left = GetFirstChild(),
		& middle = GetChild(1),
		& right = GetChild(2);
	// Output this operator
	if (RequireBrackets(left, false))
	{
		// The thing on the right
		// has children and a lower
		// lbp, meaning it needs
		// brackets.
		s << '(';
		left.Release(s);
		s << ')';
	}
	else
	{
		left.Release(s);
	}
	s << '?';
	if (RequireBrackets(middle, false))
	{
		s << '(';
		middle.Release(s);
		s << ')';
	}
	else
	{
		middle.Release(s);
	}
	s << ':';
	if (RequireBrackets(right, false))
	{
		s << '(';
		right.Release(s);
		s << ')';
	}
	else
	{
		right.Release(s);
	}
	return s;
}
