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
//  The Original Code is the yavascript development system - CatchScope.cpp. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "CatchScope.h"

#include "Message.h"

#include <exception>

// dest
	CatchScope::
	~CatchScope()
{
	// Destroy local symbols
}

// Get a variable in the current scope
Symbol *
	CatchScope::
	GetSymbol(const char * const name)
{
	if (m_error->CheckName(name))
	{
		return m_error;
	}
	return m_parent->GetSymbol(name);
}

// Get a label in the current scope
Symbol *
	CatchScope::
	GetLabel(const char * const name)
{
	return m_parent->GetLabel(name);
}

// Get a function in the current scope
Symbol *
	CatchScope::
	GetFunction(const char * const name)
{
	return m_parent->GetFunction(name);
}

bool
	CatchScope::
	IsLocal(const char * const name)
{
	if (m_error->CheckName(name))
	{
		return true;
	}
	return m_parent->IsLocal(name);
}

// Add a symbol to the current scope
Symbol *
	CatchScope::
	AddSymbol(const char * const name)
{
	return m_parent->AddSymbol(name);
}

// Add a label to the current scope
Symbol *
	CatchScope::
	AddLabel(const char * const name)
{
	return m_parent->AddLabel(name);
}

// Add a function to the current scope
Symbol *
	CatchScope::
	AddFunction(const char * const name)
{
	return m_parent->AddFunction(name);
}

Symbol *
	CatchScope::
	MakeCatchSymbol(const char * const name)
{
	Symbol *
		nu = NULL;
	try
	{
		// Create the symbol
		nu = new Symbol(name);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
		nu = NULL;
	}
	return nu;
}
