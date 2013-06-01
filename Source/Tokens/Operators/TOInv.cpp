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
//  The Original Code is the yavascript development system - TOInv.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOInv.h"

Token &
	TOInv::
	NUD(SyntaxHandler & sh)
{
	AddSymbols(sh, sh.Expression(150));
	return *this;
}

std::ostream &
	TOInv::
	Release(std::ostream & s) const
{
	Token
		& right = GetFirstChild();
	// Output this operator
	s << '~';
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
