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
//  The Original Code is the yavascript development system - TT_Control.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TT_Control.h"

#include "../../Message.h"
#include "../../Generator.h"

bool
	TT_Control::
	IsStatement() const
{
	return true;
}

bool
	TT_Control::
	Conditional(SyntaxHandler & sh)
{
	// Can do expression optimisation here
	if (sh.Advance(TokenType::TO_BRACKET_O).GetType() == TokenType::TO_BRACKET_C)
	{
		// if ()
		Message::Send(Message::INVALID_EXPRESSION);
	}
	else
	{
		// Add the conditional
		Token &
			expr = sh.Expression();
		if (expr.IsAssignment())
		{
			// if (a = b)
			// Warn of possibly unintended assignment
			// This currently also does: if (a += b)
			// I've not decided if this is a bug or feature
			Message::Send(Message::UNINTENDED_ASSIGNMENT);
			Add(expr);
		}
		else if (expr.GetType() == TokenType::TO_BRACKET_O)
		{
			// if ((x))
			// Useful for intended assignments
			// if ((a = b))
			// Don't include the extrs brackets.
			// Pop gets the contents and
			// removes them from the brackets
			Add(expr.Pop());
			// Delete the brackets but not
			// the old contents (popped).
			delete &expr;
		}
		else
		{
			Add(expr);
		}
	}
	// Check for a close bracket
	sh.Advance(TokenType::TO_BRACKET_C);
	return true;
}

bool
	TT_Control::
	Statement(SyntaxHandler & sh)
{
	// This function checks for
	// an empty statement after
	// the given control statement.
	// It adds whatever's given.
	if (sh.GetCurrent().GetType() == TokenType::TT_EOS)
	{
		// Add a null expression
		Add(Generator::Null());
		// Require them to do:
		// if (a) {}
		// To have an empty statement
		// not:
		// if (a) ;
		// Which is much simpler to type
		// by mistake.
		Message::Send(Message::UNINTENDED_EOS);
		sh.EoS();
		return false;
	}
	// Control statement payloads
	// should be surrounded by
	// braces, even when not
	// required.
	Add(sh.Statement(true));
	return true;
}
