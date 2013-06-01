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
//  The Original Code is the yavascript development system - SyntaxHandler.h.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "TokenType.h"

class Token;

// "Interface"
class SyntaxHandler
{
public:
	// Evaluate part of a statement.
	virtual Token &
		Expression(const int rbp = 0) = 0;
	
	// Evaluate a new statement.
	// Generally calls the STD on
	// the first token instead of NUD.
	// If group is true a group is expected
	// if it's false it's not.
	virtual Token &
		Statement(const bool group = false, const char * const label = NULL) = 0;
	
	// Re-get the current token
	virtual Token &
		GetCurrent() = 0;
	
	virtual Token &
		Advance(const TokenType::E_TYPE type = TokenType::TT__NONE) = 0;
	
	virtual Token &
		EoS() = 0;
	
	virtual bool
		SkippedLine() = 0;
	
	virtual void
		SetRegex(const bool set) = 0;
	
private:
	// No private things, pointless in an interface.
};
