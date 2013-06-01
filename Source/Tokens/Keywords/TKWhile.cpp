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
//  The Original Code is the yavascript development system - TKWhile.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKWhile.h"

Token &
	TKWhile::
	STD(SyntaxHandler & sh)
{
	// This is by far the simplest
	// of the control statements.
	// Especially as 90% of the code
	// is inherited from TT_Control.
	// Code to resolve a while statement
	// Do the conditional
	Conditional(sh);
	// Add the statement
	Statement(sh);
	return *this;
}

std::ostream &
	TKWhile::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKWhile::
	Release(std::ostream & s) const
{
	DoLabel(s);
	s << "while(";
	GetFirstChild().Release(s);
	s << ')';
	GetChild(1).Release(s);
	return s;
}

bool
	TKWhile::
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
