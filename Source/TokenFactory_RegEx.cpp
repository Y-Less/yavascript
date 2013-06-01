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
//  The Original Code is the yavascript development system - TokenFactory_RegEx.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Message.h"

#include <iostream>

// TODO: RegEx input validation
// Could take a while, leave it for now
Token &
	TokenFactory::
	DoRegex()
{
	unsigned char
		ch;
	bool
		rnl = false;
	// Expecting a regex
	// If we're here it HAS to be a regex
	// Not anything else
	std::streampos
		pos = m_sCur->tellg();
	// Subtract 1 twice
	pos -= 1;
	for ( ; ; )
	{
		ch = Read();
		if (ch == '\0')
		{
			// Reached end of file
			Message::Send(Message::UNEXPECTED_EOF);
			break;
		}
		if (rnl)
		{
			rnl = false;
			if (ch == '\r')
			{
				ch = Read();
				if (ch != '\n')
				{
					m_sCur->unget();
				}
			}
		}
		else
		{
			// Check character
			// \ means is an escape
			// / is end of regex
			if (ch == '\\')
			{
				rnl = true;
			}
			else if (ch == '/' || ch == '\r' || ch == '\n')
			{
				break;
			}
		}
	}
	if (ch != '/')
	{
		Message::Send(Message::UNCLOSED_REGEX);
	}
	do
	{
		ch = Read();
		// Find the end
		// Regex have i, g or m at the end for scope
	}
	while (ch == 'i' || ch == 'g' || ch == 'm');
	std::streampos
		len;
	if (!ch)
	{
		// At the end of the file
		m_sCur->clear();
		len = 1;
	}
	else
	{
		len = 0;
	}
	len += m_sCur->tellg();
	// Make sure the first / is included
	// We know what it is but this way is easier
	// Also ensures the right amount of memory is allocated
	len -= pos;
	char *
		c = (char *)alloca(len);
	if (c)
	{
		// Check memory allocated
		m_sCur->seekg(pos);
		len -= 1;
		m_sCur->read(c, len);
		c[len] = '\0';
		if (m_sCur->bad())
		{
			Message::Send(Message::INPUT_STREAM_ERROR);
		}
		else
		{
			return Create(c, TokenType::TT_REGEX);
		}
	}
	else
	{
		m_sCur->unget();
		Message::Send(Message::OUT_OF_MEMORY);
	}
	// Will probably fail
	// Only gets here if there's a problem above
	// Stream and memory errors should be fatal
	// so this point should never be reached
	return Create("", TokenType::TT_REGEX);
}
