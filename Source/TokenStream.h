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
//  The Original Code is the yavascript development system - TokenStream.h.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "Token.h"

// Interface for things
// providing a stream of tokens
class TokenStream
{
public:
	// Get the next token in the stream
	virtual Token &
		GetNext() = 0;
	
	// Set wanting a regular
	// expression, not a division
	virtual void
		SetRegex(const bool set) = 0;
};
