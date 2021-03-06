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
//  The Original Code is the yavascript development system - TKFinally.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKFinally.h"

#include "../../Message.h"

Token &
	TKFinally::
	STD(SyntaxHandler & sh)
{
	// If this is called it's bad
	// The "try" handler should cover this
	// this being called means there was
	// no "try" before.
	Message::Send(Message::UNMATCHED_FINALLY);
	delete &sh.Statement(true);
	return *this;
}
