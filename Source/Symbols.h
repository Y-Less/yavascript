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
//  The Original Code is the yavascript development system - Symbols.h.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "Scope.h"

class Symbols
{
public:
	// Add a symbol to the symbol table
	virtual Symbol &
		AddSymbol(const char * const name, const bool bDec = false, const bool bFunction = false, const bool bLabel = false) = 0;
	
	// Set current scope as unoptimisable
	virtual void
		DirtyCurrent(const bool set) = 0;
	
	// Add a new scope
	virtual Scope &
		AddScope(Scope & scope) = 0;
	
	// End the current scope
	virtual Scope &
		EndScope() = 0;
	
	virtual Scope &
		GetCurrent() = 0;
};
