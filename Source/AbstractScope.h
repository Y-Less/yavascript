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
//  The Original Code is the yavascript development system - AbstractScope.h.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "Scope.h"

// A catch scope is just a minor extension
// of the enclosing scope.  And variables
// declared in it are part of the parent.
// The only variable this has locally is
// the single variable declared in the
// catch expression.
class AbstractScope :
	public Scope
{
public:
	// cons
		AbstractScope() :
			m_child(NULL),
			m_next(NULL)
	{
	}
	
	// Add a child scope to the current scope
	virtual void
		AddChild(Scope & scope);
	
private:
	Scope
		* m_child,
		* m_next;
	
	// cons
		AbstractScope(Scope & s)
	{
	};
	
	AbstractScope &
		operator=(Scope & s)
	{
		return *this;
	}
};
