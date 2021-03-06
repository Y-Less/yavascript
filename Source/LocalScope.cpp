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
//  The Original Code is the yavascript development system - LocalScope.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "LocalScope.h"

#include "Message.h"

#include <exception>

// dest
	LocalScope::
	~LocalScope()
{
	// Destroy local symbols
}

// Get a variable in the current scope
Symbol *
	LocalScope::
	GetSymbol(const char * const name)
{
	Symbol *
		ret = Find(name, m_symbols);
	if (ret)
	{
		return ret;
	}
	return m_parent->GetSymbol(name);
}

// Get a label in the current scope
Symbol *
	LocalScope::
	GetLabel(const char * const name)
{
	// Don't propogate labels
	return Find(name, m_labels);
}

// Get a function in the current scope
Symbol *
	LocalScope::
	GetFunction(const char * const name)
{
	Symbol *
		ret = Find(name, m_functions);
	if (ret)
	{
		return ret;
	}
	return m_parent->GetFunction(name);
}

bool
	LocalScope::
	IsLocal(const char * const name)
{
	return Find(name, m_symbols) || Find(name, m_functions);
}

// Add a symbol to the current scope
Symbol *
	LocalScope::
	AddSymbol(const char * const name)
{
	return Add(name, &m_symbols);
}

// Add a label to the current scope
Symbol *
	LocalScope::
	AddLabel(const char * const name)
{
	return Add(name, &m_labels);
}

// Add a function to the current scope
Symbol *
	LocalScope::
	AddFunction(const char * const name)
{
	return Add(name, &m_functions);
}

// Find a symbol name from the given list
Symbol *
	LocalScope::
	Find(const char * const name, Symbol * start) const
{
	while (start)
	{
		if (start->CheckName(name))
		{
			return start;
		}
		start = start->GetNext();
	}
	return NULL;
}

Symbol *
	LocalScope::
	Add(const char * const name, Symbol ** start)
{
	Symbol *
		nu = NULL;
	try
	{
		// Create the symbol
		nu = new Symbol(name);
		// Add it to the list
		// Order is important, but it's
		// easy to go backwards
		nu->SetNext(*start);
		*start = nu;
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
		nu = NULL;
	}
	return nu;
}
