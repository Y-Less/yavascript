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
//  The Original Code is the yavascript development system - TKContinue.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TKContinue.h"

#include "../../Message.h"

#include "../TLiteral.h"

Token &
	TKContinue::
	STD(SyntaxHandler & sh)
{
	// Breaks must be followed by a label
	// on the same line if they're to have
	// a label at all.
	if (sh.SkippedLine())
	{
		// If there's a semi-colon on a
		// different line then it's
		// technicallt wrong for continue.
		if (sh.GetCurrent().GetType() == TokenType::TT_EOS)
		{
			// Semicolon on the wrong line
			// TODO: Warning
		}
	}
	else
	{
		// Fine and happy
		Token &
			label = sh.GetCurrent();
		if (label.GetType() != TokenType::TT_EOS)
		{
			// Label
			// TODO: Resolve the label
			if (label.IsSymbol() || label.IsReserved())
			{
				Add(label);
				m_sSymbols.AddSymbol(TL::G(label).GetString(), false, false, true);
			}
			else
			{
				// TODO: Error
				// Drop the following expression
				Message::Send(Message::NOT_A_LABEL);
				delete &sh.Expression();
			}
		}
		sh.EoS();
	}
	return *this;
}

std::ostream &
	TKContinue::
	Debug(std::ostream & s) const
{
	// TODO
	return s << "continue";
}

std::ostream &
	TKContinue::
	Release(std::ostream & s) const
{
	s << "continue";
	if (HasChildren())
	{
		// Don't need to check for space
		// requirement, it will be needed.
		s << ' ';
		GetFirstChild().Release(s);
	}
	return s;
}
