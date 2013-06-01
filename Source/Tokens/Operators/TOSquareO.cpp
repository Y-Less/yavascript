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
//  The Original Code is the yavascript development system - TOSquareO.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOSquareO.h"

#include "../../Generator.h"
#include "../../Message.h"

Token &
	TOSquareO::
	LED(SyntaxHandler & sh, Token & left)
{
	// Using an array
	AddSymbols(sh, left);
	if (sh.GetCurrent().GetType() == TokenType::TO_SQUARE_C)
	{
		// a[]
		Message::Send(Message::INVALID_INDEX);
	}
	else
	{
		Token &
			right = sh.Expression();
		AddSymbols(sh, right);
	}
	sh.Advance(TokenType::TO_SQUARE_C);
	return *this;
}

Token &
	TOSquareO::
	NUD(SyntaxHandler & sh)
{
	// Declaring an array
	Token &
		ret = Generator::CIL(TokenType::TC_ARRAY);
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	// We don't actually need this token
	Dispose();
	if (type == TokenType::TO_SQUARE_C)
	{
		// Empty array
		// Get rid of the [] tokens
		sh.Advance(TokenType::TO_SQUARE_C);
		return ret;
	}
	for ( ; ; )
	{
		if (type == TokenType::TO_COMMA)
		{
			// Empty array value
			ret.Add(Generator::Null());
		}
		else
		{
			// Add the value of the entry
			ret.Add(sh.Expression());
			if (sh.GetCurrent().GetType() == TokenType::TO_SQUARE_C)
			{
				// Empty array
				// Get rid of the [] tokens
				sh.Advance(TokenType::TO_SQUARE_C);
				return ret;
			}
		}
		sh.Advance(TokenType::TO_COMMA);
		type = sh.GetCurrent().GetType();
		if (type == TokenType::TO_SQUARE_C)
		{
			// Empty array
			// Get rid of the [] tokens
			// Add a final empty entry:
			// [,]
			// needs two items.
			ret.Add(Generator::Null());
			sh.Advance(TokenType::TO_SQUARE_C);
			return ret;
		}
	}
}

std::ostream &
	TOSquareO::
	Release(std::ostream & s) const
{
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
	s << '[';
	right.Release(s);
	s << ']';
	return s;
}
