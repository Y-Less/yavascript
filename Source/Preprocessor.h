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
//  The Original Code is the yavascript development system - Preprocessor.h. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <istream>
#include <map>

#include "TokenFactory.h"

#include "PreprocType.h"
#include "SyntaxHandler.h"

class Preprocessor :
	public SyntaxHandler
{
public:
	// cons
		Preprocessor() :
			m_defines(),
			m_pFactory(NULL),
			m_indent(0)
	{
	};
	
	// cons
		Preprocessor(const Preprocessor & p) :
			m_defines(p.m_defines),
			m_pFactory(p.m_pFactory),
			m_indent(0)
	{
	};
	
	// dest
		~Preprocessor()
	{
	};
	
	Preprocessor &
		operator=(const Preprocessor & p)
	{
		m_defines = p.m_defines;
		m_pFactory = p.m_pFactory;
		return *this;
	};
	
	void
		DoDirective(TokenFactory & input);
	
	bool
		Defined(std::string key);
	
	std::istream *
		Get(std::string key);
	
	// SyntaxHandler functions
	// Evaluate part of a statement.
	virtual Token &
		Expression(const int rbp = 0);
	
	// Evaluate a new statement.
	// Generally calls the STD on
	// the first token instead of NUD.
	// If group is true a group is expected
	// if it's false it's not.
	virtual Token &
		Statement(const bool group = false, const char * const label = NULL);
	
	// Re-get the current token
	virtual Token &
		GetCurrent()
	{
		if (m_cur)
		{
			return *m_cur;
		}
		return Advance();
	};
	
	virtual Token &
		Advance(const TokenType::E_TYPE type = TokenType::TT__NONE);
	
	virtual Token &
		EoS()
	{
		return Advance();
	};
	
	virtual bool
		SkippedLine()
	{
		// Never here
		return false;
	};
	
	virtual void
		SetRegex(const bool set)
	{
		// Never here
	};
	
	void
		CheckEnd();
	
private:
	bool
		SkipTo();
	
	void
		SkipString();
	
	bool
		SkipWhitespace(unsigned char & ch);
	
	char
		SkipComment(unsigned char & ch);
	
	char *
		GetDefineName();
	
	char *
		GetLine(const bool save);
	
	double
		DoExpr(Token & t);
	
	PreprocType::E_PREPROC
		GetType();
	
	// Define table
	std::map<std::string, std::string>
		m_defines;
	
	// Enum for state machine
	enum E_STATE
	{
		ES__NONE = 0,
		ES__DONE,
		ES__UNKNOWN,
		ES_I,
		ES_IF,
		ES_E,
	};
	
	Token *
		m_cur;
	
	TokenFactory *
		m_pFactory;
	
	int
		m_indent;
};
