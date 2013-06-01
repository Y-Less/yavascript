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
//  The Original Code is the yavascript development system - SymbolTable.cpp.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "SymbolTable.h"

#include "Message.h"

// cons
	SymbolTable::
	SymbolTable() :
		m_stGlobal()
{
	m_stCurrent = &this->m_stGlobal;
}

// Creates a new scope table
// and sets it as the current
Scope &
	SymbolTable::
	AddScope(Scope & scope)
{
	m_stCurrent->AddChild(scope);
	m_stCurrent = &scope;
	return scope;
}

// Ends the current scope
// and drops back to the parent
Scope &
	SymbolTable::
	EndScope()
{
	m_stCurrent = &m_stCurrent->GetParent();
	return *m_stCurrent;
}

// 
// Six Combinations:
// 
// Nothing:				Regular variable used normally
// bDec:				Regular variable declaration
// bFunction + bDec:	function bla()
// bFunction:			bla()
// bLabel + bDec:		moo:
// bLabel:				goto moo;
// 

Symbol &
	SymbolTable::
	AddSymbol(const char * const name, const bool bDec, const bool bFunction, const bool bLabel)
{
	if (bLabel)
	{
		// Accessing a label
		if (bDec)
		{
			// Declaring a label
			Symbol *
				label = m_stCurrent->GetLabel(name);
			if (label)
			{
				// Already exists
				Message::Send(Message::MULTI_LABEL, name);
				return *label;
			}
			else
			{
				// Add it
				if (m_stCurrent->GetSymbol(name) || m_stCurrent->GetFunction(name))
				{
					// Already exists as a variable
					Message::Send(Message::SYMBOL_SHADOW, name);
				}
				return *m_stCurrent->AddLabel(name);
			}
		}
		else
		{
			// Using a label
			Symbol *
				label = m_stCurrent->GetLabel(name);
			if (label)
			{
				return *label;
			}
			else
			{
				Message::Send(Message::UNDEFINED_LABEL, name);
				return *m_stCurrent->AddLabel(name);
			}
		}
	}
	else if (bDec)
	{
		if (bFunction)
		{
			// Declaring a named function
			// These are ones using:
			// function name() {};
			// syntax, these are handled
			// differently by yavascript.
			// It's assumed that if you use
			// that syntax you don't want
			// to reuse that symbol, if you
			// want to assign a function to
			// a variable which can be
			// altered use:
			// name = function() {};
			// 
			// See if the symbol already exists
			Symbol *
				ret = m_stCurrent->GetSymbol(name);
			if (!ret)
			{
				// Not a symbol, try as a function
				ret = m_stCurrent->GetFunction(name);
			}
			// NOT "else"
			if (ret)
			{
				Message::Send(Message::FUNCTION_REDEFINITION);
				return *ret;
			}
			if (m_stCurrent->GetLabel(name))
			{
				// Shadowing a label
				Message::Send(Message::LABEL_SHADOW);
			}
			return *m_stCurrent->AddFunction(name);
		}
		else
		{
			// Declaring a regular variable properly
			Symbol *
				ret = m_stCurrent->GetSymbol(name);
			if (ret)
			{
				// Already have a symbol of this name
				if (m_stCurrent->IsLocal(name))
				{
					// Redeclaration of local
					Message::Send(Message::LOCAL_REDECLARATION, name);
					return *ret;
				}
				else
				{
					// Redeclaration of global
					Message::Send(Message::LOCAL_SHADOW, name);
				}
			}
			else
			{
				ret = m_stCurrent->GetFunction(name);
				if (ret)
				{
					// Already have a function with this name
					if (m_stCurrent->IsLocal(name))
					{
						Message::Send(Message::LOCAL_FUNCTION_REDEFINITION);
						return *ret;
					}
					else
					{
						Message::Send(Message::FUNCTION_REDEFINITION);
					}
				}
			}
			return *m_stCurrent->AddSymbol(name);
		}
	}
	else
	{
		// Using symbols and functions are
		// handled together as they're
		// essentially the same as one may
		// easilly by the other.
		// See if the symbol already exists
		Symbol *
			ret = m_stCurrent->GetSymbol(name);
		if (!ret)
		{
			// Not a symbol, try as a function
			ret = m_stCurrent->GetFunction(name);
		}
		// NOT "else"
		if (ret)
		{
			return *ret;
		}
		if (m_stCurrent->GetLabel(name))
		{
			// Shadowing a label
			Message::Send(Message::IMPLICIT_GLOBAL_SHADOW, name);
		}
		else
		{
			// Doesn't exist, create globally
			Message::Send(Message::IMPLICIT_GLOBAL, name);
		}
		// Add it as a symbol as it's not a
		// named function so we don't know
		// what it's meant to be
		return *m_stGlobal.AddSymbol(name);
	}
}
