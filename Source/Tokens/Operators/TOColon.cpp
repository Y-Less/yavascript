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
//  The Original Code is the yavascript development system - TOColon.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOColon.h"

#include "../../Message.h"

Token &
	TOColon::
	LED(SyntaxHandler & sh, Token & left)
{
	Message::Send(Message::UNMATCHED_COLON);
	AddSymbols(sh, left);
	AddSymbols(sh, sh.Expression());
	return *this;
}

std::ostream &
	TOColon::
	Release(std::ostream & s) const
{
	// In an object
	Token
		& left = GetChild(0),
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
	s << ':';
	if (RequireBrackets(right, false))
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
