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
//  The Original Code is the yavascript development system - TokenFactory_String.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Message.h"
#include "StringCast.h"

#include <iostream>

unsigned short
	TokenFactory::
	GetOctEscape(unsigned char & ch)
{
	// Octal code
	// \000 etc
	unsigned short
		val = 0,
		i;
	// Valid codes are:
	// {0-7}
	// {0-7}{0-7}
	// {0-3}{0-7}{0-7}
	// 0377 == 0xFF == 255
	// This makes this one much more complex
	// than the hex and unicode ones as
	// a) This one is validly variable length
	// b) It's limited to 0000-0377
	// OK, it's not MUCH more complex, but it
	// is slightly more complex
	for (i = 0; i != 3; ++i)
	{
		if (IsOct(ch))
		{
			val = (val * 8) + (ch - '0');
			ch = Read();
		}
		else
		{
			if (IsDec(ch))
			{
				// Decimal number
				// TODO: Warning
			}
			if (val > 255)
			{
				// Invalid oct number (i.e. 400+)
				// TODO: Warning
				return 255;
			}
			return val;
		}
	}
	if (IsDec(ch))
	{
		// Confusing e.g.:
		// \1234
		// Only the first three are taken
		// TODO: Warning
	}
	if (val > 255)
	{
		// Invalid oct number (i.e. 400+)
		// TODO: Warning
		return 255;
	}
	return val;
}

unsigned short
	TokenFactory::
	GetHexEscape(unsigned char & ch)
{
	unsigned short
		val = 0;
	for (int i = 0; i != 2; ++i)
	{
		if (IsDec(ch))
		{
			val = (val * 16) + (ch - '0');
		}
		else if ((unsigned char)((ch | 0x20) - 'a') < 6)
		{
			// More static maths, slightly faster than:
			// val = (val * 16) + ((ch - 'A') + 10)
			// Although the compiler could PROBABLY
			// work out the rearrangement, it may not
			val = (val * 16) + ((ch | 0x20) - 'a' + 10);
		}
		else
		{
			// TODO: Warning
			return val;
		}
		ch = Read();
	}
	if (IsHex(ch))
	{
		// Possibly ambiguous, e.g.:
		// \x0A0
		// Only two characters are used
		// TODO: Warning
	}
	return val;
}

unsigned short
	TokenFactory::
	GetUnicodeEscape(unsigned char & ch)
{
	unsigned short
		val = 0;
	for (int i = 0; i != 4; ++i)
	{
		if (IsDec(ch))
		{
			val = (val * 16) + (ch + (0 - '0'));
		}
		else if ((unsigned char)((ch | 0x20) - 'a') < 6)
		{
			// More static maths, slightly faster than:
			// val = (val * 16) + ((ch - 'A') + 10)
			// Although the compiler could PROBABLY
			// work out the rearrangement, it may not
			val = (val * 16) + ((ch | 0x20) - 'a' + 10);
		}
		else
		{
			// TODO: Warning
			return val;
		}
		ch = Read();
	}
	if (IsHex(ch))
	{
		// Possibly ambiguous, e.g.:
		// \u0A0B1
		// Only four characters are used
		// TODO: Warning
	}
	return val;
}

std::streampos
	TokenFactory::
	OutputUnicode(char * const c, std::streampos pos, unsigned short val) const
{
	// http://www.cl.cam.ac.uk/~mgk25/unicode.html#utf-8
	if (!val)
	{
		// Make it a sudo-valid UTF-8 character
		// 0x80 in UTF-8 means "1 byte, value 0"
		// It's not strictly supported (they should
		// all start with 0 or 110 but 10 is
		// THORETICALLY possible, and thus used here).
		// \000 is used as a string terminator in C
		// which we don't want as it's not in ECMA.
		c[pos] = (char)0x80;
	}
	else if (val < 0x80)
	{
		// Regular ASCII
		c[pos] = (unsigned char)val;
	}
	else
	{
		// Determine the length of the unicode
		if (val <= 0x07FF)
		{
			// Two bytes
			c[pos] = 0xC0 | (val >> 6);
			pos += 1;
			c[pos] = 0x80 | (val & 0x3F);
		}
		else if (val <= 0xFFFF)
		{
			// Three bytes
			// Don't need masking on the first one
			// The check above ensures it will be in range
			c[pos] = 0xE0 | (val >> 12);
			pos += 1;
			c[pos] = 0x80 | ((val >> 6) & 0x3F);
			pos += 1;
			c[pos] = 0x80 | (val & 0x3F);
		}
		// Can't have longer in javascript
	}
	pos += 1;
	return pos;
}

Token &
	TokenFactory::
	DoString(const unsigned char end)
{
	// Get the position of the start of this string
	// Note that this is within the string
	// it does not include the start " or '
	unsigned char
		ch;
	std::streampos
		pos = m_sCur->tellg();
	bool
		escape = false;
	for ( ; ; )
	{
		// Find the REAL end of the string
		ch = Read();
		if (escape)
		{
			// Last character was a \
			// Treat specially
			if (!IsOct(ch))
			{
				// Not an octal character code
				switch (ch)
				{
					case '\0':
						// End of file reached
						Message::Send(Message::UNEXPECTED_EOF, "End Of String");
						return Create(TokenType::TT__EOF);
					case '\r':
						// MAY need to handle two together
						IncLine();
						ch = Read();
						if (ch != '\n')
						{
							// Not a CR/LF ending
							// Don't escape multiple lines
							m_sCur->unget();
						}
						break;
					case '\n':
						IncLine();
						// AFAIK \n\r is not used anywhere for new line
						// \n = Unix
						// \r\n = Windows
						// \r = Something
					// FALLTHROUGH
					case '"':
					case 'n':
					case 'r':
					case 't':
					case 'b':
					case 'f':
					case 'v':
					case '\'':
					case '\\':
						// Valid escape characters
					case 'u':
						// Unicode character
					case 'x':
						// Hex character
					case '/':
						// Not really valid
						// but used to counter
						// HTML parsing bugs
						break;
					default:
						// Invalid escape character
						// Complain!
						Message::Send(Message::INVALID_ESCAPE_SEQUENCE, SC::L(ch));
						break;
				}
			}
			// Escaped character handled
			escape = false;
		}
		else
		{
			// Can't put end in the switch unfortunately
			if (ch == end)
			{
				// Get the length of the string to store
				// Note that this INCLUDES the end quote
				// but this extra character will be used for NULL
				std::streampos
					len = m_sCur->tellg();
				len -= pos;
				if (len == std::streampos(1))
				{
					// No string exists
					return Create("", TokenType::TT_STRING);
				}
				// Allocate temporary space on the stack
				// full malloc isn't really needed
				// 
				// Although the string being written is NOT
				// the same as the string being read it can't
				// be longer than the source as qualified
				// escape sequences will ALL end up shorter
				// than their original counterparts.
				char *
					c = (char *)alloca(len);
				// This uses alloca, so don't need cleanup
				if (c)
				{
					m_sCur->seekg(pos);
					pos = 0;
					ch = Read();
					len -= 1;
					while (len)
					{
						if (ch == '\\')
						{
							// Get the escaped character
							// may not need to output it
							ch = Read();
							len -= 1;
							if (IsOct(ch))
							{
								// TODO: Deprecation warning
								// Output unicode where appropriate
								// Adjust the characters left to read
								len += m_sCur->tellg();
								pos = OutputUnicode(c, pos, GetOctEscape(ch)); // ch REFERENCE
								// Readjust the number of characters to read
								len -= m_sCur->tellg();
								// Need to tell the sytem we've read a lot
								// of characters at once in the functions.
								continue;
							}
							else
							{
								switch (ch)
								{
									case 'n':
										// New line
										ch = '\n';
										break;
									case 'r':
										// Carriage return
										ch = '\r';
										break;
									case 't':
										// Tab
										ch = '\t';
										break;
									case 'b':
										// Backspace
										ch = '\b';
										break;
									case 'f':
										// Form feed
										ch = '\f';
										break;
									case 'v':
										// Vertical tab
										ch = '\v';
										break;
									case '/':
										// Keep this escape
										// for compatability
										c[pos] = '\\';
										pos += 1;
										break;
									case 'u':
										// Unicode character, needs encoding
										// Javascript is UTF-16, this is UTF-8
										len += m_sCur->tellg();
										ch = Read();
										pos = OutputUnicode(c, pos, GetUnicodeEscape(ch)); // ch REFERENCE
										len -= m_sCur->tellg();
										continue;
									case 'x':
										// HEX escape sequence
										len += m_sCur->tellg();
										ch = Read();
										pos = OutputUnicode(c, pos, GetHexEscape(ch)); // ch REFERENCE
										len -= m_sCur->tellg();
										continue;
									case '\n':
									case '\r':
										// Skip newline
										ch = Read();
										if (ch == '\n')
										{
											// \r\n
											// May also be \n\n which would already
											// be known to be invalid from above
											// Two newlines in a row are valid,
											// but not when the second isn't escaped
											// and is in a string
											ch = Read();
										}
										len -= 1;
										// \r only so already got the next character
										continue;
									case '"':
									case '\'':
									case '\\':
										// Above three stated explicitly for obviousness
									default:
										// Invalid escape characters
										// Or " and ' which don't now need escapes
										// The type of string enclosing will determine
										// which of " or ' get escaped.  For example:
										// "Hello \"Alex\""
										// will become:
										// 'Hello "Alex"'
										// So that the "s don't need escaping.
										// "Hi \'\'\""
										// Will become:
										// "Hi ''\""
										// So that the least number of quotes need escaping
										// 
										// Invalid escape sequences are handled above
										// don't re-warn down here
										break;
								}
							}
						}
						// Save the character and get the next
						c[pos] = ch;
						pos += 1;
						ch = Read();
						len -= 1;
					}
					c[pos] = '\0';
					return Create(c, TokenType::TT_STRING);
				}
				else
				{
					// Out of memory
					Message::Send(Message::OUT_OF_MEMORY);
				}
				return Create(TokenType::TT__NONE);
			}
			else
			{
				switch (ch)
				{
					case '\0':
						// End of file reached
						Message::Send(Message::UNEXPECTED_EOF, SC::L(end));
						return Create(TokenType::TT__EOF);
					case '\r':
					case '\n':
						// Unclosed string or unescaped EOL
						Message::Send(Message::UNCLOSED_STRING_LITERAL);
						m_sCur->unget();
						// TODO: Make it return as much as it's got
						// I'm not sure which is preferable, either
						// way it's a error so doesn't really matter
						return GetNext();
					case '\\':
						// Escape
						escape = true;
						break;
				}
			}
		}
	}
	// No break as it never gets here
}
