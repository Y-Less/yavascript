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
//  The Original Code is the yavascript development system - TKInstanceof.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKInstanceof.h"

#include <sstream>

std::ostream &
	TKInstanceof::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKInstanceof::
	Release(std::ostream & s) const
{
	Token
		& left = GetChild(0),
		& right = GetChild(1);
	// * 140
	// + 130
	// May or may not need a
	// space before the
	// "instanceof"
	std::ostringstream
		sb;
	GetFirstChild().Release(sb);
	std::string
		str = sb.str();
	const char
		ch = str[str.length() - 1];
	if (RequireBrackets(left, false))
	{
		// The thing on the right
		// has children and a lower
		// lbp, meaning it needs
		// brackets.
		s << '(' << str << ')';
	}
	else
	{
		s << str;
	}
	if ((const unsigned char)((ch | 0x20) - 'a') < 26 || (const unsigned char)(ch - '0') < 10 || ch == '_' || ch == '$')
	{
		// Output the space
		s << ' ';
	}
	// Output this operator
	s << "instanceof";
	if (RequireBrackets(right, true))
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
		DoSpacePar(right, s);
	}
	return s;
}

bool
	TKInstanceof::
	DoSpacePar(Token & token, std::ostream & s) const
{
	std::ostringstream
		sb;
	// Output to the string buffer
	token.Release(sb);
	// Get the string
	std::string
		str = sb.str();
	// Get the first character
	const char
		ch = str[0];
	// Same as TokenFactory::IsSym
	if ((const unsigned char)((ch | 0x20) - 'a') < 26 || (const unsigned char)(ch - '0') < 10 || ch == '_' || ch == '$')
	{
		s << ' ';
		s << str;
		return true;
	}
	s << str;
	return false;
}
