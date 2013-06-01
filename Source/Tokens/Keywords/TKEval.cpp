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
//  The Original Code is the yavascript development system - TKEval.cpp.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKEval.h"

#include "../../Message.h"
#include "../../Generator.h"

Token &
	TKEval::
	NUD(SyntaxHandler & sh)
{
	Message::Send(Message::USE_EVAL);
	/*Token &
		f = sh.Advance(TokenType::TO_BRACKET_O);
	if (f.GetType() == TokenType::TO_BRACKET_C)
	{
		// Skip the bracket
		sh.SetRegex(false);
		sh.Advance(TokenType::TO_BRACKET_C);
		// Get rid of the eval
		Dispose();
		// Return nothing
		return Generator::Undef();
		// Optimised out the eval in RARE cases
	}
	// Bad
	Message::Send(Message::USE_EVAL);
	Token &
		contents = sh.Expression(0);
	// Can add code here to try evaluate
	// the contents inline, to get rid
	// of the eval in more cases.
	// However this is a lot of work to
	// be done at a later date.
	// Having said that, the design of
	// the tokeniser and compiler do
	// mean that we can just instantiate
	// a new instance of SyntaxHandler
	// and pass a string stream to the
	// tokeniser, making this design
	// excellent for future expansion!
	sh.Advance(TokenType::TO_BRACKET_C);
	// From now on treat it like a regular
	// function call for simplicity (as
	// that is technically what it is).
	Token &
		func = Generator::CIL(TokenType::TC_FUNC_CALL);
	func.Add(*this);
	func.Add(contents);*/
	return *this;
}

std::ostream &
	TKEval::
	Debug(std::ostream & s) const
{
	// TODO
	return s << "eval";
}

std::ostream &
	TKEval::
	Release(std::ostream & s) const
{
	return s << "eval";
}
