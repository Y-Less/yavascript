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
//  The Original Code is the yavascript development system - StringCast.h.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <string>
#include <sstream>

namespace SC
{
	// Converts a given item to a string where possible
	// Used so we can do it inline instead of messing about
	// Simply sets up a stream, outputs the value to the
	// stream (assuming it has a relevant stream function)
	// then returns the stream converted to a string.
	// Reference version
	template <typename T>
	std::string
		R(T &i)
	{
		// Set up the stream
		std::ostringstream
			s;
		// Output to the stream
		s << i;
		// Return the string version
		return s.str();
	};
	
	// Literal version
	template <typename T>
	std::string
		L(T i)
	{
		// Set up the stream
		std::ostringstream
			s;
		// Output to the stream
		s << i;
		// Return the string version
		return s.str();
	};
};
