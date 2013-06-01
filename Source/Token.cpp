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
//  The Original Code is the yavascript development system - Token.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Token.h"

#include "Tokens/TLiteral.h"

#include "Message.h"

#include <string>
#include <iostream>

#include "StringCast.h"

#include "Compiler.h"

Token
	Token::m_sNone(TokenType::TT__NONE);

Symbols &
	Token::m_sSymbols = Compiler::Get().GetSymbols();

// cons
	Token::
	Token(const TokenType::E_TYPE type) :
		m_type(type),
		m_lbp(0),
		m_parent(NULL),
		m_last(NULL),
		m_next(NULL),
		m_child(NULL),
		m_dispose(false),
		m_iChildren(0),
		m_label(NULL)
{
}

// cons
	Token::
	Token(const TokenType::E_TYPE type, int lbp) :
		m_type(type),
		m_lbp(lbp),
		m_parent(NULL),
		m_last(NULL),
		m_next(NULL),
		m_child(NULL),
		m_dispose(false),
		m_iChildren(0),
		m_label(NULL)
{
}

// dest
	Token::
	~Token()
{
	// Remove from parent
	if (m_parent)
	{
		m_parent->Remove(*this);
	}
	// Delete all node children
	Token *
		c = m_child;
	while (c)
	{
		Token *
			n = c->m_next;
		delete c;
		c = n;
	}
}

Token &
	Token::
	LED(SyntaxHandler & sh, Token & left)
{
	Message::Send(Message::EXPECTED_OPERATOR, SC::R(*this));
	Dispose();
	return left;
}

Token &
	Token::
	NUD(SyntaxHandler & sh)
{
	Message::Send(Message::EXPECTED_IDENTIFIER, SC::R(*this));
	return *this;
}

Token &
	Token::
	STD(SyntaxHandler & sh)
{
	return *this;
}

Token &
	Token::
	Remove(Token & item)
{
	if (item.m_parent != this)
	{
		// Can't remove a child that
		// isn't really a child
		return *this;
	}
	// It is a child of this one
	if (m_child == &item)
	{
		// First child
		m_child = item.m_next;
		if (m_child)
		{
			m_child->m_last = item.m_last;
		}
	}
	else
	{
		item.m_last->m_next = item.m_next;
		if (item.m_next)
		{
			item.m_next->m_last = item.m_last;
		}
		else
		{
			m_child->m_last = item.m_last;
		}
	}
	item.m_parent = NULL;
	item.m_last = NULL;
	item.m_next = NULL;
	// Decrement the number of children
	--m_iChildren;
	return *this;
}

Token &
	Token::
	Pop()
{
	if (m_child)
	{
		Token *
			ret = m_child;
		m_child = ret->m_next;
		if (m_child)
		{
			m_child->m_last = ret->m_last;
		}
		ret->m_parent = NULL;
		ret->m_last = NULL;
		ret->m_next = NULL;
		// Decrement the number of children
		--m_iChildren;
		return *ret;
	}
	return m_sNone;
}

Token &
	Token::
	Add(Token & item)
{
	// The forwards list stops at the end
	// The backwards list loops
	// This is so forward itteration is easy
	// but all nodes are accessible from anywhere
	if (item.m_parent)
	{
		item.m_parent->Remove(item);
	}
	if (m_child)
	{
		// Children exist already
		// Add it to the end
		item.m_last = m_child->m_last;
		item.m_last->m_next = &item;
		m_child->m_last = &item;
	}
	else
	{
		item.m_last = &item;
		m_child = &item;
	}
	item.m_parent = this;
	item.m_next = NULL;
	// Increment the number of children
	++m_iChildren;
	return *this;
}

Token &
	Token::
	AddHead(Token & item)
{
	if (item.m_parent)
	{
		item.m_parent->Remove(item);
	}
	// Add it to the START
	item.m_next = m_child;
	if (m_child)
	{
		// Children exist already
		item.m_last = m_child->m_last;
		m_child->m_last = &item;
	}
	else
	{
		item.m_last = &item;
	}
	m_child = &item;
	item.m_parent = this;
	// Increment the number of children
	++m_iChildren;
	return *this;
}

void
	Token::
	AddSymbols(SyntaxHandler & sh, Token & token)
{
	if (token.GetType() == TokenType::TO_BRACKET_O)
	{
		// Remove brackets
		Token &
			add = token.Pop();
		if (add.IsSymbol() || add.IsReserved())
		{
			m_sSymbols.AddSymbol(TL::G(add).GetString());
		}
		Add(add);
		delete &token;
	}
	else
	{
		if (token.IsSymbol() || token.IsReserved())
		{
			m_sSymbols.AddSymbol(TL::G(token).GetString());
		}
		Add(token);
	}
}

// Do we need brackets around
// the given token to preserve
// operator and execution
// precedence?
bool
	Token::
	RequireBrackets(Token & child, const bool right) const
{
	// a + (b - c)
	// Should become:
	// a+(b-c)
	// (a + b) - c
	// Should become:
	// a+b-c
	// However:
	// ~~a
	// Should not become:
	// ~(~a)
	//if (child.m_lbp == 170) std::cout << "this: " << m_lbp << ", that: " << child.m_lbp << ", " << (((child.m_lbp < m_lbp) || (right && (child.m_lbp < m_lbp))) && child.m_child) << std::endl;
	return (((child.m_lbp < m_lbp) || (right && (child.m_lbp < m_lbp))) && child.m_child);
}

void
	Token::
	SetLabel(const char * const l)
{
	delete [] m_label;
	m_label = NULL;
	if (l)
	{
		try
		{
			// Save a COPY of the string
			char *
				s = new char [strlen(l) + 1];
			strcpy(s, l);
			m_label = s;
		}
		catch (std::exception e)
		{
			Message::Send(Message::OUT_OF_MEMORY);
			m_label = NULL;
		}
	}
}
