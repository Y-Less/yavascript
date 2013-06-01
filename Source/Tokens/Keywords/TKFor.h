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
//  The Original Code is the yavascript development system - TKFor.h.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "../Types/TT_Control.h"

class TKFor :
	public TT_Control
{
public:
	// cons
		TKFor() :
			TT_Control(TokenType::TK_for)
	{
	};
	
	virtual bool
		RequireSemicolon() const;
	
	virtual std::ostream &
		Debug(std::ostream & s) const;
	
	virtual std::ostream &
		Release(std::ostream & s) const;
	
	virtual Token &
		STD(SyntaxHandler & sh);
	
	virtual bool
		Labelable() const
	{
		return true;
	};
	
protected:
	virtual bool
		Conditional(SyntaxHandler & sh);
	
private:
	bool
		Modifiers(SyntaxHandler & sh);
	
	bool
		Initialisation(SyntaxHandler & sh, Token & first);
};
