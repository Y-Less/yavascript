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
//  The Original Code is the yavascript development system - Symbol.h.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <string.h>

class Symbol
{
public:
	// cons
		Symbol(const char * const name) :
			m_pNext(NULL),
			m_name(SaveName(name))
	{
	};
	
	// dest
		~Symbol()
	{
		delete [] m_name;
	}
	
	void
		SetNext(Symbol * next)
	{
		m_pNext = next;
	};
	
	Symbol *
		GetNext() const
	{
		return m_pNext;
	};
	
	bool
		CheckName(const char * name);
	
private:
	// Can't use standard lists here
	// There are multiple entry points
	Symbol *
		m_pNext;
	
	const char * const
		m_name;
	
	Symbol &
		operator=(const Symbol & s)
	{
		return *this;
	};
	
	// cons
		Symbol(const Symbol & s) :
			m_name(NULL)
	{
	};
	
	static char *
		SaveName(const char * const name);
};
