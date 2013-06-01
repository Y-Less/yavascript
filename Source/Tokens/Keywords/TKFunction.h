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
//  The Original Code is the yavascript development system - TKFunction.h.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../TKeyword.h"

class TKFunction :
	public TKeyword
{
public:
	// cons
		TKFunction() :
			TKeyword(TokenType::TK_function, 170),
			m_scope(NULL),
			m_stmt(false)
	{
	};
	
	virtual std::ostream &
		Debug(std::ostream & s) const;
	
	virtual std::ostream &
		Release(std::ostream & s) const;
	
	virtual Token &
		NUD(SyntaxHandler & sh);
	
	virtual Token &
		STD(SyntaxHandler & sh);
	
	virtual bool
		IsStatement() const;
	
	virtual bool
		RequireSemicolon() const;
	
	virtual bool
		HasEffect() const
	{
		// If there's two children it's:
		// 
		// function () {};
		// 
		// If there's three children it's:
		// 
		// function name() {};
		// 
		// Named functions are complete
		// expressions on their own.
		// This is currently the only
		// thing who's return value
		// for HasEffect is non-constant.
		return GetChildCount() == 3;
	};
	
	void
		SetStatement()
	{
		m_stmt = true;
	};
	
private:
	Scope *
		m_scope;
	
	bool
		m_stmt;
};
