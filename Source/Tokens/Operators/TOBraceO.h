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
//  The Original Code is the yavascript development system - TOBraceO.h.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../TOperator.h"

class TOBraceO :
	public TOperator
{
public:
	// cons
		TOBraceO() :
			TOperator(TokenType::TO_BRACE_O)
	{
	};
	
	virtual std::ostream &
		Debug(std::ostream & s) const;
	
	virtual std::ostream &
		Release(std::ostream & s) const;
	
	virtual bool
		IsStatement() const
	{
		return true;
	};
	
	virtual Token &
		STD(SyntaxHandler & sh);
	
	virtual Token &
		NUD(SyntaxHandler & sh);
	
	virtual bool
		Labelable() const
	{
		return true;
	};
};
