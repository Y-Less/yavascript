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
//  The Original Code is the yavascript development system - TKReturn.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKReturn.h"

#include "../../Message.h"

Token &
	TKReturn::
	STD(SyntaxHandler & sh)
{
	if (sh.SkippedLine())
	{
		// return is on it's own
		Message::Send(Message::IMPLICIT_EOS);
		return *this;
	}
	else if (sh.GetCurrent().GetType() != TokenType::TT_EOS)
	{
		Add(sh.Expression());
	}
	// This should end with a semi-colon
	sh.EoS();
	return *this;
}

std::ostream &
	TKReturn::
	Debug(std::ostream & s) const
{
	// TODO
	return s;
}

std::ostream &
	TKReturn::
	Release(std::ostream & s) const
{
	s << "return";
	if (HasChildren())
	{
		DoSpacePar(GetFirstChild(), s);
	}
	return s;
}
