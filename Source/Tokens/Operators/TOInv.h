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
//  The Original Code is the yavascript development system - TOInv.h.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../TOperator.h"

class TOInv :
	public TOperator
{
public:
	// cons
		TOInv() :
			TOperator(TokenType::TO_INV)
	{
	};
	
	virtual Token &
		NUD(SyntaxHandler & sh);
	
	virtual std::ostream &
		Release(std::ostream &s) const;
};
