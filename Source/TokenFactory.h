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
//  The Original Code is the yavascript development system - TokenFactory.h. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <istream>
#include <stack>

#include "TokenType.h"

#include "Token.h"

class Preprocessor;

class TokenFactory
{
public:
	// ================
	//  Public methods
	// ================
	
	Token &
		GetNext();
	
	// =======================
	//  Public initialisation
	// =======================
	
	// No default constructor
	
	// Constructor
	// cons
		TokenFactory(std::istream &i, char * const szName);
	
	// Destructor
	// dest
		~TokenFactory()
	{
	};
	
	void
		SetRegex(const bool set)
	{
		m_regex = set;
	};
	
	char * const
		GetStreamName() const
	{
		return m_szStreamName;
	};
	
	int
		GetLine() const
	{
		return m_line;
	};
	
	void
		IncLine();
	
private:
	// =================
	//  Private members
	// =================
	
	// Stream from which to read data
	std::istream &
		m_isInput;
	
	std::istream *
		m_sCur;
	
	// Alternate input streams
	// Supercede the main stream
	std::stack<std::istream *>
		m_altIn;
	
	// Type of last token returned
	TokenType::E_TYPE
		m_ttLast;
	
	// Name of the file (stream)
	char * const
		m_szStreamName;
	
	// Current line
	int
		m_line;
	
	bool
		m_regex,
		m_newLine;
	
	// =================
	//  Private methods
	// =================
	
	Token &
		DoGetNext();
	
	virtual void
		Unget()
	{
		m_sCur->unget();
	};
	
	// Read a single character from the input stream
	virtual unsigned char
		Read();
	
	// Create a single token of a string
	Token &
		Create(const char * const str, const TokenType::E_TYPE type);
	
	// Create a single token of the given type
	Token &
		Create(const TokenType::E_TYPE type);
	
	bool
		CheckLetters(const char * str);
	
	static Token *
		CreateOperator(const TokenType::E_TYPE type);
	
	static Token *
		CreateKeyword(const TokenType::E_TYPE type);
	
	static Token *
		CreateReserve(const TokenType::E_TYPE type);
	
	static Token *
		CreateGlobal(const TokenType::E_TYPE type);
	
	// =====================
	//  Basic common checks
	// =====================
	
	static inline bool
		IsHex(const unsigned char ch)
	{
		// Equivalent to:
		// return ((ch >= '0') && ch <= '9') || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'));
		// But obviously shorter and, more importantly,
		// with less comparisons, thus less jumps.
		// The unsignedness of the char is important.
		return (unsigned char)(ch - '0') < 10 || (unsigned char)((ch | 0x20) - 'a') < 6;
	};
	
	static inline bool
		IsOct(const unsigned char ch)
	{
		return (unsigned char)(ch - '0') < 8;
	};
	
	static inline bool
		IsDec(const unsigned char ch)
	{
		return (unsigned char)(ch - '0') < 10;
	};
	
	static inline bool
		IsSym(const unsigned char ch)
	{
		// Valid symbol START characters
		// Numbers are only valid in symbols AFTER the first character
		// Otherwise it would be VERY hard to tell them from numbers
		// If not impossible in some cases, and that's BAAD!
		return (unsigned char)((ch | 0x20) - 'a') < 26 || ch == '_' || ch == '$';
	};
	
	// ==================
	//  Number functions
	// ==================
	
	Token &
		DoNumber(unsigned char ch);
	
	void
		GetHexLen(unsigned char ch);
	
	void
		GetDecLen(unsigned char ch, bool frac);
	
	bool
		GetOctLen(unsigned char ch);
	
	// Generate a decimal string from an octal input
	Token &
		DoOct(const std::streampos start);
	
	// Generate a decimal string from a hex input
	Token &
		DoHex(const std::streampos start);
	
	// Generate a decimal string from a decimal input
	Token &
		DoDec(const std::streampos start);
	
	// ==================
	//  Symbol functions
	// ==================
	
	Token &
		DoSymbol(unsigned char ch);
	
	// =================
	//  RegEx functions
	// =================
	
	Token &
		DoRegex();
	
	// ====================
	//  Operator functions
	// ====================
	
	Token &
		DoOperator(unsigned char ch);
	
	// ==================
	//  String functions
	// ==================
	
	// Does the actual parsing of a string token
	Token &
		DoString(const unsigned char end);
	
	// Interprets an octal escape sequence
	unsigned short
		GetOctEscape(unsigned char & ch);
	
	// Interprets a hex escape sequence
	unsigned short
		GetHexEscape(unsigned char & ch);
	
	// Interprets a unicode escape sequence
	unsigned short
		GetUnicodeEscape(unsigned char & ch);
	
	// Writes a unicode sequence to a string
	std::streampos
		OutputUnicode(char * const c, std::streampos pos, unsigned short val) const;
	
	// ========================
	//  Private initialisation
	// ========================
	
	// Copy constructor
	// cons
		TokenFactory(const TokenFactory &t) :
			m_isInput(t.m_isInput),
			m_ttLast(TokenType::TT__NONE),
			m_szStreamName(""),
			m_line(1),
			m_regex(true),
			m_sCur(NULL),
			m_newLine(true)
	{
	};
	
	// Assignment operator
	TokenFactory
		&operator=(const TokenFactory &t)
	{
		return *this;
	};
	
	// States for various machines
	enum E_STATE
	{
		// Initial state
		ES__NONE = 0,
		// Misc states
		ES__DONE,
		ES__UNKNOWN,
		// Symbol states
		ES_24,
		ES_24define,
		ES_24undef,
		ES_E,
		ES_R,
		ES_Re,
		ES_S,
		ES_5F5F,
		ES_b,
		ES_c,
		ES_ca,
		ES_con,
		ES_d,
		ES_de,
		ES_do,
		ES_e,
		ES_ex,
		ES_f,
		ES_final,
		ES_i,
		ES_imp,
		ES_in,
		ES_int,
		ES_n,
		ES_p,
		ES_pr,
		ES_s,
		ES_t,
		ES_th,
		ES_throw,
		ES_tr,
		ES_v,
		ES_vo,
		ES_w,
		// Operator states
		ES_21,
		ES_213D,
		ES_25,
		ES_26,
		ES_2A,
		ES_2B,
		ES_2D,
		ES_2F,
		ES_3C,
		ES_3C3C,
		ES_3D,
		ES_3D3D,
		ES_3E,
		ES_3E3E,
		ES_3E3E3E,
		ES_5E,
		ES_7C,
		// State count
		ES__MAX,
	};
	
	// Allow the pre-processor to
	// access this stream
	friend class Preprocessor;
};
