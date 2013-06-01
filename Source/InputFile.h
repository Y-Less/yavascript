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
//  The Original Code is the yavascript development system - InputFile.h.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <string>
#include <iostream>

#include "TokenFactory.h"
#include "TokenStream.h"

// An input file purely contains information
// on what it is and it's current token stream
class InputFile :
	public TokenStream
{
public:
	// cons
		InputFile(char * const szFile, InputFile * parent);
	
	// dest
		~InputFile()
	{
	};
	
	virtual Token &
		GetNext();
	
	virtual void
		SetRegex(const bool set)
	{
		m_tokenFactory.SetRegex(set);
	};
	
	char * const
		GetFileName() const
	{
		return m_tokenFactory.GetStreamName();
	};
	
	InputFile *
		GetParent() const
	{
		return m_parent;
	};
	
private:
	// cons
		InputFile(const InputFile &i) :
			m_tokenFactory(*GetStream(""), ""),
			m_parent(NULL)
	{
	};
	
	static std::istream *
		GetStream(char * const szFile);
	
	InputFile &
		operator=(const InputFile &i)
	{
		return *this;
	};
	
	// Private members
	TokenFactory
		m_tokenFactory;
	
	InputFile *
		m_parent;
	
	bool
		m_bStart,
		m_bEnd;
};
