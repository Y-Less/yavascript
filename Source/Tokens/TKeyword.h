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
//  The Original Code is the yavascript development system - TKeyword.h.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../Token.h"

class TKeyword :
	public Token
{
public:
	// cons
		TKeyword(const TokenType::E_TYPE type) :
			Token(type, -10)
	{
	};
	
	// cons
		TKeyword(const TokenType::E_TYPE type, const int lbp) :
			Token(type, lbp)
	{
	};
	
protected:
	bool
		DoSpacePar(Token & token, std::ostream & s) const;
};
