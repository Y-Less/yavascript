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
//  The Original Code is the yavascript development system - TOAdd.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOAdd.h"

#include "../../StringCast.h"

#include "../TString.h"

#include <iostream>

Token &
	TOAdd::
	LED(SyntaxHandler & sh, Token & left)
{
	// Inline addition
	Token &
		right = sh.Expression(130);
	if (CheckParameters(left, right))
	{
		AddSymbols(sh, left);
		AddSymbols(sh, right);
		// This is a FIFO stack
		// NOT a FILO stack
		Token
			& le = Pop(),
			& re = Pop();
		if (re.IsString())
		{
			// See if the le can be coerced
			// to a string
			if (le.IsString() || le.IsNumber())
			{
				// Well that's just easy!
				// Numbers are stored as
				// strings internally for
				// exactly this sort of thing
				// We don't need this
				// token any more.
				Add(le);
				Dispose();
				// Add the texts together
				// Use C++ strings for speed
				dynamic_cast<TString *>(&re)->SetValue((SC::R(le) + SC::R(re)).c_str());
				return re;
			}
		}
		else if (le.IsString())
		{
			if (re.IsString() || re.IsNumber())
			{
				Add(re);
				Dispose();
				dynamic_cast<TString *>(&le)->SetValue((SC::R(le) + SC::R(re)).c_str());
				return le;
			}
		}
		/*else if (le.IsNumber())
		{
			if (re.IsNumber())
			{
				// Do the sum and return
				// the result (smaller)
			}
		}
		else if (le.IsSymbol())
		{
			// Constant value propogation
		}
		else if (re.IsSymbol())
		{
			// Constant value propogation
		}*/
		// Add the two tree branches
		Add(le);
		Add(re);
	}
	else
	{
		SignalBad();
		delete &left;
		delete &right;
	}
	return *this;
}

Token &
	TOAdd::
	NUD(SyntaxHandler & sh)
{
	AddSymbols(sh, sh.Expression(150));
	return *this;
}

std::ostream &
	TOAdd::
	Debug(std::ostream & s) const
{
	// Function to do the addition
	s << "$Y._add(";
	// Parameters
	GetChild(0).Debug(s);
	s << ", ";
	GetChild(1).Debug(s);
	// End
	s << ')';
	return s;
}

std::ostream &
	TOAdd::
	Release(std::ostream & s) const
{
	if (GetChildCount() == 1)
	{
		// +3;
		// becomes:
		// 3;
		Token &
			t = GetFirstChild();
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
		// a + -b
		// a - b
		s << '-';
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
		// a++ + b
		if (left.GetType() == TokenType::TO_INC_POST)
		{
			// Ouptut a space
			s << ' ';
		}
		// Output this operator
		s << '+';
		if (right.GetType() == TokenType::TO_INC_PRE)
		{
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
