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
//  The Original Code is the yavascript development system - Symbol.cpp.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Symbol.h"

#include "Message.h"

#include <exception>

char *
	Symbol::
	SaveName(const char * const name)
{
	if (name)
	{
		try
		{
			// Save a COPY of the string
			char *
				s = new char [strlen(name) + 1];
			strcpy(s, name);
			return s;
		}
		catch (std::exception e)
		{
			Message::Send(Message::OUT_OF_MEMORY);
		}
	}
	return NULL;
}

bool
	Symbol::
	CheckName(const char * name)
{
	return !strcmp(name, m_name);
}
