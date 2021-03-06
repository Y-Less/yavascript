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
//  The Original Code is the yavascript development system - TOMulAss.cpp.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TOMulAss.h"

std::ostream &
	TOMulAss::
	Debug(std::ostream & s) const
{
	// Function to do the assign
	s << '(';
	GetChild(0).Debug(s);
	s << " = $Y._mulAss(";
	// Parameters
	GetChild(0).Debug(s);
	s << ", ";
	GetChild(1).Debug(s);
	// End
	s << "))";
	return s;
}
