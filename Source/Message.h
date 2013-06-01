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
//  The Original Code is the yavascript development system - Message.h.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#pragma once

#include <string>
#include <ostream>

// Would normally use a namespace here
// But that doesn't support private/public
// You can encourage it, but not enforce it
class Message
{
public:
	// Information messages
	enum E_MESSAGE
	{
		UNEXPECTED_EOF = 0,
		COULD_NOT_OPEN,
		ERROR_ABORT,
		UNKNOWN_DIRECTIVE,
		EMPTY_DIRECTIVE,
		INVALID_PARAMETER,
		MISSING_PARAMETER,
		UNKNOWN_MESSAGE,
		UNKNOWN_TARGET_TYPE,
		OUT_OF_MEMORY,
		INVALID_CHARACTER,
		INVALID_NUMBER,
		AMBIGUOUS_OCTAL_NUMBER,
		UNCLOSED_STRING_LITERAL,
		INPUT_STREAM_ERROR,
		INVALID_ESCAPE_SEQUENCE,
		INVALID_NUMERIC_CONSTANT,
		UNKNOWN_TOKEN_TYPE,
		USED_RESERVE,
		UNEXPECTED_TOKEN,
		INT_OVERFLOW,
		HEX_FRACTION,
		OCT_FRACTION,
		EXPECTED_TOKEN,
		MISSING_EXPONENT,
		OCT_SCIENTIFIC,
		MULTIPLE_LABELS,
		NOT_LABELABLE,
		LABELED_EOF,
		EMPTY_VAR_LIST,
		UNDEFINED_LABEL,
		USE_WITH,
		USE_EVAL,
		USE_G_FUNCTION,
		USED_UNDEFINED,
		REDUNDANT_VAR,
		IMPLICIT_EOS,
		MISSING_EOS,
		COULD_NOT_PARSE,
		UNKNOWN_NUD,
		UNKNOWN_LED,
		EXPECTED_IDENTIFIER,
		EXPECTED_OPERATOR,
		EXPECTED_RH,
		EXPECTED_LH,
		EXPECTED_EXPRESSION,
		UNCLOSED_COMMENT,
		IMPLICIT_GLOBAL,
		IMPLICIT_GLOBAL_SHADOW,
		LOCAL_REDECLARATION,
		LOCAL_SHADOW,
		LABEL_SHADOW,
		MULTI_LABEL,
		SYMBOL_SHADOW,
		POSSIBLY_AMBIGUOUS,
		UNKNOWN_STATE,
		NO_EFFECT,
		EXPECTED_GROUP,
		EMPTY_STATEMENT,
		INVALID_EXPRESSION,
		NOT_A_LABEL,
		UNMATCHED_CATCH,
		UNMATCHED_FINALLY,
		UNMATCHED_ELSE,
		UNMATCHED_CASE,
		UNMATCHED_DEFAULT,
		UNMATCHED_COLON,
		INVALID_TRY,
		INVALID_OPERANDS,
		UNINTENDED_ASSIGNMENT,
		EXPECTED_FUNCTION,
		INVALID_CALL,
		INVALID_FOR,
		INVALID_VAR_ASSIGNMENT,
		UNCLOSED_REGEX,
		INVALID_INDEX,
		INVALID_IDENTIFIER,
		BAD_THIS,
		UNINTENDED_EOS,
		CONSTRUCTOR_CALL,
		NEW_MATH,
		NEW_LITERAL,
		NEW_ANON,
		NEW_LOWER_OBJECT,
		EMPTY_SWITCH,
		MULTI_DEFAULT,
		FUNCTION_REDEFINITION,
		LOCAL_FUNCTION_REDEFINITION,
		WITH_DECLARATION,
		BAD_PARAMETER_COUNT,
		PAR_NOT_CONSTANT,
		UNKNOWN_TYPE_CREATION,
		INVALID_MACRO,
		MACRO_EXISTS,
		UNDEFINED_MACRO,
		COMPLEX_PREPROC,
		MISSING_ENDIF,
		UNMATCHED_ENDIF,
		UNMATCHED_PELSE,
		// Add new messages here
		E_MESSAGE_MAX,
	};
	
	// Message levels
	enum E_LEVEL
	{
		E_LEVEL_UNSET = 0,	// Default value, warn that it's not set
		E_LEVEL_IGNORE,		// Ignore the problem, don't display a message
		E_LEVEL_INFO,		// Information, just tell them something
		E_LEVEL_WARNING,	// Warning, make it a warning
		E_LEVEL_ERROR,		// Error, don't make the file
		E_LEVEL_FATAL		// Fatal, give up now!
	};
	
	friend std::ostream &
		operator<<(std::ostream & o, const E_LEVEL & m)
	{
		switch (m)
		{
			case E_LEVEL_INFO:
				return o << "Info";
			case E_LEVEL_WARNING:
				return o << "Warning";
			case E_LEVEL_ERROR:
				return o << "Error";
			case E_LEVEL_FATAL:
				return o << "Fatal Error";
		}
		// "E_LEVEL_IGNORE" is ignored, so
		// we don't need code to display it
		return o;
	};
	
	static void
		Send(const E_MESSAGE number, const std::string got = "", const std::string expect = "");
	
	static void
		SetValues(char * const file, int line)
	{
		// Only copies the pointer
		// If the remote deletes the string
		// we will have a problem here
		// Basically don't do it!
		sFileName = file;
		sLineNumber = line;
	};
	
	static void
		SetLevel(const E_MESSAGE number, const E_LEVEL level)
	{
		// This allows for customisation of error messages
		// It's never actually called, but it's here
		// for future ease of expansion.  The original
		// warning system was designed with this in mind
		// to allow for various options
		if (number < E_MESSAGE_MAX)
		{
			sTypes[number] = level;
		}
	};
	
	static const E_LEVEL
		GetLevel(const E_MESSAGE number)
	{
		if (number < E_MESSAGE_MAX)
		{
			return sTypes[number];
		}
		return E_LEVEL_UNSET;
	};
	
	static int
		GetWarnCount()
	{
		return sWarnCount;
	};
	
	static int
		GetErrorCount()
	{
		return sErrorCount;
	};
	
private:
	// Used to determine wether or not to
	// terminate compilation
	static bool
		IsFatal(const E_MESSAGE number)
	{
		return sTypes[number] == E_LEVEL_FATAL;
	};
	
	// Used to determine wether or not to
	// display the message
	static bool
		IsIgnored(const E_MESSAGE number)
	{
		return sTypes[number] == E_LEVEL_IGNORE;
	};
	
	// Array of message levels
	static E_LEVEL
		sTypes[E_MESSAGE_MAX];
	
	static const char *
		sFileName;
	
	static int
		sLineNumber,
		sWarnCount,
		sErrorCount;
};
