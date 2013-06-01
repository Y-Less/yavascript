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
//  The Original Code is the yavascript development system - Message.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Message.h"

#include <iostream>

// Need an arbitrary but largeish
// number.  If the question is:
// "What number shall I pick?"
// Then the ANSWER is obvious:
#define ERROR_ABORT_COUNT (42)

const char *
	Message::sFileName = NULL;

int
	Message::sLineNumber = 0,
	Message::sWarnCount = 0,
	Message::sErrorCount = 0;

Message::E_LEVEL
	Message::sTypes[] =
	{
		E_LEVEL_ERROR,		// UNEXPECTED_EOF
		E_LEVEL_FATAL,		// COULD_NOT_OPEN
		E_LEVEL_FATAL,		// ERROR_ABORT
		E_LEVEL_WARNING,	// UNKNOWN_DIRECTIVE
		E_LEVEL_WARNING,	// EMPTY_DIRECTIVE
		E_LEVEL_WARNING,	// INVALID_PARAMETER
		E_LEVEL_WARNING,	// MISSING_PARAMETER
		E_LEVEL_INFO,		// UNKNOWN_MESSAGE
		E_LEVEL_WARNING,	// UNKNOWN_TARGET_TYPE
		E_LEVEL_FATAL,		// OUT_OF_MEMORY
		E_LEVEL_WARNING,	// INVALID_CHARACTER
		E_LEVEL_ERROR,		// INVALID_NUMBER
		E_LEVEL_WARNING,	// AMBIGUOUS_OCTAL_NUMBER
		E_LEVEL_ERROR,		// UNCLOSED_STRING_LITERAL
		E_LEVEL_FATAL,		// INPUT_STREAM_ERROR
		E_LEVEL_WARNING,	// INVALID_ESCAPE_SEQUENCE
		E_LEVEL_ERROR,		// INVALID_NUMERIC_CONSTANT
		E_LEVEL_ERROR,		// UNKNOWN_TOKEN_TYPE
		E_LEVEL_WARNING,	// USED_RESERVE
		E_LEVEL_ERROR,		// UNEXPECTED_TOKEN
		E_LEVEL_WARNING,	// INT_OVERFLOW
		E_LEVEL_ERROR,		// HEX_FRACTION
		E_LEVEL_WARNING,	// OCT_FRACTION
		E_LEVEL_ERROR,		// EXPECTED_TOKEN
		E_LEVEL_ERROR,		// MISSING_EXPONENT
		E_LEVEL_WARNING,	// OCT_SCIENTIFIC
		E_LEVEL_WARNING,	// MULTIPLE_LABELS
		E_LEVEL_WARNING,	// NOT_LABELABLE
		E_LEVEL_WARNING,	// LABELED_EOF
		E_LEVEL_ERROR,		// EMPTY_VAR_LIST
		E_LEVEL_ERROR,		// UNDEFINED_LABEL
		E_LEVEL_WARNING,	// USE_WITH
		E_LEVEL_WARNING,	// USE_EVAL
		E_LEVEL_WARNING,	// USE_G_FUNCTION
		E_LEVEL_WARNING,	// USED_UNDEFINED
		E_LEVEL_WARNING,	// REDUNDANT_VAR
		E_LEVEL_WARNING,	// IMPLICIT_EOS
		E_LEVEL_WARNING,	// MISSING_EOS
		E_LEVEL_FATAL,		// COULD_NOT_PARSE
		E_LEVEL_FATAL,		// UNKNOWN_NUD
		E_LEVEL_FATAL,		// UNKNOWN_LED
		E_LEVEL_ERROR,		// EXPECTED_IDENTIFIER
		E_LEVEL_ERROR,		// EXPECTED_OPERATOR
		E_LEVEL_ERROR,		// EXPECTED_RH
		E_LEVEL_ERROR,		// EXPECTED_LH
		E_LEVEL_WARNING,	// EXPECTED_EXPRESSION
		E_LEVEL_ERROR,		// UNCLOSED_COMMENT
		E_LEVEL_WARNING,	// IMPLICIT_GLOBAL
		E_LEVEL_WARNING,	// IMPLICIT_GLOBAL_SHADOW
		E_LEVEL_WARNING,	// LOCAL_REDECLARATION
		E_LEVEL_WARNING,	// LOCAL_SHADOW
		E_LEVEL_WARNING,	// LABEL_SHADOW
		E_LEVEL_ERROR,		// MULTI_LABEL
		E_LEVEL_WARNING,	// SYMBOL_SHADOW
		E_LEVEL_IGNORE,		// POSSIBLY_AMBIGUOUS
		E_LEVEL_INFO,		// UNKNOWN_STATE
		E_LEVEL_WARNING,	// NO_EFFECT
		E_LEVEL_IGNORE,		// EXPECTED_GROUP
		E_LEVEL_WARNING,	// EMPTY_STATEMENT
		E_LEVEL_ERROR,		// INVALID_EXPRESSION
		E_LEVEL_ERROR,		// NOT_A_LABEL
		E_LEVEL_ERROR,		// UNMATCHED_CATCH
		E_LEVEL_ERROR,		// UNMATCHED_FINALLY
		E_LEVEL_ERROR,		// UNMATCHED_ELSE
		E_LEVEL_ERROR,		// UNMATCHED_CASE
		E_LEVEL_ERROR,		// UNMATCHED_DEFAULT
		E_LEVEL_ERROR,		// UNMATCHED_COLON
		E_LEVEL_ERROR,		// INVALID_TRY
		E_LEVEL_ERROR,		// INVALID_OPERANDS
		E_LEVEL_WARNING,	// UNINTENDED_ASSIGNMENT
		E_LEVEL_ERROR,		// EXPECTED_FUNCTION
		E_LEVEL_ERROR,		// INVALID_CALL
		E_LEVEL_ERROR,		// INVALID_FOR
		E_LEVEL_ERROR,		// INVALID_VAR_ASSIGNMENT
		E_LEVEL_ERROR,		// UNCLOSED_REGEX
		E_LEVEL_ERROR,		// INVALID_INDEX
		E_LEVEL_ERROR,		// INVALID_IDENTIFIER
		E_LEVEL_ERROR,		// BAD_THIS
		E_LEVEL_WARNING,	// UNINTENDED_EOS
		E_LEVEL_WARNING,	// CONSTRUCTOR_CALL
		E_LEVEL_WARNING,	// NEW_MATH
		E_LEVEL_WARNING,	// NEW_LITERAL
		E_LEVEL_WARNING,	// NEW_ANON
		E_LEVEL_WARNING,	// NEW_LOWER_OBJECT
		E_LEVEL_ERROR,		// EMPTY_SWITCH
		E_LEVEL_ERROR,		// MULTI_DEFAULT
		E_LEVEL_WARNING,	// FUNCTION_REDEFINITION
		E_LEVEL_WARNING,	// LOCAL_FUNCTION_REDEFINITION
		E_LEVEL_WARNING,	// WITH_DECLARATION
		E_LEVEL_ERROR,		// BAD_PARAMETER_COUNT
		E_LEVEL_ERROR,		// PAR_NOT_CONSTANT
		E_LEVEL_INFO,		// UNKNOWN_TYPE_CREATION
		E_LEVEL_ERROR,		// INVALID_MACRO
		E_LEVEL_WARNING,	// MACRO_EXISTS
		E_LEVEL_WARNING,	// UNDEFINED_MACRO
		E_LEVEL_ERROR,		// COMPLEX_PREPROC
		E_LEVEL_ERROR,		// MISSING_ENDIF
		E_LEVEL_ERROR,		// UNMATCHED_ENDIF
		E_LEVEL_ERROR,		// UNMATCHED_PELSE
	};

void
	Message::
	Send(const E_MESSAGE number, const std::string got, const std::string expect)
{
	// Check it's a valid message
	if (number >= E_MESSAGE_MAX)
	{
		// Nope, give an error
		Send(UNKNOWN_MESSAGE);
		return;
	}
	switch (sTypes[number])
	{
		case E_LEVEL_IGNORE:
			// Don't display the message
			return;
		case E_LEVEL_WARNING:
			//return;
			// Increase warn count
			++sWarnCount;
			break;
		case E_LEVEL_ERROR:
			++sErrorCount;
			if (sErrorCount >= ERROR_ABORT_COUNT)
			{
				Send(ERROR_ABORT);
				return;
			}
			break;
		case E_LEVEL_FATAL:
			++sErrorCount;
			break;
	}
	// Display the message
	// Convenience variable
	std::ostream &
		out = std::cout;
	// Output the filename
	if (sFileName)
	{
		out << sFileName << ' ';
		if (!sLineNumber)
		{
			out << ": ";
		}
	}
	// Output the line number
	if (sLineNumber)
	{
		out << '(' << sLineNumber << "): ";
	}
	// Output the error level
	out << sTypes[number] << " (" << int(number) << ") - ";
	// Output the message
	switch (number)
	{
		case UNEXPECTED_EOF:
			out << "Unexpected end of file";
			if (!got.empty())
			{
				out << ", expected: \"" << got << '"';
			}
			break;
		case COULD_NOT_OPEN:
			out << "Could not open file: " << got;
			break;
		case ERROR_ABORT:
			out << "Exceeded " << ERROR_ABORT_COUNT << " errors, aborting compilation";
			break;
		case UNKNOWN_DIRECTIVE:
			out << "Unknown Pre-Processor Directive";
			break;
		case EMPTY_DIRECTIVE:
			out << "Missing Pre-Processor Directive";
			break;
		case INVALID_PARAMETER:
			// FALLTHROUGH
		case MISSING_PARAMETER:
			out << "Missing parameter for option \"" << got << '"';
			break;
		case UNKNOWN_MESSAGE:
			out << "Unknown error message, please report to developers";
			break;
		case UNKNOWN_TARGET_TYPE:
			out << "Unknown ECMAScript implementation, you may get excess warnings";
		case OUT_OF_MEMORY:
			out << "Out of memory";
			break;
		case INVALID_CHARACTER:
			out << "Invalid character";
			if (!got.empty())
			{
				out << " \"" << got << '"';
			}
			out << ", skipping";
			break;
		case INVALID_NUMBER:
			out << "Invalid number: " << got;
			break;
		case AMBIGUOUS_OCTAL_NUMBER:
			out << "Decimal number with leading 0, ambiguous octal number: " << got;
			break;
		case UNCLOSED_STRING_LITERAL:
			out << "Unclosed string literal";
			break;
		case INPUT_STREAM_ERROR:
			out << "Input read error";
			break;
		case INVALID_ESCAPE_SEQUENCE:
			out << "Invalid escape sequence: \"\\" << got << '"';
			break;
		case INVALID_NUMERIC_CONSTANT:
			out << "Invalid numeric digit: \"" << got << '"';
			break;
		case UNKNOWN_TOKEN_TYPE:
			out << "Unknown token type, please report to yavascript developers";
			break;
		case USED_RESERVE:
			out << "Used a reserved word, may cause future incompatibilities: " << got;
			break;
		case UNEXPECTED_TOKEN:
			out << "Unexpected token";
			if (!got.empty())
			{
				out << ": " << got;
			}
			if (!expect.empty())
			{
				out << ", Expected: " << expect;
			}
			break;
		case INT_OVERFLOW:
			out << "Unsigned number overflow";
			break;
		case HEX_FRACTION:
			out << "Can't have a fraction on a hex number";
			break;
		case OCT_FRACTION:
			out << "Can't have a fraction on an octal number, converting to decimal";
			break;
		case EXPECTED_TOKEN:
			out << "Expected token";
			if (!got.empty())
			{
				out << ": \"" << got << '"';
			}
			if (!expect.empty())
			{
				out << ", found: \"" << expect << '"';
			}
			break;
		case MISSING_EXPONENT:
			out << "Missing exponent";
			break;
		case OCT_SCIENTIFIC:
			out << "Can't have an exponent on an octal number, converting to decimal";
			break;
		case MULTIPLE_LABELS:
			out << "Multiple statement labels found";
			break;
		case NOT_LABELABLE:
			out << "Label found on non-label-able statement";
			if (!got.empty())
			{
				out << " Label: \"" << got << '"';
			}
			break;
		case LABELED_EOF:
			out << "Expected statement, found EOF";
			break;
		case EMPTY_VAR_LIST:
			out << "Empty var list";
			break;
		case UNDEFINED_LABEL:
			out << "Undefined label: " << got;
			break;
		case USE_WITH:
			out << "\"with\" is evil, consider revising";
			break;
		case USE_EVAL:
			out << "\"eval\" is evil, consider revising";
			break;
		case USE_G_FUNCTION:
			out << "\"Function\" is evil, consider revising";
			break;
		case USED_UNDEFINED:
			out << "\"undefined\" may not be undefined, consider using \"void 0\" or \"typeof\"";
			break;
		case REDUNDANT_VAR:
			out << "var statement has no effect";
			break;
		case IMPLICIT_EOS:
			out << "Implicit End Of Statement, consider adding a semi-colon";
			break;
		case MISSING_EOS:
			out << "Implicit statement continuation, consider moving the operator";
			break;
		case COULD_NOT_PARSE:
			out << "Could not parse file \"" << got << '"';
			break;
		case UNKNOWN_NUD:
			out << "Base NUD function called";
			break;
		case UNKNOWN_LED:
			out << "Base LED function called";
			break;
		case EXPECTED_IDENTIFIER:
			out << "Expected identifier";
			if (!got.empty())
			{
				out << " but got: \"" << got << '"';
			}
			break;
		case EXPECTED_OPERATOR:
			out << "Expected binary operator but got: \"" << got << '"';
			break;
		case EXPECTED_RH:
			out << "Expected right hand expression";
			if (!got.empty())
			{
				out << " but got: \"" << got << '"';
			}
			break;
		case EXPECTED_LH:
			out << "Expected left hand expression";
			if (!got.empty())
			{
				out << " but got: \"" << got << '"';
			}
			break;
		case EXPECTED_EXPRESSION:
			out << "Expected expression";
			break;
		case UNCLOSED_COMMENT:
			out << "Unclosed stream comment, expected \"*/\"";
			break;
		case IMPLICIT_GLOBAL:
			out << "Implicit global \"" << got << '"';
			break;
		case IMPLICIT_GLOBAL_SHADOW:
			// Very sinister
			out << "Implicit global \"" << got << "\" shadows local label";
			break;
		case LOCAL_REDECLARATION:
			out << "Redeclaration of local variable: " << got;
			break;
		case LOCAL_SHADOW:
			out << "Local variable shadows variable at preceding level: " << got;
			break;
		case LABEL_SHADOW:
			out << "Local variable shadows label name: " << got;
			break;
		case MULTI_LABEL:
			out << "Multiple lables with the same name in current scope: " << got;
			break;
		case SYMBOL_SHADOW:
			out << "Label shadows variable name: " << got;
			break;
		case POSSIBLY_AMBIGUOUS:
			out << "Symbol is similar to a keyword, may be confusing";
			break;
		case UNKNOWN_STATE:
			out << "Unknown symbol state, please report to developers";
			break;
		case NO_EFFECT:
			out << "Expression has no effect";
			break;
		case EXPECTED_GROUP:
			out << "Expected statement group";
			break;
		case EMPTY_STATEMENT:
			out << "Empty statement";
			break;
		case INVALID_EXPRESSION:
			out << "Invalid expression";
				break;
		case NOT_A_LABEL:
			out << "Not a label";
			break;
		case UNMATCHED_CATCH:
			out << "Found \"catch\" without a matching \"try\"";
			break;
		case UNMATCHED_FINALLY:
			out << "Found \"finally\" without a matching \"try\"";
			break;
		case UNMATCHED_ELSE:
			out << "Found \"else\" without a matching \"if\"";
			break;
		case UNMATCHED_CASE:
			out << "Found \"case\" outside a switch statement";
			break;
		case UNMATCHED_DEFAULT:
			out << "Found \"default\" outside a switch statement";
			break;
		case UNMATCHED_COLON:
			out << "Found \":\" without a matching \"?\"";
			break;
		case INVALID_TRY:
			out << "Invalid \"try\" statement, expected \"catch\" or \"finally\"";
			break;
		case INVALID_OPERANDS:
			out << "Invalid operator operands";
			break;
		case UNINTENDED_ASSIGNMENT:
			out << "Possibly unintended assignment";
			break;
		case EXPECTED_FUNCTION:
			out << "Expected function or identifier";
			break;
		case INVALID_CALL:
			out << "Invalid function call";
			break;
		case INVALID_FOR:
			out << "Invalid for statement - usage: for (x in y) or: for (x; y; z)";
			break;
		case INVALID_VAR_ASSIGNMENT:
			out << "Invalid var assignment";
			break;
		case UNCLOSED_REGEX:
			out << "Unclosed Regular Expression literal";
			break;
		case INVALID_INDEX:
			out << "Invalid/empty array index";
			break;
		case INVALID_IDENTIFIER:
			out << "Invalid object property identifier";
			break;
		case BAD_THIS:
			out << "\"this\" is only valid as the start of an object";
			break;
		case UNINTENDED_EOS:
			out << "Possibly unintended \";\", use {} for an empty statement";
			break;
		case CONSTRUCTOR_CALL:
			out << "Missing brackets on new object";
			break;
		case NEW_MATH:
			// This should be an error
			// but it's possible that they
			// redefined "Math" to have a
			// constructor, in which case
			// we want their code to compile.
			out << "\"Math\" is not an instantiateable object";
			break;
		case NEW_LITERAL:
			out << "Found \"new " << got << "\", consider using a basic literal";
			if (!expect.empty())
			{
				out << ", example: " << expect;
			}
			break;
		case NEW_ANON:
			out << "New anonymous functions are pointless, consider revising";
			break;
		case NEW_LOWER_OBJECT:
			out << "Found a constructor not starting with an upper case letter";
			break;
		case EMPTY_SWITCH:
			out << "Switch statement has no cases";
			break;
		case MULTI_DEFAULT:
			out << "Multiple defaults found for the current switch";
			break;
		case FUNCTION_REDEFINITION:
			out << "Named function redefinition, consider using \"name = function () {}\" for reassignable functions";
			break;
		case LOCAL_FUNCTION_REDEFINITION:
			out << "Local named function redefinition, consider using \"name = function () {}\" for reassignable functions";
			break;
		case WITH_DECLARATION:
			out << "Declaring symbols within a \"with\" block is ambiguous";
			break;
		case BAD_PARAMETER_COUNT:
			out << "Function \"" << got << "\" takes " << expect << "parameter";
			// Plurals
			if (expect != "1")
			{
				out << 's';
			}
			break;
		case PAR_NOT_CONSTANT:
			out << "Parameter \"" << got << "\" could not be resolved at compile time";
			break;
		case UNKNOWN_TYPE_CREATION:
			out << "No generator for \"" << got << "\" found, please report";
			break;
		case INVALID_MACRO:
			out << "Invalid or missing macro name";
			break;
		case MACRO_EXISTS:
			out << "Macro \"" << got << "\" already defined";
			break;
		case UNDEFINED_MACRO:
			out << "Macro \"" << got << "\" is not defined";
			break;
		case COMPLEX_PREPROC:
			out << "Could not evaluate constant expression";
			break;
		case MISSING_ENDIF:
			out << "Missing #endif";
			break;
		case UNMATCHED_ENDIF:
			out << "Unmatched #endif";
			break;
		case UNMATCHED_PELSE:
			// PELSE = Pre-processor else
			// Not to be confused with ELSE
			out << "Unmatched #else";
			break;
	}
	// Write a new line
	out << std::endl;
	// Abort if it's fatal
	if (IsFatal(number))
	{
		throw "";
	}
}
