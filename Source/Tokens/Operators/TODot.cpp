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
//  The Original Code is the yavascript development system - TODot.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TODot.h"

#include "../../Message.h"

#include "../TLiteral.h"

Token &
	TODot::
	LED(SyntaxHandler & sh, Token & left)
{
	// Exactly the same as TT_Infix
	// but with no symbol addition
	// on the right hand side.
	// 
	// a.b = 2;
	// 
	// a is a symbol, b is not.
	// If you have:
	// 
	// a.b.c = 2;
	// 
	// Then the first set is 'a',
	// which is a symbol, and 'b',
	// which is on the right.  The
	// second set is 'a.b', which
	// isn't a symbol, and 'c',
	// which is on the right.  So
	// they're all resolved correctly.
	Token &
		right = sh.Expression(160);
	if (CheckParameters(left, right))
	{
		// Do the left normally
		AddSymbols(sh, left);
		// Do the right specially
		if (right.GetType() == TokenType::TO_BRACKET_O)
		{
			// Remove brackets
			Add(right.Pop());
			delete &right;
		}
		else
		{
			Add(right);
		}
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
	TODot::
	CheckParameters(Token & left, Token & right) const
{
	if (left.IsAssignment() || right.IsAssignment())
	{
		// Warning
		// Unintended assignment
		Message::Send(Message::UNINTENDED_ASSIGNMENT);
	}
	if (right.GetType() == TokenType::TK_this)
	{
		// 'this' must go on the left
		Message::Send(Message::BAD_THIS);
	}
	return !(
		left.GetType() == TokenType::TT__NONE ||
		right.GetType() == TokenType::TT__NONE);
}

std::ostream &
	TODot::
	Debug(std::ostream & s) const
{
	// Function to do the addition
	s << "$Y._dot(";
	// Parameters
	GetChild(0).Debug(s);
	s << ", \"";
	GetChild(1).Debug(s);
	// End
	s << "\")";
	return s;
}
