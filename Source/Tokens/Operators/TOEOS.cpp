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
//  The Original Code is the yavascript development system - TOEOS.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOEOS.h"

#include "../../Message.h"

// This is handled slightly specially
// it's not completely treated as
// an operator.

Token &
	TOEOS::
	NUD(SyntaxHandler & sh)
{
	Message::Send(Message::EXPECTED_RH, ";");
	return *this;
}

Token &
	TOEOS::
	STD(SyntaxHandler & sh)
{
	Message::Send(Message::EMPTY_STATEMENT);
	return *this;
}

bool
	TOEOS::
	IsStatement() const
{
	return true;
}
