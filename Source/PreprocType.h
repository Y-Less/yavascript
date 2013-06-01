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
//  The Original Code is the yavascript development system - PreprocType.h.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <ostream>

class PreprocType
{
public:
	enum E_PREPROC
	{
		PP__NONE = 0,
		PP_IF,
		PP_IFDEF,
		PP_IFNDEF,
		PP_ELSE,
		PP_ENDIF,
		PP_DEFINE,
		PP_UNDEF,
		PP_INCLUDE,
		PP_PRAGMA,
	};
	
	friend std::ostream &
		operator<<(std::ostream &s, const E_PREPROC t)
	{
		switch (t)
		{
			case PP_IF:
				return s << "#if";
			case PP_IFDEF:
				return s << "#ifdef";
			case PP_IFNDEF:
				return s << "#ifndef";
			case PP_ELSE:
				return s << "#else";
			case PP_ENDIF:
				return s << "#endif";
			case PP_DEFINE:
				return s << "#define";
			case PP_UNDEF:
				return s << "#undef";
			case PP_INCLUDE:
				return s << "#include";
			case PP_PRAGMA:
				return s << "#pragma";
		}
		return s;
	};
};
