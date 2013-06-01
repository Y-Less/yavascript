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
//  The Original Code is the yavascript development system - TCArray.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TCArray.h"

std::ostream &
	TCArray::
	Debug(std::ostream & s) const
{
	// Function to define an array
	s << "$Y._array(";
	// Function name
	Token::Itter
		itter = *this;
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
	s << ')';
	return s;
}

std::ostream &
	TCArray::
	Release(std::ostream & s) const
{
	s << '[';
	Token::Itter
		itter = *this;
	// Parameters
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
	s << ']';
	return s;
}
