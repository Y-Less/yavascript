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
//  The Original Code is the yavascript development system - WithScope.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "WithScope.h"

#include "Message.h"

#include <exception>

// dest
	WithScope::
	~WithScope()
{
	// Destroy local symbols
}

// Get a variable in the current scope
Symbol *
	WithScope::
	GetSymbol(const char * const name)
{
	Symbol *
		ret = Find(name, m_symbols);
	if (ret)
	{
		return ret;
	}
	return Add(name, &m_symbols);
}

// Get a label in the current scope
Symbol *
	WithScope::
	GetLabel(const char * const name)
{
	// "with" scopes defer to their
	// parent on labels only
	return m_parent->GetLabel(name);
}

// Get a function in the current scope
Symbol *
	WithScope::
	GetFunction(const char * const name)
{
	Symbol *
		ret = Find(name, m_functions);
	if (ret)
	{
		return ret;
	}
	return Add(name, &m_functions);
}

bool
	WithScope::
	IsLocal(const char * const name)
{
	// Everything in a "with" scope
	// counts as local as it may
	// or may not be...
	return true;
}

// Add a symbol to the current scope
Symbol *
	WithScope::
	AddSymbol(const char * const name)
{
	return Add(name, &m_symbols);
}

// Add a label to the current scope
Symbol *
	WithScope::
	AddLabel(const char * const name)
{
	// "with" scopes defer to their
	// parent on labels only
	return m_parent->AddLabel(name);
}

// Add a function to the current scope
Symbol *
	WithScope::
	AddFunction(const char * const name)
{
	return Add(name, &m_functions);
}

// Find a symbol name from the given list
Symbol *
	WithScope::
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
	WithScope::
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
