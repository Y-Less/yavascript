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
//  The Original Code is the yavascript development system - TKeyword.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKeyword.h"

#include <sstream>

bool
	TKeyword::
	DoSpacePar(Token & token, std::ostream & s) const
{
	// This function takes a token
	// input and outputs it to the
	// given stream, outputting a
	// space first on the stream if
	// the first character in the
	// stream is a symbol character.
	// This is to optimise things:
	// 
	// else++a;
	// 
	// as opposed to:
	// 
	// else a++;
	// 
	// This sort of efficiency is
	// only worried about in
	// release mode, debug just
	// add the space regardless.
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
