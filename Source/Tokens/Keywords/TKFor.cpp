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
//  The Original Code is the yavascript development system - TKFor.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKFor.h"

#include "../../Message.h"
#include "../../Generator.h"

#include "../TLiteral.h"

#include "TKVar.h"

#include <iostream>
#include <sstream>

Token &
	TKFor::
	STD(SyntaxHandler & sh)
{
	// 
	// The resulting tree is either:
	// 
	//      --------for/in--------
	//      |         |          |
	// identifier expression statement
	// 
	// Or:
	// 
	//  -------------for-----------
	//  |      |        |         |
	// var condition modifier statement
	// 
	// Or:
	// 
	//  -------------for------------
	//  |      |        |          |
	// item condition modifier statement
	// 
	// Three children mean for/in.
	// Four children mean for.
	// Anything else is wrong.
	// 
	// var, item, condition and modifier may
	// all be null if required:
	// 
	// for (a in b) {}
	// for (var a in b) {}
	// for (a; b; c) {}
	// for ( ; a; b) {}
	// for (a; ; b) {}
	// for (a; b; ) {}
	// for (a; ; ) {}
	// for ( ; a; ) {}
	// for ( ; ; a) {}
	// for (var a; b; c) {}
	// for (var a; ; b) {}
	// for (var a; b; ) {}
	// for (var a; ; ) {}
	// 
	// Note that the only statements
	// which affect the scope chain
	// are function, with and catch.
	// Variables declared using var in
	// a for statement, while syntactically
	// correct, are NOT restricted to
	// the scope of the for loop:
	// 
	// for (var i = 0; i != 10; ++i) {}
	// alert(i);
	// 
	// The above will display 10,
	// despite the non-intuative
	// nature of this code from the
	// point of view of other
	// languages.  This is however
	// good for space optimisation.
	// 
	// Just to confuse things, this
	// is valid:
	// 
	// for (var i = j in k; i; --i);
	// 
	sh.Advance(TokenType::TO_BRACKET_O);
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	if (type == TokenType::TT_EOS)
	{
		// Skip initialisation
		// Definately:
		// for ( ; ; )
		// Can't give a warning
		// but safely dispose of it
		sh.EoS();
		// Add blank initialisation
		Add(Generator::Null());
		// Add conditionals
		Conditional(sh);
		// Add modifiers
		Modifiers(sh);
	}
	else if (type == TokenType::TO_BRACKET_C)
	{
		// Invalid for
		Message::Send(Message::INVALID_FOR);
	}
	else if (type == TokenType::TK_var)
	{
		// Need to figure out what sort it is
		Token &
			var = sh.GetCurrent();
		Token &
			sym = sh.Advance();
		if (!sym.IsSymbol() && !sym.IsReserved())
		{
			Message::Send(Message::EXPECTED_IDENTIFIER);
		}
		if (sh.Advance().GetType() == TokenType::TK_in)
		{
			// for (var x in y) {}
			sh.Advance(TokenType::TK_in);
			// Add the var
			m_sSymbols.AddSymbol(TL::G(sym).GetString(), true);
			var.Add(sym);
			Add(var);
			// Add the expression
			Add(sh.Expression());
		}
		else
		{
			// for (var x; y; z) {}
			if (!dynamic_cast<TKVar *>(&var)->DoVar(sh, &sym))
			{
				// Didn't end in a semi-colon
				// TODO: Error
				Message::Send(Message::EXPECTED_TOKEN, ";");
			}
			Add(var);
			Conditional(sh);
			Modifiers(sh);
		}
	}
	else
	{
		// Not determined wether this is:
		// for (x in y)
		// or:
		// for (x; y; z)
		Token &
			first = sh.Expression();
		if (first.GetType() == TokenType::TK_in)
		{
			// for (x in y)
			Token &
				ident = first.Pop();
			if (!ident.IsSymbol() && !ident.IsReserved())
			{
				// Bad
				Message::Send(Message::EXPECTED_IDENTIFIER);
			}
			// Add the 'in' children to us
			// And remove from their current parent
			Add(ident);
			Add(first.Pop());
			// Don't need the 'in' token
			delete &first;
		}
		else
		{
			// for (x; y; z)
			Initialisation(sh, first);
			sh.EoS();
			Conditional(sh);
			Modifiers(sh);
		}
	}
	sh.Advance(TokenType::TO_BRACKET_C);
	// Add the code to be looped
	// Preferably enclosed in braces
	Statement(sh);
	return *this;
}

bool
	TKFor::
	Conditional(SyntaxHandler & sh)
{
	// Custom implementation
	// There are no brackets here
	// Can do expression optimisation here
	if (sh.GetCurrent().GetType() == TokenType::TT_EOS)
	{
		// No conditional
		Add(Generator::Null());
	}
	else
	{
		// Add the conditional
		Token &
			expr = sh.Expression();
		if (expr.IsAssignment())
		{
			// if (a = b)
			// Warn of possibly unintended assignment
			// This currently also does: if (a += b)
			// I've not decided if this is a bug or feature
			Message::Send(Message::UNINTENDED_ASSIGNMENT);
			Add(expr);
		}
		else if (expr.GetType() == TokenType::TO_BRACKET_O)
		{
			// if ((x))
			// Useful for intended assignments
			// if ((a = b))
			// Don't include the extrs brackets.
			// Pop gets the contents and
			// removes them from the brackets
			Add(expr.Pop());
			// Delete the brackets but not
			// the old contents (popped).
			delete &expr;
		}
		else
		{
			Add(expr);
		}
	}
	// Check for a close bracket
	sh.EoS();
	return true;
}

bool
	TKFor::
	Initialisation(SyntaxHandler & sh, Token & first)
{
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	Token &
		p = Generator::Null();
	Add(p);
	// Add the expression we already
	// read from determining if type
	p.Add(first);
	if (type == TokenType::TT_EOS)
	{
		return true;
	}
	// Skip the comma
	type = sh.Advance(TokenType::TO_COMMA).GetType();
	for ( ; ; )
	{
		if (type == TokenType::TO_COMMA)
		{
			// Missing statement
			// for (x; y; , z) {}
			Message::Send(Message::INVALID_EXPRESSION);
		}
		else if (type == TokenType::TT__END || type == TokenType::TT__EOF)
		{
			return false;
		}
		else
		{
			// Get an expression from the list
			Token &
				expr = sh.Expression(0);
			// Add it to the tree
			// TODO: Check it's a valid expresion
			p.Add(expr);
			type = sh.GetCurrent().GetType();
			if (type == TokenType::TT__END || type == TokenType::TT__EOF)
			{
				return false;
			}
			else if (type == TokenType::TT_EOS)
			{
				return true;
			}
		}
		// Skip the comma
		sh.Advance(TokenType::TO_COMMA);
		type = sh.GetCurrent().GetType();
		if (type == TokenType::TT_EOS)
		{
			Message::Send(Message::EXPECTED_EXPRESSION);
			return true;
		}
	}
}

bool
	TKFor::
	Modifiers(SyntaxHandler & sh)
{
	TokenType::E_TYPE
		type = sh.GetCurrent().GetType();
	// Parent for the modifiers
	Token &
		p = Generator::Null();
	Add(p);
	if (type == TokenType::TO_BRACKET_C)
	{
		return true;
	}
	for ( ; ; )
	{
		if (type == TokenType::TO_COMMA)
		{
			// Missing statement
			// for (x; y; , z) {}
			Message::Send(Message::INVALID_EXPRESSION);
		}
		else if (type == TokenType::TT__END || type == TokenType::TT__EOF)
		{
			return false;
		}
		else
		{
			// Get an expression from the list
			Token &
				expr = sh.Expression(0);
			// Add it to the tree
			// TODO: Check it's a valid expresion
			p.Add(expr);
			type = sh.GetCurrent().GetType();
			if (type == TokenType::TT__END || type == TokenType::TT__EOF)
			{
				return false;
			}
			else if (type == TokenType::TO_BRACKET_C)
			{
				return true;
			}
		}
		// Skip the comma
		sh.Advance(TokenType::TO_COMMA);
		type = sh.GetCurrent().GetType();
		if (type == TokenType::TO_BRACKET_C)
		{
			Message::Send(Message::EXPECTED_EXPRESSION);
			return true;
		}
	}
}

std::ostream &
	TKFor::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKFor::
	Release(std::ostream & s) const
{
	DoLabel(s);
	// Three children mean for/in.
	// Four children mean for.
	// Anything else is wrong.
	s << "for(";
	switch (GetChildCount())
	{
		case 3:
		{
			// May or may not need a
			// space before the "in"
			std::ostringstream
				sb;
			Token &
				left = GetFirstChild();
			left.Release(sb);
			std::string
				str = sb.str();
			// Output the thing
			s << str;
			const char
				ch = str[str.length() - 1];
			if ((const unsigned char)((ch | 0x20) - 'a') < 26 || (const unsigned char)(ch - '0') < 10 || ch == '_' || ch == '$')
			{
				// Output the space
				s << ' ';
			}
			s << "in";
			// 120 = "in" lbp
			Token &
				right = GetChild(1);
			if (right.GetLBP() <= 120 && right.HasChildren())
			{
				s << '(';
				right.Release(s);
				s << ')';
			}
			else
			{
				DoSpacePar(right, s);
			}
			s << ')';
			GetChild(2).Release(s);
			break;
		}
		case 4:
		{
			Token &
				init = GetFirstChild();
			if (init.GetType() == TokenType::TK_var)
			{
				init.Release(s);
			}
			else
			{
				Token::Itter
					inits = init;
				bool
					ic = false;
				while (inits.HasNext())
				{
					if (ic)
					{
						s << ',';
					}
					else
					{
						ic = true;
					}
					inits.Next().Release(s);
				}
			}
			s << ';';
			// The easy one - conditional
			// expressions sort themselves
			// out with logic operators.
			GetChild(1).Release(s);
			s << ';';
			// Output all the modifiers
			// These are children of
			// a null node to maintain
			// constant children counts
			Token::Itter
				modifiers = GetChild(2);
			bool
				comma = false;
			while (modifiers.HasNext())
			{
				if (comma)
				{
					s << ',';
				}
				else
				{
					comma = true;
				}
				modifiers.Next().Release(s);
			}
			s << ')';
			GetChild(3).Release(s);
			break;
		}
	}
	return s;
}

bool
	TKFor::
	RequireSemicolon() const
{
	// An if only requires a semicolon
	// when it ends in an expression.
	// For example:
	// for (;;) alert('hi');
	// requires a semicolon.
	// for (;;) function m() {}
	// doesn't.
	switch (GetChildCount())
	{
		case 3:
		{
			// for ( in ) {}
			Token &
				fb = GetChild(2);
			if (fb.IsStatement())
			{
				// See if the statement
				// child need a semicolon
				return fb.RequireSemicolon();
			}
			else
			{
				// All expressions should
				return true;
			}
		}
		case 4:
		{
			// for ( ; ; ) {}
			Token &
				fb = GetChild(3);
			if (fb.IsStatement())
			{
				return fb.RequireSemicolon();
			}
			else
			{
				// All expressions should
				return true;
			}
		}
	}
	// Not really needed as
	// this should never be
	// needed before the
	// children are defined.
	// But it's needed by
	// the compiler.
	return false;
}
