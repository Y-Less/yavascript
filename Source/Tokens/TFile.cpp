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
//  The Original Code is the yavascript development system - TFile.cpp.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TFile.h"

#include "../Generator.h"

Token &
	TFile::
	STD(SyntaxHandler & sh)
{
	// Based on TOBraceO
	// Group of statements
	TokenType::E_TYPE
		type;
	// Loop through the whole file
	for ( ; ; )
	{
		type = sh.GetCurrent().GetType();
		if (
			type == TokenType::TT__EOF ||
			type == TokenType::TT__END)
		{
			break;
		}
		// Add all statements from the file
		Add(sh.Statement());
	}
	sh.Advance();
	if (HasChildren())
	{
		return *this;
	}
	Dispose();
	return Generator::Null();
}

bool
	TFile::
	IsStatement() const
{
	return true;
}

std::ostream &
	TFile::
	Debug(std::ostream & s) const
{
	Token::Itter
		t = *this;
	bool
		semi = false;
	while (t.HasNext())
	{
		Token &
			cur = t.Next();
		cur.Debug(s);
		if (semi)
		{
			// Should put in a
			// semicolon
			if (cur.IsStatement())
			{
				// Some statements
				// need semicolons
				if (cur.RequireSemicolon())
				{
					s << ';';
				}
			}
			else
			{
				// All expressions
				// need semicolons
				s << ';';
			}
		}
		else
		{
			// This way means there's
			// no semi-colon at the
			// end - every character
			//counts.
			semi = true;
		}
	}
	return s;
}

std::ostream &
	TFile::
	Release(std::ostream & s) const
{
	Token::Itter
		t = *this;
	bool
		semi = false;
	while (t.HasNext())
	{
		if (semi)
		{
			s << ';';
		}
		Token &
			cur = t.Next();
		cur.Release(s);
		// Should put in a
		// semicolon
		if (cur.IsStatement())
		{
			// Some statements
			// need semicolons
			semi = cur.RequireSemicolon();
		}
		else
		{
			// All expressions
			// need semicolons
			semi = true;
		}
	}
	return s;
}
