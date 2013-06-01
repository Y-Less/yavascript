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
//  The Original Code is the yavascript development system - Parser.h.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "SyntaxHandler.h"
#include "Token.h"
#include "TokenStream.h"

// This class is responsible
// for generating the parse
// tree.
class Parser :
	public SyntaxHandler
{
public:
	// cons
		Parser(TokenStream & stream);
	
	// dest
		~Parser();
	
	// =========================
	//  SyntaxHandler functions
	// =========================
	
	virtual Token &
		Expression(const int rbp = 0);
	
	virtual Token &
		Statement(const bool group = false, const char * const label = NULL);
	
	virtual Token &
		GetCurrent();
	
	virtual void
		SetRegex(const bool set);
	
	virtual Token &
		Advance(const TokenType::E_TYPE type = TokenType::TT__NONE);
	
	virtual Token &
		EoS();
	
	virtual bool
		SkippedLine();
	
private:
	// cons
		Parser(const Parser & c);
	
	virtual Token &
		ExpressionLabel(const int rbp, Token * t);
	
	Parser &
		operator=(const Parser & c)
	{
		return *this;
	};
	
	Token &
		GetNextReal(bool & skipNL);
	
	Token &
		Update(Token & nu);
	
	// Last read token
	Token *
		m_cur;
	
	TokenStream &
		m_tokens;
	
	bool
		m_bNL;
};
