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
//  The Original Code is the yavascript development system - SymbolTable.h.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "GlobalScope.h"
#include "Symbols.h"

class SymbolTable :
	public Symbols
{
public:
	// cons
		SymbolTable();
	
	//dest
		~SymbolTable()
	{
	};
	
	virtual Symbol &
		AddSymbol(const char * const name, const bool bDec = false, const bool bFunction = false, const bool bLabel = false);
	
	// Set as unoptimisable
	virtual void
		DirtyCurrent(const bool set)
	{
		m_stCurrent->SetDirty(set);
	};
	
	virtual Scope &
		AddScope(Scope & scope);
	
	virtual Scope &
		EndScope();
	
	virtual Scope &
		GetCurrent()
	{
		return *m_stCurrent;
	};
	
private:
	// cons
		SymbolTable(const SymbolTable & s) :
			m_stGlobal()
	{
	};
	
	SymbolTable &
		operator=(const SymbolTable & s)
	{
		return *this;
	};
	
	GlobalScope
		m_stGlobal;
	
	Scope *
		m_stCurrent;
};
