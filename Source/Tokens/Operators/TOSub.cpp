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
//  The Original Code is the yavascript development system - TOSub.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOSub.h"

Token &
	TOSub::
	NUD(SyntaxHandler & sh)
{
	AddSymbols(sh, sh.Expression(150));
	return *this;
}

std::ostream &
	TOSub::
	Debug(std::ostream & s) const
{
	// Function to do the addition
	s << "$Y._sub(";
	// Parameters
	GetChild(0).Debug(s);
	s << ", ";
	GetChild(1).Debug(s);
	// End
	s << ')';
	return s;
}

std::ostream &
	TOSub::
	Release(std::ostream & s) const
{
	if (GetChildCount() == 1)
	{
		// -3;
		s << '-';
		Token &
			t = GetFirstChild();
		// TODO: Handle
		// a = -(-b);
		if (RequireBrackets(t, true))
		{
			s << '(';
			t.Release(s);
			s << ')';
		}
		else
		{
			t.Release(s);
		}
		return s;
	}
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
	if (right.GetType() == TokenType::TO_SUB && right.GetChildCount() == 1)
	{
		// a - -b
		// a + b
		s << '+';
		Token &
			cur = right.GetFirstChild();
		// + and - have the same LBP
		if (RequireBrackets(cur, true))
		{
			s << '(';
			cur.Release(s);
			s << ')';
		}
		else
		{
			cur.Release(s);
		}
	}
	else
	{
		// a-- - b
		if (left.GetType() == TokenType::TO_INC_POST)
		{
			// Ouptut a space
			s << ' ';
		}
		// Output this operator
		s << '-';
		if (right.GetType() == TokenType::TO_INC_PRE)
		{
			// a - --b
			// Ouptut a space
			s << ' ';
			right.Release(s);
		}
		else if (RequireBrackets(right, true))
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
	}
	return s;
}
