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
//  The Original Code is the yavascript development system - TKVar.h.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../TKeyword.h"

#include "TKFor.h"

class TKVar :
	public TKeyword
{
public:
	// cons
		TKVar() :
			TKeyword(TokenType::TK_var)
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
	
	virtual bool
		RequireSemicolon() const
	{
		return true;
	};
	
	virtual Token &
		STD(SyntaxHandler & sh);
	
private:
	bool
		DoVar(SyntaxHandler & sh, Token * token);
	
	// Let TKFor use DoVar
	// But no-one else
	friend class TKFor;
};
