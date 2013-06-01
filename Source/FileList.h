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
//  The Original Code is the yavascript development system - FileList.h.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <map>
#include <string>
#include <stack>

#include "TokenStream.h"
#include "InputFile.h"
#include "Message.h"

class FileList :
	public TokenStream
{
public:
	// cons
		FileList() :
			m_cur(NULL),
			m_mapFiles()
	{
	};
	
	// dest
		~FileList()
	{
	};
	
	bool
		Add(const char * const file);
	
	// Get the next token in the stream
	virtual Token &
		GetNext();
	
	// Set wanting a regular
	// expression, not a division
	virtual void
		SetRegex(const bool set);
	
private:
	// cons
		FileList(const FileList &l) :
			m_cur(NULL),
			m_mapFiles()
	{
	};
	
	FileList &
		operator=(const FileList &f)
	{
		return *this;
	};
	
	static void
		MakeFileName(std::string & str1, const std::string str2);
	
	// Put this first to hopefully
	// improve optimisations
	InputFile *
		m_cur;
	
	std::map<std::string, InputFile *>
		m_mapFiles;
};
