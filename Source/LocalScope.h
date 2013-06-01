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
//  The Original Code is the yavascript development system - LocalScope.h.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "AbstractScope.h"

class LocalScope :
	public AbstractScope
{
public:
	// cons
		LocalScope(Scope * parent) :
			AbstractScope(),
			m_bDirty(false),
			m_symbols(NULL),
			m_functions(NULL),
			m_labels(NULL),
			m_parent(parent)
	{
	};
	
	// dest
		~LocalScope();
	
	// Get a variable in the current scope
	virtual Symbol *
		GetSymbol(const char * const name);
	
	// Get a label in the current scope
	virtual Symbol *
		GetLabel(const char * const name);
	
	// Get a function in the current scope
	virtual Symbol *
		GetFunction(const char * const name);
	
	// Add a symbol to the current scope
	virtual Symbol *
		AddSymbol(const char * const name);
	
	// Add a label to the current scope
	virtual Symbol *
		AddLabel(const char * const name);
	
	// Add a function to the current scope
	virtual Symbol *
		AddFunction(const char * const name);
	
	virtual bool
		IsLocal(const char * const name);
	
	// Set a scope dirty or clean
	// A scope is dirty when it contains
	// one of the evil constructs (eval,
	// with, Function etc).
	virtual void
		SetDirty(const bool set)
	{
		m_bDirty = set;
		if (set)
		{
			// Don't unset it
			// could be dirty for other
			// reasons too.
			m_parent->SetDirty(true);
		}
	};
	
	// Get wether or not this scope is dirty
	virtual bool
		GetDirty() const
	{
		return m_bDirty;
	};
	
	virtual Scope &
		GetParent()
	{
		return *m_parent;
	};
	
private:
	bool
		m_bDirty;
	
	Symbol
		* m_symbols,
		* m_labels,
		* m_functions;
	
	Scope *
		m_parent;
	
	Symbol *
		Find(const char * const name, Symbol * start) const;
	
	Symbol *
		Add(const char * const name, Symbol ** start);
};
