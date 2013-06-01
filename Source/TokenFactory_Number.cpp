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
//  The Original Code is the yavascript development system - TokenFactory_Number.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TokenFactory.h"

#include "Message.h"

#include <iostream>

Token &
	TokenFactory::
	DoNumber(unsigned char ch)
{
	// Determine what sort of number this is
	// and save it as a DECIMAL string (for ease
	// of processing later).  Note that octal
	// numbers are technically deprecated.
	// 
	// Get the current stream position.
	// This is actually AFTER the first
	// character in the number, however this
	// may not matter, for example in 020 we
	// don't need the leading 0.  Where it
	// does matter we have "pos -= 1;"
	std::streampos
		pos;
	if (ch == '0')
	{
		// No "pos -= 1;" here as we don't
		// need to bother including leading 0's
		// May be octal, hex or decimal
		ch = Read();
		if ((ch | 0x20) == 'x')
		{
			// Hex
			ch = Read();
			if (!IsHex(ch))
			{
				// Must have at least one number after the 0x
				// TODO: Warning
				return Create("0", TokenType::TT_NUMBER);
			}
			while (ch == '0')
			{
				ch = Read();
			}
			if (!IsHex(ch))
			{
				m_sCur->unget();
				return Create("0", TokenType::TT_NUMBER);
			}
			pos = m_sCur->tellg();
			pos -= 1;
			// Exclude the "0x"
			GetHexLen(ch);
			return DoHex(pos);
		}
		else
		{
			// Skip leading zeroes
			while (ch == '0')
			{
				ch = Read();
			}
			// Get the new start point
			pos = m_sCur->tellg();
			pos -= 1;
			if (IsOct(ch))
			{
				// MAY be octal
				if (GetOctLen(ch))
				{
					// Definatey octal
					// TODO: Deprecation warning
					return DoOct(pos);
				}
				// Not octal
			}
			else if (IsDec(ch))
			{
				// TODO: Warning
				// Leading zero on decimal number
				// Definately decimal
				GetDecLen(ch, false);
			}
			else if (ch == '.')
			{
				// false despite having a '.'
				// Let the function handle it
				GetDecLen('.', false);
			}
			else if ((ch | 0x20) == 'e')
			{
				// 0e1 makes no sense regardless of the
				// number after the e
				// Call this to skip all additional numbers
				GetDecLen('e', true);
				// TODO: Warning
				return Create("0", TokenType::TT_NUMBER);
			}
			else if (IsSym(ch)) // includes 'x' not 'e'
			{
				// Invalid numeric constant
				// TODO: Warning
				m_sCur->unget();
				return Create("0", TokenType::TT_NUMBER);
			}
			else
			{
				// Zero
				m_sCur->unget();
				return Create("0", TokenType::TT_NUMBER);
			}
		}
	}
	else if (ch == '.')
	{
		// Has to be decimal or an operator
		ch = Read();
		if (IsDec(ch))
		{
			// Include the decimal point
			pos = m_sCur->tellg();
			pos -= 2;
			// Decimal number starting
			// with a decimal point
			GetDecLen(ch, true);
		}
		else
		{
			// Dot operator
			m_sCur->unget();
			return DoOperator('.');
		}
	}
	else
	{
		// Include the first number
		pos = m_sCur->tellg();
		pos -= 1;
		// Number (it's filtered in GetNext)
		GetDecLen(ch, false);
	}
	return DoDec(pos);
}

Token &
	TokenFactory::
	DoDec(const std::streampos start)
{
	m_sCur->clear();
	std::streampos
		len = m_sCur->tellg();
	len -= start;
	char *
		c = (char *)alloca((size_t)len + 1);
	if (c)
	{
		m_sCur->seekg(start);
		m_sCur->read(c, len);
		c[len] = '\0';
		if (m_sCur->bad())
		{
			Message::Send(Message::INPUT_STREAM_ERROR);
		}
		else
		{
			return Create(c, TokenType::TT_NUMBER);
		}
	}
	else
	{
		// TODO: Error
	}
	return Create("0", TokenType::TT_NUMBER);
}

Token &
	TokenFactory::
	DoHex(const std::streampos start)
{
	m_sCur->clear();
	// Generate the number in decimal
	std::streampos
		len = m_sCur->tellg();
	// Get the hex string length
	len -= start;
	// Allocate approximately enough memory
	// for the decimal equivalent (over
	// allocates), plus NULL.
	char *
		c = (char *)alloca((size_t)len * 2 + 1);
	if (c)
	{
		// Blank the string
		memset(c, '\0', (size_t)len * 2 + 1);
		// Go to the start of the important parts
		// of the hex number (i.e. after "0x")
		m_sCur->seekg(start);
		int
			sp = 0,
			ap,
			carry;
		// Read in the hex string and convert
		// it to a string representation of a
		// decimal number inline.
		while (len)
		{
			unsigned char
				ch = Read();
			len -= 1;
			// Multiply by 16
			ap = ++sp;
			// Determine the next character to add
			if ((ch - '0') < 10)
			{
				carry = ch - '0';
			}
			else
			{
				carry = (ch | 0x20) - ('a' - 10);
			}
			// Magic happens here, the code below
			// will loop through the existing
			// number (0 to start with), multiply
			// it by 16 and add the new number.
			// The new number is propogated through
			// the sum in combination with the
			// carry from the multiplication, this
			// is to reduce the amount of code
			// required
			while (ap)
			{
				carry += c[ap - 1] * 16;
				c[ap] = carry % 10;
				carry /= 10;
				--ap;
			}
			// This is always the most significant
			// position, however it may sometimes be 0
			c[0] = carry;
			// Large carry - occurs around 0xFFFF
			while (carry >= 10)
			{
				// Correct the first value
				// Only do this if we actually
				// need to, not every time as
				// mods are slow and the check
				// must be done every time anyway
				c[0] %= 10;
				carry /= 10;
				// Need to grow the number - it's
				// got too large and the carry
				// wants to overflow
				// Shift the number
				ap = ++sp;
				while (ap)
				{
					c[ap] = c[ap - 1];
					--ap;
				}
				// Add the new bit of carry to
				// the start
				c[0] = carry;
			}
		}
		// Convert the numbers to characters
		while (sp >= 0)
		{
			c[sp] += '0';
			--sp;
		}
		// Drop any leading zeroes
		if (c[0] == '0')
		{
			return Create(c + 1, TokenType::TT_NUMBER);
		}
		else
		{
			return Create(c, TokenType::TT_NUMBER);
		}
	}
	else
	{
		// TODO: Error
		return Create("0", TokenType::TT_NUMBER);
	}
}

Token &
	TokenFactory::
	DoOct(const std::streampos start)
{
	m_sCur->clear();
	std::streampos
		len = m_sCur->tellg();
	len -= start;
	// Allocate (more than) enough space
	char *
		c = (char *)alloca((size_t)len + 2);
	if (c)
	{
		memset(c, '\0', (size_t)len + 2);
		m_sCur->seekg(start);
		int
			sp = 0,
			ap,
			carry;
		while (len)
		{
			len -= 1;
			ap = ++sp;
			carry = Read() - '0';
			while (ap)
			{
				carry += c[ap - 1] * 8;
				c[ap] = carry % 10;
				carry /= 10;
				--ap;
			}
			// c[0] is always 0
			// Not ideal but simple
		}
		// Convert the numbers to characters
		while (sp)
		{
			c[sp] += '0';
			--sp;
		}
		// Drop any leading zeroes
		// (c[0] is ALWAYS 0 for octal)
		if (c[1] == '0')
		{
			return Create(c + 2, TokenType::TT_NUMBER);
		}
		else
		{
			return Create(c + 1, TokenType::TT_NUMBER);
		}
	}
	else
	{
		// TODO: Error
		return Create("0", TokenType::TT_NUMBER);
	}
}

void
	TokenFactory::
	GetHexLen(unsigned char ch)
{
	while (IsHex(ch))
	{
		ch = Read();
	}
	if (IsSym(ch))
	{
		// Invalid numeric constant
		// TODO: Warning
	}
	else if (ch == '.')
	{
		// Decimal hex
		// TODO: Warning
	}
	m_sCur->unget();
}

bool
	TokenFactory::
	GetOctLen(unsigned char ch)
{
	while (IsOct(ch))
	{
		ch = Read();
	}
	if (IsDec(ch) || ch == '.' || (ch | 0x20) == 'e')
	{
		// Started out octal,
		// Then changed
		// TODO: Warning
		GetDecLen(ch, false);
		// Not octal (i.e. decimal)
		return false;
	}
	else if (IsSym(ch))
	{
		// Invalid numeric constant
		// TODO: Warning
	}
	// Put the character back
	m_sCur->unget();
	// Valid octal number
	return true;
}

void
	TokenFactory::
	GetDecLen(unsigned char ch, bool frac)
{
	// Decimal numbers can include fractions
	// and exponents, which we also need to
	// track
	bool
		exp = false;
	for ( ; ; )
	{
		if (ch == '.')
		{
			if (exp)
			{
				// Can't have decimal exponents
				// TODO: Warning
				return;
			}
			else if (frac)
			{
				// Can't have a dp twice
				// TODO: Warning
				return;
			}
			else
			{
				// OK, we're in the fraction
				frac = true;
			}
		}
		else if ((ch | 0x20) == 'e')
		{
			if (exp)
			{
				// Already in the exponent
				// TODO: Warning
				return;
			}
			else
			{
				exp = true;
			}
		}
		else if (!IsDec(ch))
		{
			if (IsSym(ch))
			{
				// Invalid numeric constant
				// TODO: Warning
			}
			m_sCur->unget();
			// End of the number
			return;
		}
		ch = Read();
	}
}
