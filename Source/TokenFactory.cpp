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
//  The Original Code is the yavascript development system - TokenFactory.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Tokens/TNumber.h"
#include "Tokens/TString.h"
#include "Tokens/TSymbol.h"
#include "Tokens/TRegex.h"
#include "Tokens/TNull.h"
#include "Tokens/TGen.h"

#include "Tokens/Operators/TOEOS.h"

#include "StringCast.h"

#include "Message.h"
#include "Compiler.h"

#include <iostream>

#ifndef alloca
	#include <alloca.h>
#endif

// cons
	TokenFactory::
	TokenFactory(std::istream & input, char * const szName) :
		m_isInput(input),
		m_ttLast(TokenType::TT__NONE),
		m_szStreamName(szName),
		m_line(1),
		m_regex(true),
		m_sCur(NULL),
		m_newLine(true)
{
}

// Sort out the streams
// then get the next token
Token &
	TokenFactory::
	GetNext()
{
	// Set file information for errors
	Message::SetValues(m_szStreamName, m_line);
	if (m_altIn.empty())
	{
		// Default stream
		m_sCur = &m_isInput;
		Token &
			ret = DoGetNext();
		return ret;
	}
	else
	{
		// Get the next token
		m_sCur = m_altIn.top();
		Token &
			ret = DoGetNext();
		// Check if this is the
		// end of the stream.
		m_sCur->peek();
		if (m_sCur->eof())
		{
			// Yes - pop it
			std::istream *
				latest = m_altIn.top();
			m_altIn.pop();
			// Remove the memory
			delete latest;
		}
		return ret;
	}
}

void
	TokenFactory::
	IncLine()
{
	if (m_altIn.empty())
	{
		// Only increase if
		// we're working in the
		// original stream
		Message::SetValues(m_szStreamName, ++m_line);
	}
}
// Actually get the next token
Token &
	TokenFactory::
	DoGetNext()	
{
	// Get the next character in the stream
	// to determine what to do next
	unsigned char
		ch = Read();
	
// =====================
//  START: Preprocessor
// =====================
	
	if (m_newLine)
	{
		// Update line position
		//IncLine();
		m_newLine = false;
		// Check for pre-processor directives
		if (ch == '#')
		{
			Compiler::Get().GetPreprocessor().DoDirective(*this);
			return Create(TokenType::TT_EOL);
		}
	}
	
// ===================
//  START: Whitespace
// ===================
	
	// Return New Line
	bool
		rnl = false; // I keep calling this RNLI...
	while (ch <= ' ')
	{
		switch (ch)
		{
			case '\0':
				// End of file
				return Create(TokenType::TT__EOF);
			case ' ':
			case '\t':
				// Regular space
				break;
			case '\r':
				// New line
				rnl = true;
				// Increase the current line number
				IncLine();
				ch = Read();
				// Only increment one for \r\n
				if (ch == '\n')
				{
					break;
				}
				continue;
			case '\n':
				// New line
				rnl = true;
				// Increment line counter
				IncLine();
				break;
			default:
				// Unknown character (bell, vtab etc)
				Message::Send(Message::INVALID_CHARACTER);
				break;
		}
		ch = Read();
	}
	if (rnl)
	{
		// Found a new line (and skipped it)
		m_newLine = true;
		Unget();
		if (m_ttLast == TokenType::TT_EOL || m_ttLast == TokenType::TT_EOS)
		{
			// Last token was also a new line
			// This only happens when there's only
			// comments between two new lines
			return GetNext();
		}
		else
		{
			// Should we create a new line here?
			// Only make one if it's possible for the last token to be an EOS
			// It may not be but reduce the number to check later
			// Return a new line for later processing
			return Create(TokenType::TT_EOL);
		}
	}
	
// =================
//  END: Whitespace
// =================
	
// ===============
//  START: Number
// ===============
	
	// Unsigned comparison
	if (IsDec(ch) || ch == '.')
	{
		// For now just get the string version of the number
		// if we need it's value for later optimisations we
		// can calculate it at the time.  But atm the more
		// important thing is to maintain accuaracy,
		// converting to a double may loose some accuacy the
		// interpreter might not, or may mess up the number
		// more by being approximated twice on different
		// architectures.
		return DoNumber(ch);
	}
	
// =============
//  END: Number
// =============
	
// ===============
//  START: Symbol
// ===============
	
	// Only check IsSym as numbers aren't valid
	// for the start of a symbol, only in one
	if (IsSym(ch))
	{
		return DoSymbol(ch);
	}
	
// =============
//  END: Symbol
// =============
	
// ==============
//  START: Other
// ==============
	
	// No more ranges to deal with
	// Just switch by the character
	switch (ch)
	{
	// ==============
	//  START: Slash
	// ==============
		
		case '/':
			// Could be a block comment, line comment, regex or division
			// Very annoying!
			// New lines in block comments DO NOT act as new lines
			ch = Read();
			// Go on the next character
			if (ch == '\0')
			{
				Message::Send(Message::UNEXPECTED_EOF, "rvalue");
				return Create(TokenType::TO_DIV);
			}
			else if (ch == '/')
			{
				// //
				do
				{
					// Skip text to the end of the line
					ch = Read();
				}
				while (ch != '\0' && ch != '\r' && ch != '\n');
				// On default windows (CR/LF) this unget isn't needed
				// However on other systems, and even on Windows sometimes
				// only CR or LF are used, which would entirely loose the new line
				Unget();
				// Skip the comment and return the next token
				return GetNext();
			}
			else if (ch == '*')
			{
				// /*
				ch = Read();
				for ( ; ; )
				{
					// One of the few places where unget isn't required
					// Either it is /, in which case we can skip it
					// or it isn't, in which case it's ignored
					// Could have **/ (or ***/ etc)
					while (ch == '*')
					{
						ch = Read();
						if (ch == '/')
						{
							// End of the comment
							// Skip this token and proceed to the next
							return GetNext();
						}
					}
					if (ch == '\0')
					{
						// Reached end of file before end of comment
						Message::Send(Message::UNCLOSED_COMMENT);
						return Create(TokenType::TT__EOF);
					}
					else if (ch == '\r')
					{
						IncLine();
						ch = Read();
						// \r\n newline
						if (ch != '\n')
						{
							continue;
						}
					}
					else if (ch == '\n')
					{
						IncLine();
					}
					ch = Read();
				}
				// Will never get here
				// Either the comment will end or the file will end
				// and both are handled above
			}
			else
			{
				// Fixed a minor bug with:
				// a = 3/2;
				// Where the 2 wouldn't get parsed.
				// and with:
				// a = /reg/
				// where the first character was missed
				Unget();
				if (m_regex)
				{
					return DoRegex();
				}
				return DoOperator('/');
			}
		
	// ============
	//  END: Slash
	// ============
		
	// ==================
	//  START: Semicolon
	// ==================
		
		case ';':
			// Change [;]+ to ;
			/*if (m_ttLast == TokenType::TT_EOS)
			{
				return GetNext();
			}*/
			// Removed the multiple semicolon optimisation
			// I realised that:
			// for ( ; ; )
			// Gets ruined by it despite being valid.
			return Create(TokenType::TT_EOS);
		
	// ================
	//  END: Semicolon
	// ================
		
	// ===============
	//  START: String
	// ===============
		
		case '\'':
			return DoString('\'');
		
		case '"':
			return DoString('"');
		
	// =============
	//  END: String
	// =============
	}
	
// ============
//  END: Other
// ============
	
// =================
//  START: Operator
// =================
	
	return DoOperator(ch);
	
// ===============
//  END: Operator
// ===============
}

Token &
	TokenFactory::
	Create(const char * const str, const TokenType::E_TYPE type)
{
	// If we're lucky the compiler will optimise
	// most of this function away
	Token
		*t = NULL;
	try
	{
		switch (type)
		{
			case TokenType::TT_STRING:
				t = new TString(str);
				break;
			case TokenType::TT_SYMBOL:
				t = new TSymbol(str);
				break;
			case TokenType::TT_REGEX:
				t = new TRegex(str);
				break;
			case TokenType::TT_NUMBER:
				t = new TNumber(str);
				break;
		}
		m_ttLast = type;
	}
	catch (std::exception)
	{
		delete t;
		t = NULL;
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *t;
}

Token &
	TokenFactory::
	Create(const TokenType::E_TYPE type)
{
	Token
		*t = NULL;
	try
	{
		if (TokenType::IsGlobal(type))
		{
			t = CreateGlobal(type);
		}
		else if (TokenType::IsKeyword(type))
		{
			t = CreateKeyword(type);
		}
		else if (TokenType::IsReserved(type))
		{
			t = CreateReserve(type);
		}
		else if (TokenType::IsOperator(type))
		{
			t = CreateOperator(type);
		}
		else
		{
			switch (type)
			{
				case TokenType::TT_EOS:
					t = new TOEOS();
					break;
				case TokenType::TT__EOF:
				case TokenType::TT_EOL:
					t = new TGen(type);
					break;
				case TokenType::TT__NONE:
					t = new TNull();
					break;
				default:
					Message::Send(Message::UNKNOWN_TOKEN_TYPE);
					break;
					// Unknown type
			}
		}
		m_ttLast = type;
	}
	catch (std::exception)
	{
		delete t;
		t = NULL;
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *t;
}

unsigned char
	TokenFactory::
	Read()
{
	char
		ret;
	// Get a single character and check it suceeded
	if (m_sCur->get(ret).fail())
	{
		if (m_sCur->bad())
		{
			// Should be a fatal error
			Message::Send(Message::INPUT_STREAM_ERROR);
		}
		// Just EOF
		return '\0';
	}
	return (unsigned char)ret;
}

bool
	TokenFactory::
	CheckLetters(const char * str)
{
	// This function loops through a string and
	// checks if the remainder exactly matches the given
	// string.  The string it's comparing is read from
	// the input stream
	if (m_sCur->eof())
	{
		// End of file
		// Return easily
		return false;
	}
	char
		ch;
	// Lop through the string
	while (*str)
	{
		// Get a character from the stream
		m_sCur->get(ch);
		// Something went wrong reading the stream
		if (m_sCur->fail())
		{
			if (m_sCur->bad())
			{
				// Should be a fatal error
				Message::Send(Message::INPUT_STREAM_ERROR);
			}
			// Just an EOF
			return false;
		}
		// Compare the characters
		else if (ch != *str++)
		{
			// Put the bad character back
			Unget();
			return false;
		}
	}
	// All the same
	return true;
}
