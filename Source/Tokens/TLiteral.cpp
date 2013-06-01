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
//  The Original Code is the yavascript development system - TLiteral.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TLiteral.h"

#include "../Message.h"

// cons
	TLiteral::
	TLiteral(const char * str, const TokenType::E_TYPE type) :
		Token(type, -10)
{
	if (str == NULL)
	{
		m_szStr = NULL;
	}
	else
	{
		// Allocate memory for the string
		try
		{
			// Save a COPY of the string
			char *
				s = new char [strlen(str) + 1];
			strcpy(s, str);
			m_szStr = s;
		}
		catch (std::exception e)
		{
			Message::Send(Message::OUT_OF_MEMORY);
			m_szStr = NULL;
		}
	}
}

bool
	TLiteral::
	SetValue(const char * str)
{
	// Free the current value
	delete [] m_szStr;
	m_szStr = NULL;
	if (str)
	{
		try
		{
			// Save a COPY of the string
			char *
				s = new char [strlen(str) + 1];
			strcpy(s, str);
			m_szStr = s;
		}
		catch (std::exception e)
		{
			Message::Send(Message::OUT_OF_MEMORY);
			m_szStr = NULL;
		}
	}
	return true;
}

Token &
	TLiteral::
	NUD(SyntaxHandler & sh)
{
	// For now don't do anything extra
	// literals are just output as is
	return *this;
}

// dest
	TLiteral::
	~TLiteral()
{
	// Delete the string
	delete [] m_szStr;
	m_szStr = NULL;
}
	
std::ostream &
	TLiteral::
	Debug(std::ostream & s) const
{
	return s << m_szStr;
}

std::ostream &
	TLiteral::
	Release(std::ostream & s) const
{
	return s << m_szStr;
}
