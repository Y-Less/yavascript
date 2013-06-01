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
//  The Original Code is the yavascript development system - Scope.h.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "Symbol.h"

// Interface class for scopes
// Defines methods implemented
// be various scopes.
// Four scope types:
// 
// Global,
// Local,
// Catch,
// With,
// 
class Scope
{
public:
	// Get a variable in the current scope
	virtual Symbol *
		GetSymbol(const char * const name) = 0;
	
	// Get a label in the current scope
	virtual Symbol *
		GetLabel(const char * const name) = 0;
	
	// Get a function in the current scope
	virtual Symbol *
		GetFunction(const char * const name) = 0;
	
	// Add a symbol to the current scope
	virtual Symbol *
		AddSymbol(const char * const name) = 0;
	
	// Add a label to the current scope
	virtual Symbol *
		AddLabel(const char * const name) = 0;
	
	// Add a function to the current scope
	virtual Symbol *
		AddFunction(const char * const name) = 0;
	
	// Checks if the given symbol
	// is really local or inherited
	// Doesn't check labels
	virtual bool
		IsLocal(const char * const name) = 0;
	
	// Set a scope dirty or clean
	// A scope is dirty when it contains
	// one of the evil constructs (eval,
	// with, Function etc).
	virtual void
		SetDirty(const bool set) = 0;
	
	// Get wether or not this scope is dirty
	virtual bool
		GetDirty() const = 0;
	
	// Add a child scope to the current scope
	virtual void
		AddChild(Scope & scope) = 0;
	
	// Get a scope's parent
	virtual Scope &
		GetParent() = 0;
};
