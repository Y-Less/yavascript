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
//  The Original Code is the yavascript development system - Compiler.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Compiler.h"

#include <string.h>
#include <fstream>

#include "Optimiser.h"

Compiler &
	Compiler::
	Get()
{
	static Compiler *
		s_compiler = new Compiler();
	return *s_compiler;
}

bool
	Compiler::
	SetOption(E_OPTION key, const char * const value)
{
	switch (key)
	{
		case E_OPTION_WARNING:
			// Ignore certain warnings
			if (!_stricmp(value, "shadow"))
			{
				Message::SetLevel(Message::LOCAL_SHADOW, Message::E_LEVEL_IGNORE);
			}
			else if (!_stricmp(value, "eos"))
			{
				Message::SetLevel(Message::IMPLICIT_EOS, Message::E_LEVEL_IGNORE);
			}
			/*else if (!_stricmp(value, "shadow"))
			{
				Message::SetLevel(Message::LOCAL_SHADOW, Message::E_LEVEL_IGNORE);
			}
			else if (!_stricmp(value, "shadow"))
			{
				Message::SetLevel(Message::LOCAL_SHADOW, Message::E_LEVEL_IGNORE);
			}
			else if (!_stricmp(value, "shadow"))
			{
				Message::SetLevel(Message::LOCAL_SHADOW, Message::E_LEVEL_IGNORE);
			}*/
			break;
		case E_OPTION_FILE:
			m_files.Add(value);
			m_bGotFile = true;
			break;
		case E_OPTION_TARGET:
			// Target implementation
			if (!_stricmp(value, "web"))
			{
				// Load DOM definition files
				m_files.Add("web_globals.js");
				// Ignore the output -
				// this is just to load
				// the global information.
				delete & Parse();
			}
			/*else if (!_stricmp(value, "flash"))
			{
				// Load flash definition files
			}
			else if (!_stricmp(value, "yahoo"))
			{
				// Load yahoo definition files
			}
			else if (!_stricmp(value, "windows"))
			{
				// Load windows definition files
			}
			else if (!_stricmp(value, "acrobat"))
			{
				// Load acrobat definition files
			}
			else if (!_stricmp(value, "flex"))
			{
				// Load flex definition files
			}
			else if (!_stricmp(value, "max"))
			{
				// Load max/msp definition files
			}
			else if (!_stricmp(value, "windows"))
			{
				// Load windows definition files
			}
			else if (!_stricmp(value, "rhino"))
			{
				// Load rhino definition files
			}*/
			else
			{
				// Unsupported implementation
				// Should still compile, but
				// may give excess warnings.
				// TODO: Warning
				Message::Send(Message::UNKNOWN_TARGET_TYPE);
			}
			break;
		case E_OPTION_OUTPUT:
			SetOutput(value);
			break;
	}
	return true;
}

void
	Compiler::
	DoOption(int argc, char * argv [], const char * const option, const E_OPTION value, const bool par)
{
	// Loop through all the
	// given switches to
	// find the one we want
	int
		i = 0;
	while (i != argc)
	{
		if (!strcmp(argv[i], option))
		{
			// Found the option
			if (par)
			{
				// Has a parameter
				++i;
				if (i < argc)
				{
					// Given one
					if (argv[i][0] == '-')
					{
						// Another option
						Message::Send(Message::INVALID_PARAMETER, option);
					}
					else
					{
						SetOption(value, argv[i]);
						// Could return here
						// But they may decide
						// to do more.
						++i;
					}
				}
				else
				{
					// No parameter given
					Message::Send(Message::MISSING_PARAMETER, option);
				}
			}
			else
			{
				// No parameter required
				SetOption(value, "");
				++i;
			}
		}
		else
		{
			++i;
		}
	}
}

Token &
	Compiler::
	Parse()
{
	Token *
		ret;
	bool
		real = false;
	for ( ; ; )
	{
		ret = &m_parser.Statement();
		// We need to make sure this
		// is really the end of the
		// stream.  When a new file
		// is added after all the
		// others have been done, then
		// end of stream token is
		// still in the system, even
		// though it's no longer the
		// end of the stream.
		TokenType::E_TYPE
			type = ret->GetType();
		if (type == TokenType::TT__END)
		{
			if (real)
			{
				// Really is the end
				break;
			}
			else
			{
				real = true;
			}
		}
		else if (type != TokenType::TT__EOF)
		{
			break;
		}
	}
	return *ret;
}

bool
	Compiler::
	Options(int argc, char * argv [])
{
	// Do the options in the correct order.
	// This is so we don't add compiling
	// files before we add global files.
	DoOption(argc, argv, "-w", E_OPTION_WARNING, true);
	DoOption(argc, argv, "-t", E_OPTION_TARGET, true);
	DoOption(argc, argv, "-f", E_OPTION_FILE, true);
	DoOption(argc, argv, "-o", E_OPTION_OUTPUT, true);
	if (!m_out)
	{
		SetOutput("default_output.js");
	}
	return m_bGotFile;
}

void
	Compiler::
	AddFile(const char * const file)
{
	m_files.Add(file);
}

void
	Compiler::
	SetOutput(const char * const file)
{
	delete m_out;
	m_out = NULL;
	std::ostream *
		ret = NULL;
	try
	{
		ret = new std::fstream(file, std::fstream::out | std::fstream::binary);
		if (ret->fail())
		{
			Message::Send(Message::COULD_NOT_OPEN, file);
			delete ret;
		}
		else
		{
			m_out = ret;
		}
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
}
