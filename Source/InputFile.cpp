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
//  The Original Code is the yavascript development system - InputFile.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "InputFile.h"

#include <fstream>
#include <exception>

#include "Message.h"
#include "Generator.h"

#include <string.h>

#include <iostream>

// cons
	InputFile::
	InputFile(char * const szFile, InputFile * parent) :
		m_bStart(false),
		m_bEnd(false),
		m_parent(parent),
		m_tokenFactory(*GetStream(szFile), szFile)
{
}

Token &
	InputFile::
	GetNext()
{
	if (m_bEnd)
	{
		// Finished with thie file
		// don't bother with the
		// token factory again.
		return Generator::EoF();
	}
	else if (m_bStart)
	{
		Token &
			ret = m_tokenFactory.GetNext();
		if (ret.GetType() == TokenType::TT__EOF)
		{
			m_bEnd = true;
			// Add a newline to the end
			// Forces SkippedLine to true
			// This token has a VERY
			// short lifespan
			return Generator::EoL();
		}
		else
		{
			return ret;
		}
	}
	else
	{
		// Start braces enclosing
		// this file's text.  This
		// is to ensure things like:
		// 
		// if (a) $include('moo.js');
		// 
		// Are read in correctly.
		m_bStart = true;
		return Generator::File();
	}
};

std::istream *
	InputFile::
	GetStream(char * const szFile)
{
	std::istream *
		ret = NULL;
	try
	{
		ret = new std::fstream(szFile, std::fstream::in | std::fstream::binary);
		if (ret->fail())
		{
			Message::Send(Message::COULD_NOT_OPEN, szFile);
		}
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return ret;
}
