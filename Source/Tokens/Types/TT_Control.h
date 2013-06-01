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
//  The Original Code is the yavascript development system - TT_Control.h.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../TKeyword.h"

class TT_Control :
	public TKeyword
{
public:
	// cons
		TT_Control(const TokenType::E_TYPE type) :
			TKeyword(type)
	{
	};
	
	virtual bool
		IsStatement() const;
	
protected:
	virtual bool
		Conditional(SyntaxHandler & sh);
	
	virtual bool
		Statement(SyntaxHandler & sh);
};
