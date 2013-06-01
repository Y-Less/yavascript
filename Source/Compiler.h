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
//  The Original Code is the yavascript development system - Compiler.h.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include "Parser.h"
#include "SymbolTable.h"
#include "FileList.h"
#include "Preprocessor.h"

#include <iostream>

// Singleton
// Controls everything
class Compiler
{
public:
	static Compiler &
		Get();
	
	Symbols &
		GetSymbols()
	{
		return m_symbols;
	};

	Preprocessor &
		GetPreprocessor()
	{
		return m_preProc;
	};
	
	Token &
		Parse();
	
	bool
		Options(int argc, char * argv []);
	
	void
		AddFile(const char * const file);
	
	std::ostream &
		GetOutput() const
	{
		return *m_out;
	};
	
private:
	// Builds the parse tree
	Parser
		m_parser;
	
	// Table of symbols defined
	// in this script.
	SymbolTable
		m_symbols;
	
	// List of files to compile
	FileList
		m_files;
	
	// The preprocessor
	Preprocessor
		m_preProc;
	
	// cons
		Compiler() :
			m_symbols(),
			m_files(),
			m_parser(m_files),
			m_bGotFile(false),
			m_preProc(),
			m_out(NULL)
	{
	};
	
	// dest
		~Compiler()
	{
	};
	
	// cons
		Compiler(const Compiler & c) :
			m_symbols(),
			m_files(),
			m_parser(m_files),
			m_bGotFile(false),
			m_preProc(),
			m_out(NULL)
	{
	};
	
	Compiler &
		operator=(const Compiler & c)
	{
		return *this;
	};
	
	enum E_OPTION
	{
		E_OPTION_WARNING = 0,
		E_OPTION_FILE,
		E_OPTION_TARGET,
		E_OPTION_OUTPUT,
	};
	
	bool
		m_bGotFile;
	
	std::ostream *
		m_out;
	
	void
		SetOutput(const char * const file);
	
	bool
		SetOption(E_OPTION key, const char * const value);
	
	void
		DoOption(int argc, char * argv [], const char * const option, const E_OPTION value, const bool par);
};
