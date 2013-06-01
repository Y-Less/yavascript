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
//  The Original Code is the yavascript development system - Parser.cpp.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Parser.h"

#include "Message.h"
#include "Generator.h"
#include "Compiler.h"

#include "StringCast.h"

#include "Tokens/TLiteral.h"

#include <iostream>

// cons
	Parser::
	Parser(TokenStream & ts) :
		m_tokens(ts),
		//m_tList(TokenType::TT__NONE),
		m_cur(NULL),
		m_bNL(false)
{
}

// cons
	Parser::
	Parser(const Parser & c) :
		m_tokens(c.m_tokens),
		//m_tList(TokenType::TT__NONE),
		m_cur(c.m_cur),
		m_bNL(c.m_bNL)
{
}

// dest
	Parser::
	~Parser()
{
}

Token &
	Parser::
	ExpressionLabel(const int rbp, Token * t)
{
	Token *
		left;
	// DON'T move on here
	// It's already been moved on for th
	// label lookahead.
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
		if (!SkippedLine())
		{
			// Got a new token on the same line
			Message::Send(Message::EXPECTED_OPERATOR, SC::R(*t));
		}
	}
	return *left;
}

Token &
	Parser::
	Expression(const int rbp)
{
	Token
		*t,
		*left;
	t = &GetCurrent();
	if (!t->IsOperator())
	{
		// Can't have regex directly after
		// another symbol/literal - it
		// may come after a keyword, but
		// those aren't handled here.
		SetRegex(false);
	}
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
		if (!SkippedLine())
		{
			// Got a new token on the same line
			Message::Send(Message::EXPECTED_OPERATOR, SC::R(*t));
		}
	}
	return *left;
}

void
	Parser::
	SetRegex(const bool set)
{
	m_tokens.SetRegex(set);
}

Token &
	Parser::
	Statement(const bool group, const char * const label)
{
	// Get the next token
	Token &
		stmt = GetCurrent();
	// Is this the start of a statement?
	if (stmt.IsStatement())
	{
		bool
			brace = (stmt.GetType() == TokenType::TO_BRACE_O);
		if (group)
		{
			// Expect a group of statements
			if (!brace)
			{
				// Warn for things like:
				// 
				// if (expr) alert('true');
				// 
				// If we get here that's the case
				// TODO: warning
			}
		}
		else
		{
			// Don't expect a group of statements
			if (brace)
			{
				// No block scoping in javascript
				// Following code has no extra
				// effects, even the 'var's.
				// 
				// alert('hi')
				// {
				//     var
				//         iNotBlockScoped = 5;
				//     alert('woo');
				// }
				// alert('three');
				// 
				// TODO: Warning
			}
		}
		Advance();
		// Yes - do the statement
		if (label)
		{
			if (stmt.Labelable())
			{
				// Add the label to the table
				Compiler::Get().GetSymbols().AddSymbol(label, true, false, true);
			}
			else
			{
				Message::Send(Message::NOT_LABELABLE);
			}
		}
		Token &
			ret = stmt.STD(*this);
		if (brace)
		{
			Advance(TokenType::TO_BRACE_C);
		}
		// Don't need that exact token
		if (stmt.Disposable())
		{
			delete &stmt;
		}
		ret.SetLabel(label);
		return ret;
	}
	if (stmt.GetType() == TokenType::TT__EOF || stmt.GetType() == TokenType::TT__END)
	{
		Advance();
		return stmt;
	}
	// Could be a label
	Token *
		expr;
	if (stmt.IsSymbol())
	{
		// Don't allow reserved words as labels
		// In case it's not a label
		// (see Expression())
		SetRegex(false);
		if (Advance().GetType() == TokenType::TO_COLON)
		{
			// Labeled statement
			// Discard the colon
			Advance(TokenType::TO_COLON);
			if (label)
			{
				// Labelled label
				Message::Send(Message::MULTIPLE_LABELS);
			}
			expr = &Statement(group, TL::G(stmt).GetString());
			delete &stmt;
			return *expr;
		}
		else
		{
			// Parse the expression,
			// passing the extra token
			if (label)
			{
				Message::Send(Message::NOT_LABELABLE);
			}
			expr = &ExpressionLabel(0, &stmt);
		}
	}
	else
	{
		// No - do the expression
		if (label)
		{
			Message::Send(Message::NOT_LABELABLE);
		}
		expr = &Expression();
	}
	if (!expr->HasEffect())
	{
		// Expression has no effect
		Message::Send(Message::NO_EFFECT);
	}
	if (m_cur->GetType() == TokenType::TO_COMMA)
	{
		Token &
			ret = Generator::Group();
		ret.Add(*expr);
		do
		{
			Advance(TokenType::TO_COMMA);
			expr = &Expression();
			if (!expr->HasEffect())
			{
				// Expression has no effect
				Message::Send(Message::NO_EFFECT);
			}
			ret.Add(*expr);
		}
		while (m_cur->GetType() == TokenType::TO_COMMA);
		EoS();
		return ret;
	}
	EoS();
	return *expr;
}

Token &
	Parser::
	GetNextReal(bool & skipNL)
{
	skipNL = false;
	// No matching tokens buffered
	// Get and save the next one
	Token *
		ret = &m_tokens.GetNext();
	while (ret->GetType() == TokenType::TT_EOL)
	{
		skipNL = true;
		ret = &m_tokens.GetNext();
	}
	return Update(*ret);
}

Token &
	Parser::
	GetCurrent()
{
	// Have a current token
	if (m_cur)
	{
		return *m_cur;
	}
	// First time (hopefully)
	bool
		b;
	SetRegex(true);
	return GetNextReal(b);
}

// This function moves on to the next token
// If a type is passed it checks that the
// current token is of that type and gives
// an error if it's not.
Token &
	Parser::
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
			// Re-return the same token
			// May need it next, e.g.:
			// 
			// if a > 10)
			// 
			// [sic]
			// 
			// will still be parsed correctly
			// if we return the token that
			// should have been the '('
			return *m_cur;
		}
		// Check call, don't actually need
		// the token
		m_cur->Dispose();
	}
	Token &
		ret = GetNextReal(m_bNL);
	SetRegex(true);
	return ret;
}

// This function is the same as Advance, but
// with an implicit TokenType::TT_EOS passed
// and giving a warning not an error as ';'s
// can be legally missed off lines.
Token &
	Parser::
	EoS()
{
	if (m_cur->GetType() != TokenType::TT_EOS)
	{
		Message::Send(Message::IMPLICIT_EOS);
		return *m_cur;
	}
	// Check call, don't actually need
	// the semicolon token.
	m_cur->Dispose();
	Token &
		ret = GetNextReal(m_bNL);
	SetRegex(true);
	return ret;
}

// This function deletes the current token
// if required (i.e. if it's been marked
// for destruction) (this keeps most of the
// destruction code in one place and
// ensures there should never be hanging
// pointers).  It also updates the current
// pointer to the newly given one and
// returns the new current (for convenience).
Token &
	Parser::
	Update(Token & nu)
{
	// Have an old token?
	if (m_cur)
	{
		// Yes. Get rid of it?
		if (m_cur->Disposable())
		{
			// Yes.
			delete m_cur;
		}
		// Unhang pointer
		m_cur = NULL;
	}
	// Set new pointer
	m_cur = &nu;
	return nu;
}

bool
	Parser::
	SkippedLine()
{
	return m_bNL;
}
