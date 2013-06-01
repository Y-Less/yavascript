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
//  The Original Code is the yavascript development system - TKNew.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKNew.h"

#include "../TLiteral.h"

#include "../../Message.h"
#include "../../StringCast.h"

Token &
	TKNew::
	NUD(SyntaxHandler & sh)
{
	if (sh.GetCurrent().GetType() == TokenType::TT_EOS)
	{
		Message::Send(Message::EXPECTED_IDENTIFIER);
		sh.EoS();
	}
	// Get the thing we're making
	Token *
		cur = &sh.Expression(155);
	// a = new Obj;
	// a = new Obj();
	// a = new Obj.member;
	// and
	// a = new Obj().member;
	// are VERY different.
	// Check why we were stopped
	Token *
		nu = &sh.GetCurrent();
	if (nu->GetType() == TokenType::TO_BRACKET_O)
	{
		// new Obj();
		// Get the parameters
		// It's done this way so that
		// we can differentiate between
		sh.Advance();
		cur = &nu->LED(sh, *cur);
		if (nu->Disposable())
		{
			delete nu;
		}
	}
	// Add it to this object
	Add(*cur);
	TokenType::E_TYPE
		type = cur->GetType();
	if (type == TokenType::TC_FUNC_CALL)
	{
		// new String();
		// Get the type of the thing we're "new"ing
		cur = &cur->GetFirstChild();
		type = cur->GetType();
		// Must have at least one child
		// to be made of type TC_FUNC_CALL
		// so don't need checks there.
	}
	else
	{
		// new String;
		// Technically valid but
		// uncommon, thus likely
		// a mistake.  However
		// note made of this for
		// code output optimisation.
		Message::Send(Message::CONSTRUCTOR_CALL);
	}
	if (TokenType::IsReserved(type) || TokenType::IsSymbol(type))
	{
		// Any of the reserved words
		// or a symbol.
		// Check for an upper case letter
		// Not required but common practice
		// and encouraged.
		const char
			ch = *TL::G(*cur).GetString();
		if (ch < 'A' || ch > 'Z')
		{
			// Doesn't start with an upper
			// case letter.  May not start
			// with a lower case one, but
			// very likely.
			Message::Send(Message::NEW_LOWER_OBJECT);
		}
	}
	else if (type == TokenType::TG_Math)
	{
		// Shouldn't be able to
		// create a math object.
		// MAY be able to detect
		// this later in constant
		// variable propogation,
		// but ever then it's not
		// certain.
		// 
		// Can get around this:
		// 
		// var
		//     m = Math,
		//     n = new m();
		// 
		// But it's better than nothing
		Message::Send(Message::NEW_MATH);
	}
	else if (type == TokenType::TK_function)
	{
		// New annonymous function
		// is pointless!
		Message::Send(Message::NEW_ANON);
	}
	else if (type == TokenType::TG_Object)
	{
		Message::Send(Message::NEW_LITERAL, "Object", "{a: 1, b: 2 + 2}");
	}
	else if (type == TokenType::TG_Boolean)
	{
		Message::Send(Message::NEW_LITERAL, "Boolean", "true");
	}
	else if (type == TokenType::TG_Number)
	{
		Message::Send(Message::NEW_LITERAL, "Number", "3.1415");
	}
	else if (type == TokenType::TG_Array)
	{
		Message::Send(Message::NEW_LITERAL, "Array", "[42, 11]");
	}
	else if (type == TokenType::TG_String)
	{
		Message::Send(Message::NEW_LITERAL, "string", "\"string literal\"");
	}
	else if (
		TokenType::IsGlobal(type) ||
		type == TokenType::TO_DOT ||
		type == TokenType::TO_SQUARE_O)
	{
		// Globals are dealt with in
		// their own files.
		// objects and arrays we
		// will have to trust the
		// user that they contain
		// constructor functions.
	}
	else
	{
		// This is NOT one of the listed items
		Message::Send(Message::EXPECTED_IDENTIFIER, SC::R(*cur));
	}
	return *this;
}

std::ostream &
	TKNew::
	Debug(std::ostream & s) const
{
	s << "$Y._new(";
	GetFirstChild().Debug(s);
	s << ')';
	return s;
}

std::ostream &
	TKNew::
	Release(std::ostream & s) const
{
	s << "new";
	DoSpacePar(GetFirstChild(), s);
	return s;
}
