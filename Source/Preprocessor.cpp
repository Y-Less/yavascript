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
//  The Original Code is the yavascript development system - Preprocessor.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Preprocessor.h"

#include "Message.h"
#include "Generator.h"
#include "Compiler.h"
#include "StringCast.h"

#include "Tokens/TNumber.h"
#include "Tokens/TString.h"

#include <iostream>
#include <exception>
#include <sstream>

void
	Preprocessor::
	DoDirective(TokenFactory & input)
{
	m_pFactory = &input;
	// Got a directive
	PreprocType::E_PREPROC
		type = GetType();
	switch (type)
	{
		case PreprocType::PP_IF:
		{
			++m_indent;
			m_cur = NULL;
			try
			{
				Token &
					condition = Expression(0);
				delete m_cur;
				if (!DoExpr(condition))
				{
					// FALSE
					if (!SkipTo())
					{
						// Reached the #endif
						--m_indent;
					}
					// Skip lines in between
				}
				delete &condition;
				return;
			}
			catch (int)
			{
				// Skip the expression
				// FALSE
				if (!SkipTo())
				{
					// Reached the #endif
					--m_indent;
				}
			}
			break;
		}
		case PreprocType::PP_IFDEF:
		{
			++m_indent;
			char *
				ch = GetDefineName();
			if (ch)
			{
				if (!Defined(ch))
				{
					// Not defined, skip
					// the conditional code
					if (!SkipTo())
					{
						// Reached the #endif
						--m_indent;
					}
				}
			}
			else
			{
				Message::Send(Message::INVALID_MACRO);
				if (!SkipTo())
				{
					// Reached the #endif
					--m_indent;
				}
			}
			break;
		}
		case PreprocType::PP_IFNDEF:
		{
			++m_indent;
			char *
				ch = GetDefineName();
			if (ch)
			{
				if (Defined(ch))
				{
					// Defined, skip
					// the conditional code
					if (!SkipTo())
					{
						// Reached the #endif
						--m_indent;
					}
				}
			}
			else
			{
				Message::Send(Message::INVALID_MACRO);
				if (!SkipTo())
				{
					// Reached the #endif
					--m_indent;
				}
			}
			break;
		}
		case PreprocType::PP_ELSE:
		{
			// If we're here, the #if
			// was true that means the
			// #else should be skipped
			if (!m_indent)
			{
				Message::Send(Message::UNMATCHED_PELSE);
			}
			if (SkipTo())
			{
				Message::Send(Message::MISSING_ENDIF);
			}
			--m_indent;
			break;
		}
		case PreprocType::PP_ENDIF:
		{
			if (m_indent)
			{
				--m_indent;
			}
			else
			{
				Message::Send(Message::UNMATCHED_ENDIF);
			}
			break;
		}
		case PreprocType::PP_DEFINE:
		{
			char *
				ch = GetDefineName();
			if (ch)
			{
				if (Defined(ch))
				{
					// Exists
					Message::Send(Message::MACRO_EXISTS, ch);
				}
				char *
					tmp = GetLine(true);
				m_defines[ch] = tmp;
				// tmp will be converted to a new string
				// and that will be saved, so we can
				// get rid of the temporary chars.
				delete [] tmp;
			}
			else
			{
				Message::Send(Message::INVALID_MACRO);
			}
			// Don't discard the rest of the line
			return;
		}
		case PreprocType::PP_UNDEF:
		{
			char *
				ch = GetDefineName();
			if (ch)
			{
				if (m_defines.count(ch))
				{
					m_defines.erase(ch);
				}
				else
				{
					Message::Send(Message::UNDEFINED_MACRO);
				}
			}
			else
			{
				Message::Send(Message::INVALID_MACRO);
			}
			break;
		}
		case PreprocType::PP_INCLUDE:
		{
			m_cur = NULL;
			try
			{
				Token &
					condition = Expression(0);
				delete m_cur;
				if (condition.GetType() == TokenType::TT_STRING)
				{
					Compiler::Get().AddFile(dynamic_cast<TString *>(&condition)->GetString());
				}
				else
				{
					Message::Send(Message::COULD_NOT_OPEN, "Invalid file name");
				}
				delete &condition;
				return;
			}
			catch (int)
			{
				// Don't include
			}
			break;
		}
		case PreprocType::PP_PRAGMA:
		{
			// Currently have no pragma directives
			// Here for future expansion.
			break;
		}
		default:
		{
			Message::Send(Message::UNKNOWN_DIRECTIVE);
			break;
		}
	}
	// Skip the rest of the line
	GetLine(false);
}

void
	Preprocessor::
	CheckEnd()
{
	if (m_indent)
	{
		Message::Send(Message::MISSING_ENDIF);
	}
}	

#define EXP(n) DoExpr(t.GetChild(n))
#define IXP(n) (long long)DoExpr(t.GetChild(n))
#define UXP(n) (unsigned long long)DoExpr(t.GetChild(n))

double
	Preprocessor::
	DoExpr(Token & t)
{
	// Recursively evaluate
	// the determined expression
	switch (t.GetType())
	{
		// Do something based on
		// token ooperator type
		case TokenType::TT_NUMBER:
			return dynamic_cast<TNumber *>(&t)->GetNumeric();
		case TokenType::TO_ADD:			// +
			if (t.GetChildCount() == 2)
			{
				return EXP(0) + EXP(1);
			}
			else
			{
				return EXP(0);
			}
		case TokenType::TO_NOT:			// !
			return !EXP(0);
		case TokenType::TO_NOT_CMP:		// !=
		case TokenType::TO_NOT_EQUIV:	// !==
			return EXP(0) != EXP(1);
		case TokenType::TO_MOD:			// %
			return (double)(IXP(0) % IXP(1));
		case TokenType::TO_BAND:		// &
			return (double)(IXP(0) & IXP(1));
		case TokenType::TO_LAND:		// &&
			return EXP(0) && EXP(1);
		case TokenType::TO_MUL:			// *
			return EXP(0) * EXP(1);
		case TokenType::TO_SUB:			// -
			if (t.GetChildCount() == 2)
			{
				return EXP(0) - EXP(1);
			}
			else
			{
				return -EXP(0);
			}
		case TokenType::TO_DIV:			// /
			return EXP(0) / EXP(1);
		case TokenType::TO_LT:			// <
			return EXP(0) < EXP(1);
		case TokenType::TO_LS:			// <<
			return (double)(IXP(0) << IXP(1));
		case TokenType::TO_LTE:			// <=
			return EXP(0) <= EXP(1);
		case TokenType::TO_COMPARE:		// ==
		case TokenType::TO_EQUIV:		// ===
			return EXP(0) == EXP(1);
		case TokenType::TO_GT:			// >
			return EXP(0) > EXP(1);
		case TokenType::TO_GTE:			// >=
			return EXP(0) >= EXP(1);
		case TokenType::TO_RS:			// >>
			return (double)(IXP(0) >> IXP(1));
		case TokenType::TO_RSU:			// >>>
			return (double)(UXP(0) >> UXP(1));
		case TokenType::TO_XOR:			// ^
			return (double)(IXP(0) ^ IXP(1));
		case TokenType::TO_BOR:			// |
			return (double)(IXP(0) | IXP(1));
		case TokenType::TO_LOR:			// ||
			return EXP(0) || EXP(1);
		case TokenType::TO_INV:			// ~
			return (double)(~IXP(0));
	}
	return 0.0;
}

char *
	Preprocessor::
	GetLine(const bool save)
{
	std::streampos
		pos = m_pFactory->m_sCur->tellg(),
		len;
	unsigned char
		ch;
	bool
		escape;
	do
	{
		// Get the current character
		ch = m_pFactory->Read();
		// Constantly update our position
		// Comments may or may not be
		// included in this text block.  If
		// they aren't then we need the
		// position before they're read
		// without knowing in advance that
		// they won't be included.
		escape = false;
		if (save)
		{
			if (!ch)
			{
				// At the end of the file
				m_pFactory->m_sCur->clear();
				len = 1;
			}
			else
			{
				len = 0;
			}
			len += m_pFactory->m_sCur->tellg();
		}
		switch (ch)
		{
			case '\'':
				// In a string, ignore
				// comment-like things.
				do
				{
					ch = m_pFactory->Read();
					if (escape)
					{
						if (ch == '\r' || ch == '\n')
						{
							// Illegal
							Message::Send(Message::UNCLOSED_STRING_LITERAL);
							break;
						}
						escape = false;
					}
					else
					{
						if (ch == '\'')
						{
							break;
						}
						else if (ch == '\\')
						{
							escape = true;
						}
						else if (ch == '\r' || ch == '\n')
						{
							// Illegal
							Message::Send(Message::UNCLOSED_STRING_LITERAL);
							escape = true;
							break;
						}
					}
				}
				while (ch);
				if (!ch)
				{
					// EOF
					Message::Send(Message::UNEXPECTED_EOF);
				}
				break;
			case '"':
				// In a string, ignore
				// comment-like things.
				do
				{
					ch = m_pFactory->Read();
					if (escape)
					{
						escape = false;
						if (ch == '\r' || ch == '\n')
						{
							// Illegal
							Message::Send(Message::UNCLOSED_STRING_LITERAL);
							break;
						}
					}
					else
					{
						if (ch == '"')
						{
							break;
						}
						else if (ch == '\\')
						{
							escape = true;
						}
						else if (ch == '\r' || ch == '\n')
						{
							// Illegal
							Message::Send(Message::UNCLOSED_STRING_LITERAL);
							break;
						}
					}
				}
				while (ch);
				if (!ch)
				{
					// EOF
					Message::Send(Message::UNEXPECTED_EOF);
				}
				break;
			case '/':
				// Maybe comment
				if (SkipComment(ch) == 2)
				{
					// Passed the end of the
					// line in the comment
					escape = true;
				}
				break;
			case '\n':
			case '\r':
				// Exit
				m_pFactory->Unget();
				escape = true;
				break;
		}
	}
	while (ch && !escape);
	// Got the end of the line, or
	// as much of it as required.
	// Save it.
	if (save)
	{
		// Used so multi-line comments
		// aren't included in the output
		// but also aren't read twice by
		// the tokeniser (which would
		// break the line counting).
		std::streampos
			end;
		if (!ch)
		{
			// At the end of the file
			m_pFactory->m_sCur->clear();
			end = 1;
		}
		else
		{
			end = 0;
		}
		end += m_pFactory->m_sCur->tellg();
		char *
			c = NULL;
		len -= pos;
		try
		{
			c = new char[len];
			// Get the start of the symbol and read
			m_pFactory->m_sCur->seekg(pos);
			len -= 1;
			// This will move the stream pointer
			// to the end of the current symbol
			m_pFactory->m_sCur->read(c, len);
			c[len] = '\0';
			if (m_pFactory->m_sCur->bad())
			{
				// Error reading
				Message::Send(Message::INPUT_STREAM_ERROR);
			}
			else
			{
				// Skip past the comments
				m_pFactory->m_sCur->seekg(end);
				return c;
			}
		}
		catch (std::exception e)
		{
			delete c;
			m_pFactory->m_sCur->unget();
			Message::Send(Message::OUT_OF_MEMORY);
		}
		// Skip past the comments
		m_pFactory->m_sCur->seekg(end);
	}
	return NULL;
}

char *
	Preprocessor::
	GetDefineName()
{
	unsigned char
		ch;
	if (SkipWhitespace(ch)) // ch reference
	{
		// Don't have a name
		return NULL;
	}
	// At the start of something none-whitespace
	if (TokenFactory::IsSym(ch))
	{
		// Get the symbol start
		std::streampos
			pos = m_pFactory->m_sCur->tellg();
		pos -= 1;
		do
		{
			ch = m_pFactory->Read();
		}
		while (TokenFactory::IsSym(ch) || TokenFactory::IsDec(ch));
		// Same as regular identifiers
		// Can start with $, _, a-z, A-Z
		// Can also CONTAIN 0-9
		std::streampos
			len;
		if (!ch)
		{
			// At the end of the file
			m_pFactory->m_sCur->clear();
			len = 1;
		}
		else
		{
			len = 0;
		}
		len += m_pFactory->m_sCur->tellg();
		len -= pos;
		// Save the string somewhere
		char *
			c = NULL;
		try
		{
			c = new char[len];
			// Get the start of the symbol and read
			m_pFactory->m_sCur->seekg(pos);
			len -= 1;
			// This will move the stream pointer
			// to the end of the current symbol
			m_pFactory->m_sCur->read(c, len);
			c[len] = '\0';
			if (m_pFactory->m_sCur->bad())
			{
				// Error reading
				Message::Send(Message::INPUT_STREAM_ERROR);
			}
			else
			{
				return c;
			}
		}
		catch (std::exception e)
		{
			delete c;
			Message::Send(Message::OUT_OF_MEMORY);
		}
	}
	return NULL;
}

bool
	Preprocessor::
	SkipTo()
{
	// Skips to the matching
	// #else or #endif for the
	// current #if.
	// Used to skip text when
	// a #if is false to fully
	// not evaluate the code.
	for ( ; ; )
	{
		unsigned char
			ch;
		SkipWhitespace(ch);
		if (ch == '#')
		{
			switch (GetType())
			{
				case PreprocType::PP_IF:
				case PreprocType::PP_IFDEF:
				case PreprocType::PP_IFNDEF:
					// #if block in the false
					// area, skip over it.
					if (SkipTo())
					{
						// Got an #else
						// Go to the #endif
						if (SkipTo())
						{
							Message::Send(Message::MISSING_ENDIF);
						}
					}
					break;
				case PreprocType::PP_ELSE:
					// Found else
					GetLine(false);
					return true;
				case PreprocType::PP_ENDIF:
					// Found elseif
					GetLine(false);
					return false;
			}
		}
		else if (ch == '\r')
		{
			// Discard that character
			// (was put back before)
			m_pFactory->Read();
			ch = m_pFactory->Read();
			if (ch != '\n')
			{
				m_pFactory->Unget();
			}
			m_pFactory->IncLine();
		}
		else if (ch == '\n')
		{
			m_pFactory->Read();
			m_pFactory->IncLine();
		}
		else if (ch == '\0')
		{
			Message::Send(Message::MISSING_ENDIF);
			return false;
		}
		else
		{
			GetLine(false);
		}
	}
}

bool
	Preprocessor::
	SkipWhitespace(unsigned char & ch)
{
	ch = m_pFactory->Read();
	// Skip leading whitespace
	char
		sc;
	do
	{
		// Skip leading whitespace
		while (ch <= ' ')
		{
			if (ch == '\r' || ch == '\n')
			{
				m_pFactory->Unget();
				// Had a new line - bad
				return true;
			}
			else if (!ch)
			{
				return true;
			}
			ch = m_pFactory->Read();
		}
		// Skip comments
		sc = SkipComment(ch);
		if (sc == 2)
		{
			// Has a new line - bad
			return true;
		}
	}
	while (sc == 1);
	return false;
}

PreprocType::E_PREPROC
	Preprocessor::
	GetType()
{
	// Should be after the #
	// So the next thing to be
	// read is the directive.
	// Same as ever, use a tree.
	unsigned char
		ch;
	if (SkipWhitespace(ch))
	{
		return PreprocType::PP__NONE;
	}
	// Figure out which directive they typed
	PreprocType::E_PREPROC
		type = PreprocType::PP__NONE;
	E_STATE
		state = ES__NONE;
	while (TokenFactory::IsSym(ch) || TokenFactory::IsDec(ch))
	{
		switch (state)
		{
			case ES__NONE: // ES_NONE
				switch (ch)
				{
					case 'd':
						if (m_pFactory->CheckLetters("efine"))
						{
							// #define
							state = ES__DONE;
							type = PreprocType::PP_DEFINE;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					case 'e':
						state = ES_E;
						break;
					case 'i':
						state = ES_I;
						break;
					case 'p':
						if (m_pFactory->CheckLetters("ragma"))
						{
							// #undef
							state = ES__DONE;
							type = PreprocType::PP_PRAGMA;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					case 'u':
						if (m_pFactory->CheckLetters("ndef"))
						{
							// #undef
							state = ES__DONE;
							type = PreprocType::PP_UNDEF;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					default:
						state = ES__UNKNOWN;
						break;
				}
				break;
			case ES_I:
				switch (ch)
				{
					case 'f':
						state = ES_IF;
						type = PreprocType::PP_IF;
						break;
					case 'n':
						if (m_pFactory->CheckLetters("clude"))
						{
							// #include
							state = ES__DONE;
							type = PreprocType::PP_INCLUDE;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					default:
						state = ES__UNKNOWN;
						break;
				}
				break;
			case ES_IF:
				switch (ch)
				{
					case 'd':
						if (m_pFactory->CheckLetters("ef"))
						{
							// #include
							state = ES__DONE;
							type = PreprocType::PP_IFDEF;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					case 'n':
						if (m_pFactory->CheckLetters("def"))
						{
							// #include
							state = ES__DONE;
							type = PreprocType::PP_IFNDEF;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					default:
						state = ES__UNKNOWN;
						break;
				}
				break;
			case ES_E: // ES_NONE
				switch (ch)
				{
					case 'l':
						if (m_pFactory->CheckLetters("se"))
						{
							// #else
							state = ES__DONE;
							type = PreprocType::PP_ELSE;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					case 'n':
						if (m_pFactory->CheckLetters("dif"))
						{
							// #endif
							state = ES__DONE;
							type = PreprocType::PP_ENDIF;
						}
						else
						{
							state = ES__UNKNOWN;
						}
						break;
					default:
						state = ES__UNKNOWN;
						break;
				}
				break;
			case ES__DONE:
				// Not known but starts
				// off the same as another.
				state = ES__UNKNOWN;
				break;
			default:
				// Not as complex as in
				// TokenFactory_Symbol as
				// we don't care about
				// unknown symbols here
				break;
		}
		ch = m_pFactory->Read();
	}
	m_pFactory->Unget();
	if (state == ES__UNKNOWN)
	{
		return PreprocType::PP__NONE;
	}
	return type;
}

bool
	Preprocessor::
	Defined(std::string key)
{
	return m_defines.count(key) != 0;
}

std::istream *
	Preprocessor::
	Get(std::string key)
{
	std::istream *
		ret = NULL;
	try
	{
		ret = new std::istringstream(m_defines[key], std::istringstream::binary | std::istringstream::in);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return ret;
}

char
	Preprocessor::
	SkipComment(unsigned char & ch)
{
	// Skip comments and return true
	// if there was a comment and it
	// included a new line.
	if (ch == '/')
	{
		ch = m_pFactory->Read();
		// Go on the next character
		if (ch == '\0')
		{
			return 0;
		}
		else if (ch == '/')
		{
			// //
			do
			{
				// Skip text to the end of the line
				ch = m_pFactory->Read();
			}
			while (ch != '\0' && ch != '\r' && ch != '\n');
			m_pFactory->Unget();
			return 2;
		}
		else if (ch == '*')
		{
			// /*
			ch = m_pFactory->Read();
			int
				lc = m_pFactory->GetLine();
			for ( ; ; )
			{
				// One of the few places where unget isn't required
				// Either it is /, in which case we can skip it
				// or it isn't, in which case it's ignored
				// Could have **/ (or ***/ etc)
				while (ch == '*')
				{
					ch = m_pFactory->Read();
					if (ch == '/')
					{
						// End of the comment
						// Skip this token and proceed to the next
						if (lc == m_pFactory->GetLine())
						{
							// Didn't skip a line
							ch = m_pFactory->Read();
							return 1;
						}
						else
						{
							// Did skip a line
							return 2;
						}
					}
				}
				if (ch == '\0')
				{
					// Reached end of file before end of comment
					return 2;
				}
				else if (ch == '\r')
				{
					m_pFactory->IncLine();
					ch = m_pFactory->Read();
					// \r\n newline
					if (ch != '\n')
					{
						continue;
					}
				}
				else if (ch == '\n')
				{
					m_pFactory->IncLine();
				}
				ch = m_pFactory->Read();
			}
			// Will never get here
			// Either the comment will end or the file will end
			// and both are handled above
		}
	}
	return 0;
}

Token &
	Preprocessor::
	Statement(const bool group, const char * const label)
{
	Message::Send(Message::COMPLEX_PREPROC);
	delete [] label;
	throw 0;
	return Generator::Null();
}

Token &
	Preprocessor::
	Expression(const int rbp)
{
	Token
		*t,
		*left;
	t = &GetCurrent();
	// Move on for the NUD function
	Advance();
	// Anything here is either unary or
	// in the wrong place
	left = &t->NUD(*this);
	// Is in the wrong place at the wrong time
	if (t->Disposable())
	{
		// Not a NUD
		// Delete it here as it's after
		// the correct Advance
		delete t;
	}
	t = &GetCurrent();
	while (rbp < t->GetLBP())
	{
		Advance();
		left = &t->LED(*this, *left);
		if (t->Disposable())
		{
			// Not needed
			delete t;
		}
		t = &GetCurrent();
	}
	// Probably the end of an expression
	// But found something that shouldn't be there
	if (t->GetLBP() < 0 && rbp == 0)
	{
		// Didn't get operator
		// Got a new token on the same line
		Message::Send(Message::EXPECTED_OPERATOR, SC::R(*t));
	}
	return *left;
}

Token &
	Preprocessor::
	Advance(const TokenType::E_TYPE type)
{
	if (type != TokenType::TT__NONE)
	{
		if (m_cur->GetType() != type)
		{
			if (m_cur->GetType() == TokenType::TT__EOF || m_cur->GetType() == TokenType::TT__END)
			{
				Message::Send(Message::UNEXPECTED_EOF);
			}
			else
			{
				Message::Send(Message::EXPECTED_TOKEN, SC::L(type), SC::R(*m_cur));
			}
			return *m_cur;
		}
		// Check call, don't actually need
		// the token
		m_cur->Dispose();
	}
	Token &
		ret = m_pFactory->GetNext();
	switch (ret.GetType())
	{
		case TokenType::TT__EOF:
		case TokenType::TT__END:
		case TokenType::TT_EOL:
		case TokenType::TT_NUMBER:
		case TokenType::TT_STRING:
		case TokenType::TO_ADD:			// +
		case TokenType::TO_NOT:			// !
		case TokenType::TO_NOT_CMP:		// !=
		case TokenType::TO_NOT_EQUIV:	// !==
		case TokenType::TO_MOD:			// %
		case TokenType::TO_BAND:		// &
		case TokenType::TO_LAND:		// &&
		case TokenType::TO_BRACKET_O:	// (
		case TokenType::TO_BRACKET_C:	// )
		case TokenType::TO_MUL:			// *
		case TokenType::TO_SUB:			// -
		case TokenType::TO_DIV:			// /
		case TokenType::TO_LT:			// <
		case TokenType::TO_LS:			// <<
		case TokenType::TO_LTE:			// <=
		case TokenType::TO_COMPARE:		// ==
		case TokenType::TO_EQUIV:		// ===
		case TokenType::TO_GT:			// >
		case TokenType::TO_GTE:			// >=
		case TokenType::TO_RS:			// >>
		case TokenType::TO_RSU:			// >>>
		case TokenType::TO_XOR:			// ^
		case TokenType::TO_BOR:			// |
		case TokenType::TO_LOR:			// ||
		case TokenType::TO_INV:			// ~
			// Valid in constants
			break;
		default:
			Message::Send(Message::COMPLEX_PREPROC);
			delete &ret;
			throw 0;
			m_cur = &Generator::Null();
			return *m_cur;
	}
	m_cur = &ret;
	return ret;
}
