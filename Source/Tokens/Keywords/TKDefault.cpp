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
//  The Original Code is the yavascript development system - TKDefault.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKDefault.h"

#include "../../Message.h"
#include "../../Generator.h"

Token &
	TKDefault::
	STD(SyntaxHandler & sh)
{
	Message::Send(Message::UNMATCHED_DEFAULT);
	TokenType::E_TYPE
		type = TokenType::TT__NONE;
	// Get rid of the colon
	sh.Advance(TokenType::TO_COLON);
	// Get rid of this token
	Dispose();
	// Return a blank token
	return Generator::Null();
}
