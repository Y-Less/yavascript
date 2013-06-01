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
//  The Original Code is the yavascript development system - TCCall.cpp.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TCCall.h"

#include <iostream>

std::ostream &
	TCCall::
	Debug(std::ostream & s) const
{
	// Function to call a function
	s << "$Y._call(";
	// Function name
	Token::Itter
		itter = *this;
	itter.Next().Debug(s);
	// Parameters
	s << ", [";
	bool
		p = false;
	while (itter.HasNext())
	{
		if (p)
		{
			s << ", ";
		}
		else
		{
			p = true;
		}
		itter.Next().Debug(s);
	}
	s << "])";
	return s;
}

std::ostream &
	TCCall::
	Release(std::ostream & s) const
{
	// Function name
	if (GetFirstChild().GetType() == TokenType::TK_function)
	{
		s << '(';
		GetFirstChild().Release(s);
		s << ')';
	}
	else
	{
		GetFirstChild().Release(s);
	}
	Token::Itter
		itter = *this;
	itter.Next();
	// Parameters
	s << '(';
	bool
		p = false;
	while (itter.HasNext())
	{
		if (p)
		{
			s << ',';
		}
		else
		{
			p = true;
		}
		itter.Next().Release(s);
	}
	s << ')';
	return s;
}
