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
//  The Original Code is the yavascript development system - TString.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TString.h"

std::ostream &
	TString::
	Debug(std::ostream & s) const
{
	// These do the same thing
	return Release(s);
}

std::ostream &
	TString::
	Release(std::ostream & s) const
{
	// Determine string type
	char *
		c = GetString();
	int
		dq = 0, // Double quote count
		sq = 0; // Single quote count
	while (*c)
	{
		if (*c == '\'')
		{
			++sq;
		}
		else if (*c == '"')
		{
			++dq;
		}
		c++;
	}
	if (dq < sq)
	{
		// More single quotes
		// Surround in double quotes
		s << '"';
		DoStringOut(s, true);
		s << '"';
	}
	else
	{
		// Surround in single quotes
		s << '\'';
		DoStringOut(s, false);
		s << '\'';
	}
	return s;
}

void
	TString::
	DoStringOut(std::ostream & s, const bool dq) const
{
	char *
		c = GetString();
	char
		ch;
	int
		count;
	while ((ch = *c++))
	{
		if (ch > 128)
		{
			// Unicode
			count = (ch & 0x40) ? ((ch & 0x20) ? ((ch & 0x10) ? (3) : (2)) : (1)) : (0);
			s << ch;
			while (count--)
			{
				s << (*c++);
			}
		}
		else
		{
			switch (ch)
			{
				case '\'':
					if (dq)
					{
						s << '\'';
					}
					else
					{
						s << "\\'";
					}
					break;
				case '"':
					if (dq)
					{
						s << "\\\"";
					}
					else
					{
						s << '"';
					}
					break;
				case '\r':
					if (*c == '\n')
					{
						c++;
					}
					// FALLTHROUGH
				case '\n':
					s << "\\n";
					break;
				case '\t':
					s << "\\t";
					break;
				case '\b':
					s << "\\b";
					break;
				case '\f':
					s << "\\f";
					break;
				case '\v':
					s << "\\v";
					break;
				case '\\':
					s << "\\\\";
					break;
				case 0x80:
					s << "\0";
					break;
				default:
					s << ch;
					break;
			}
		}
	}
}
