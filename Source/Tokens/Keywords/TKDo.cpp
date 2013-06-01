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
//  The Original Code is the yavascript development system - TKDo.cpp.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKDo.h"

Token &
	TKDo::
	STD(SyntaxHandler & sh)
{
	// Add the statement to be
	// done at least once.
	Statement(sh);
	if (sh.GetCurrent().GetType() == TokenType::TK_while)
	{
		sh.Advance(TokenType::TK_while);
		// Evaluate the conditional
		// for this do-while.
		Conditional(sh);
	}
	else
	{
		// Give an error
		sh.Advance(TokenType::TK_while);
	}
	// do {} while ();
	// Should have a semi-colon (rare
	// for statements, e.g. if doesn't).
	sh.EoS();
	return *this;
}

std::ostream &
	TKDo::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKDo::
	Release(std::ostream & s) const
{
	DoLabel(s);
	s << "do";
	Token &
		tb = GetFirstChild();
	DoSpacePar(tb, s);
	// Semicolon
	if (tb.IsStatement())
	{
		if (tb.RequireSemicolon())
		{
			s << ';';
		}
	}
	else
	{
		// All expressions should
		s << ';';
	}
	s << "while(";
	GetChild(1).Release(s);
	s << ')';
	return s;
}
