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
//  The Original Code is the yavascript development system - TKIf.cpp.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKIf.h"

#include "../../Message.h"

Token &
	TKIf::
	STD(SyntaxHandler & sh)
{
	// Code to resolve an if statement
	// Do the conditional
	Conditional(sh);
	// Add the true statement
	Statement(sh);
	// Do we have an "else"?
	if (sh.GetCurrent().GetType() == TokenType::TK_else)
	{
		// Have an else
		// Don't actually need this token
		sh.Advance(TokenType::TK_else);
		// Add the "else" statement
		Statement(sh);
	}
	return *this;
}

std::ostream &
	TKIf::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKIf::
	Release(std::ostream & s) const
{
	DoLabel(s);
	// Add keyword
	s << "if(";
	GetFirstChild().Release(s);
	s << ')';
	// Output the true branch
	Token &
		tb = GetChild(1);
	if (tb.GetType() == TokenType::TK_if && GetChildCount() == 3)
	{
		// Force braces
		s << '{';
		tb.Release(s);
		s << '}';
	}
	else
	{
		tb.Release(s);
	}
	// Semicolon
	bool
		semi;
	if (tb.IsStatement())
	{
		// Some statements need semicolons
		semi = tb.RequireSemicolon();
	}
	else
	{
		// All expressions should
		semi = true;
	}
	if (GetChildCount() == 3)
	{
		// else
		if (semi)
		{
			s << ';';
		}
		s << "else";
		// False branch
		DoSpacePar(GetChild(2), s);
	}
	return s;
}

bool
	TKIf::
	RequireSemicolon() const
{
	// An if only requires a semicolon
	// when it ends in an expression.
	// For example:
	// if (a) alert('hi');
	// requires a semicolon.
	// if (a) function m() {}
	// doesn't.
	switch (GetChildCount())
	{
		case 2:
		{
			// if-then
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
		case 3:
		{
			// if-then-else
			Token &
				fb = GetChild(2);
			if (fb.IsStatement())
			{
				return fb.RequireSemicolon();
			}
			else
			{
				// All expressions should
				return true;
			}
		}
	}
	// Not really needed as
	// this should never be
	// needed before the
	// children are defined.
	// But it's needed by
	// the compiler.
	return false;
}
