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
//  The Original Code is the yavascript development system - TLiteral.h.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../Token.h"

#include <iostream>

// This class is the root
// of everythin which has
// some form of value,
// e.g. numbers, strings,
// symbols etc.  It deals
// with the memory (de)-
// allocation and
// storing.
class TLiteral :
	public Token
{
public:
	// cons
		TLiteral(const char * str, const TokenType::E_TYPE type);
	
	virtual // dest
		~TLiteral();
	
	virtual Token &
		NUD(SyntaxHandler & sh);
	
	virtual bool
		SetValue(const char * str);
	
	char * const
		GetString() const
	{
		return m_szStr;
	};
	
	virtual std::ostream &
		Debug(std::ostream & s) const;
	
	virtual std::ostream &
		Release(std::ostream & s) const;
	
protected:
	virtual std::ostream &
		Output(std::ostream & s) const
	{
		return s << m_szStr;
	};
	
private:
	char *
		m_szStr;
};

// Short convenience function
// for easilly casting to a
// TLiteral object.  Stands
// for TokenLiteral::Get()
namespace TL
{
	static TLiteral &
		G(Token & t)
	{
		return *dynamic_cast<TLiteral *>(&t);
	}
}
