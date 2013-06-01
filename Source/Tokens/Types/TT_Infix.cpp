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
//  The Original Code is the yavascript development system - TT_Infix.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TT_Infix.h"

#include "../../Message.h"

Token &
	TT_Infix::
	LED(SyntaxHandler & sh, Token & left)
{
	Token &
		right = sh.Expression(GetLBP());
	if (CheckParameters(left, right))
	{
		AddSymbols(sh, left);
		AddSymbols(sh, right);
	}
	else
	{
		SignalBad();
		delete &left;
		delete &right;
	}
	return *this;
}

bool
	TT_Infix::
	CheckParameters(Token & left, Token & right) const
{
	if (left.IsAssignment() || right.IsAssignment())
	{
		// Warning
		// Unintended assignment
		Message::Send(Message::UNINTENDED_ASSIGNMENT);
	}
	return !(
		left.GetType() == TokenType::TT__NONE ||
		right.GetType() == TokenType::TT__NONE);
}

void
	TT_Infix::
	SignalBad() const
{
	Message::Send(Message::INVALID_OPERANDS);
}

std::ostream &
	TT_Infix::
	Release(std::ostream & s) const
{
	Token
		& left = GetFirstChild(),
		& right = GetChild(1);
	// * 140
	// + 130
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
	// Output this operator
	s << GetType();
	if (RequireBrackets(right, true))
	{
		// The thing on the right
		// has children and a lower
		// lbp, meaning it needs
		// brackets.
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
