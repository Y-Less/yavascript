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
//  The Original Code is the yavascript development system - FileList.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "FileList.h"

#include "Generator.h"
#include "Message.h"

#include <iostream>

// Generate a full filename based on the current file
// and the file you're including.
// For example file "libraries/Window.js" includes
// file "/../extra/moo.js":
// First the filename is removed, so you have "libraries/"
// and "/../extra/moo.js", then they're appended, taking
// into account double //: "libraries/../extra/moo.js",
// then relative naming is accounted for, giving:
// "extra/moo.js"
void
	FileList::
	MakeFileName(std::string & str1, const std::string str2)
{
	size_t
		es;
	es = str1.find_last_of("/\\");
	// Remove the current filename
	str1.erase(es + 1);
	// Check if the new path starts with a slash
	if (str2[0] == '/' || str2[0] == '\\')
	{
		str1.append(str2, 1, std::string::npos);
	}
	else
	{
		str1.append(str2);
	}
	// Remove relative file paths (i.e. /../)
	size_t
		start;
	start = 0;
	es = 0;
	while ((es = str1.find("../", es)) != std::string::npos)
	{
		// Check it's not something stupid like /hello../
		// Also, don't remove the first ones
		if (es == start)
		{
			// No way this can happen after the start
			start = 3;
			es++;
		}
		else if (str1[es - 1] == '/' || str1[es - 1] == '\\')
		{
			// Find the start of the previous directory
			start = str1.find_last_of("/\\", es - 2);
			str1.erase(start + 1, (es - start) + 2);
			es = 0;
			start = 0;
		}
		else
		{
			es++;
		}
	}
	start = 0;
	es = 0;
	while ((es = str1.find("..\\", es)) != std::string::npos)
	{
		// Check it's not something stupid like /hello../
		// Also, don't remove the first ones
		if (es == start)
		{
			// No way this can happen after the start
			start = 3;
			es++;
		}
		else if (str1[es - 1] == '/' || str1[es - 1] == '\\')
		{
			// Find the start of the previous directory
			start = str1.find_last_of("/\\", es - 2);
			str1.erase(start + 1, (es - start) + 2);
			es = 0;
			start = 0;
		}
		else
		{
			es++;
		}
	}
}

bool
	FileList::
	Add(const char * const file)
{
	// Get the factory for this file
	// If it's already been done then return the handle
	// The fact that it's been done means it'll only
	// return EOF tokens
	std::string
		dir = "";
	if (m_cur)
	{
		dir = m_cur->GetFileName();
	}
	MakeFileName(dir, file);
	// Get the factory
	std::map<std::string, InputFile *>::iterator
		el = m_mapFiles.find(dir);
	if (el == m_mapFiles.end())
	{
		// Doesn't exist - make it
		InputFile *
			f = NULL;
		char *
			s = NULL;
		try
		{
			s = new char [dir.length() + 1];
			strcpy(s, dir.c_str());
			f = new InputFile(s, m_cur);
			m_mapFiles[dir] = f;
			// Set as the current file
			m_cur = f;
		}
		catch (std::exception e)
		{
			// If one's not made it'll
			// still be null.  It doesn't
			// really matter though as
			// the error will end the
			// program and process.
			delete [] s;
			delete f;
			Message::Send(Message::OUT_OF_MEMORY);
			return false;
		}
	}
	// Return that this file is already done
	// so we're happy to say it's fine
	return true;
}

Token &
	FileList::
	GetNext()
{
	Token *
		ret;
	if (m_cur)
	{
		// We have a current file
		// Parse it
		ret = &m_cur->GetNext();
		if (ret->GetType() == TokenType::TT__EOF)
		{
			// End of current file
//			delete ret;
			// Go up the stack
			// If we're completely finished
			// then return TT__END
			m_cur = m_cur->GetParent();
		}
		//else
		//{
			return *ret;
		//}
	}
	// We don't have a current
	// file, return end of stream
	return Generator::End();
}

// Set wanting a regular
// expression, not a division
void
	FileList::
	SetRegex(const bool set)
{
	if (m_cur)
	{
		// Set the current file
		// for reading regex
		m_cur->SetRegex(set);
	}
}
