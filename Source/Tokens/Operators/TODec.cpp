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
//  The Original Code is the yavascript development system - TODec.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TODec.h"

Token &
	TODec::
	LED(SyntaxHandler & sh, Token & left)
{
	// Postfix
	SetType(TokenType::TO_DEC_POST);
	// Make right binding by
	// not calling sh.Expression!
	Add(left);
//	sh.Advance();
	return *this;
}

Token &
	TODec::
	NUD(SyntaxHandler & sh)
{
	// Prefix
	SetType(TokenType::TO_DEC_PRE);
	AddSymbols(sh, sh.Expression(150));
	return *this;
}

std::ostream &
	TODec::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TODec::
	Release(std::ostream & s) const
{
	Token &
		child = GetFirstChild();
	// Don't worry about lbp here
	// (a - b)--; makes no sense
	if (GetType() == TokenType::TO_DEC_PRE)
	{
		s << "--";
		child.Release(s);
	}
	else if (GetType() == TokenType::TO_DEC_POST)
	{
		child.Release(s);
		s << "--";
	}
	// else TO_INC, no defined location
	return s;
}
