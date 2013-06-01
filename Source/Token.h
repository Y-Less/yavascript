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
//  The Original Code is the yavascript development system - Token.h.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "TokenType.h"
#include "SyntaxHandler.h"
#include "Symbols.h"

class Token
{
public:
	// cons
		Token(const TokenType::E_TYPE type);
	
	// cons
		Token(const TokenType::E_TYPE type, const int lbp);
	
	virtual // dest
		~Token();
	
	friend std::ostream &
		operator<<(std::ostream &s, const Token &t)
	{
		return t.Output(s);
	};
	
	virtual std::ostream &
		Debug(std::ostream &s) const
	{
		return s << m_type;
	};
	
	virtual std::ostream &
		Release(std::ostream &s) const
	{
		return s << m_type;
	};
	
	TokenType::E_TYPE
		GetType() const
	{
		return m_type;
	};
	
	int
		GetLBP() const
	{
		return m_lbp;
	};
	
	virtual Token &
		LED(SyntaxHandler & sh, Token & left);
	
	virtual Token &
		NUD(SyntaxHandler & sh);
	
	virtual Token &
		STD(SyntaxHandler & sh);
	
	virtual bool
		IsStatement() const
	{
		return false;
	};
	
	virtual bool
		RequireSemicolon() const
	{
		return false;
	};
	
	virtual bool
		HasEffect() const
	{
		return false;
	};
	
	virtual bool
		Labelable() const
	{
		return false;
	};
	
	// Check if the given token is a global token
	bool
		IsGlobal() const
	{
		return TokenType::IsGlobal(m_type);
	};
	
	// Check if the given token is a keyword token
	bool
		IsKeyword() const
	{
		return TokenType::IsKeyword(m_type);
	};
	
	// Check if the given token is a reserved token
	bool
		IsReserved() const
	{
		return TokenType::IsReserved(m_type);
	};
	
	// Check if the given token is an operator token
	bool
		IsOperator() const
	{
		return TokenType::IsOperator(m_type);
	};
	
	bool
		IsConstant() const
	{
		return TokenType::IsConstant(m_type);
	};
	
	// Check if the given token is a symbol token
	bool
		IsSymbol() const
	{
		return TokenType::IsSymbol(m_type);
	};
	
	bool
		IsString() const
	{
		return TokenType::IsString(m_type);
	};
	
	bool
		IsNumber() const
	{
		return TokenType::IsNumber(m_type);
	};
	
	bool
		IsRegex() const
	{
		return TokenType::IsRegex(m_type);
	};
	
	bool
		IsAssignment() const
	{
		return TokenType::IsAssignment(m_type);
	};
	
	void
		Dispose()
	{
		m_dispose = true;
	};
	
	bool
		Disposable() const
	{
		return m_dispose;
	};
	
	Token &
		Add(Token & item);
	
	Token &
		Remove(Token & item);
	
	// Add a token to the front
	// of the list of children
	Token &
		AddHead(Token & item);
	
	bool
		HasChildren() const
	{
		// If it's NULL then it's false
		return m_child != NULL;
	};
	
	Token &
		GetFirstChild() const
	{
		// Call HasChildren FIRST
		return *m_child;
	};
	
	bool
		RequireBrackets(Token & child, const bool right) const;
	
	Token &
		Pop();
	
	class Itter
	{
	public:
		// cons
			Itter(const Itter & i) :
				m_cur(i.m_cur)
		{
		};
		
		// cons
			Itter(const Token & t) :
				m_cur(t.m_child)
		{
		};
		
		// dest
			~Itter()
		{
		};
		
		Itter &
			operator=(const Itter & i)
		{
			m_cur = i.m_cur;
			return *this;
		};
		
		Token &
			Next()
		{
			if (m_cur)
			{
				Token *
					cur = m_cur;
				m_cur = m_cur->m_next;
				return *cur;
			}
			else
			{
				return m_sNone;
			}
		};
		
		bool
			HasNext() const
		{
			return m_cur != NULL;
		};
		
	private:
		Token *
			m_cur;
	};
	
	class ConstItter
	{
	public:
		// cons
			ConstItter(const ConstItter & i) :
				m_cur(i.m_cur)
		{
		};
		
		// cons
			ConstItter(const Token & t) :
				m_cur(t.m_child)
		{
		};
		
		// dest
			~ConstItter()
		{
		};
		
		ConstItter &
			operator=(const ConstItter & i)
		{
			m_cur = i.m_cur;
			return *this;
		};
		
		const Token &
			Next()
		{
			if (m_cur)
			{
				Token *
					cur = m_cur;
				m_cur = m_cur->m_next;
				return *cur;
			}
			else
			{
				return m_sNone;
			}
		};
		
		bool
			HasNext() const
		{
			return m_cur != NULL;
		};
		
	private:
		Token *
			m_cur;
	};
	
	static Token &
		Null()
	{
		return m_sNone;
	};
	
	int
		GetChildCount() const
	{
		return m_iChildren;
	};
	
	Token &
		GetChild(int index) const
	{
		int
			i = 0;
		Token *
			cur = m_child;
		while (i < index && cur)
		{
			++i;
			cur = cur->m_next;
		}
		return *cur;
	};
	
	void
		AddSymbols(SyntaxHandler & sh, Token & token);
	
	void
		SetLabel(const char * const l);
	
protected:
	// Print information about this token
	virtual std::ostream &
		Output(std::ostream & s) const
	{
		return s << m_type;
	};
	
	// Should be used VERY sparingly!
	void
		SetType(TokenType::E_TYPE type)
	{
		m_type = type;
	};
	
	// Handle to the global
	// symbol table for all
	// tokens to use quickly.
	static Symbols &
		m_sSymbols;
	
	std::ostream &
		DoLabel(std::ostream & s) const
	{
		if (m_label)
		{
			s << m_label << ':';
		}
		return s;
	};
	
private:
	// Blank token to return
	// as NULL
	static Token
		m_sNone;
	
	// The type of the token
	TokenType::E_TYPE
		m_type;
	
	// The binding power of this token
	int
		m_lbp,
		m_iChildren;
	// Number of children this token has
	
	// Auto memory handler
	// When set true it's got rid of
	// at the first possible moment
	bool
		m_dispose;
	
	char *
		m_label;
	
	Token
		* m_parent,
		* m_last,
		* m_next,
		* m_child;
	
	// Keep private
	// Token is an abstract class
	// As such can't be reliably assigned to
	Token &
		operator=(const Token & t)
	{
		m_type = t.m_type;
		return *this;
	};
	
	// cons
		Token(const Token & t)
	{
	};
};
