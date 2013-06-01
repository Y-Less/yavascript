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
//  The Original Code is the yavascript development system - Generator.cpp.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "Generator.h"

#include "Message.h"
#include "Tokens/TGen.h"
#include "Tokens/TNull.h"
#include "Tokens/TNumber.h"
#include "Tokens/TFile.h"
#include "Tokens/CIL/TCCall.h"
#include "Tokens/CIL/TCArray.h"
#include "Tokens/CIL/TCObject.h"
#include "Tokens/Keywords/TKVoid.h"
#include "Tokens/Operators/TOBraceO.h"

#include <exception>

Token &
	Generator::
	Null()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TNull();
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	End()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TGen(TokenType::TT__END);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	EoF()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TGen(TokenType::TT__EOF);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	EoL()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TGen(TokenType::TT_EOL);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	Group()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TOBraceO();
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	File()
{
	Token *
		ret = NULL;
	try
	{
		ret = new TFile();
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	Undef(const bool set)
{
	Token *
		ret = NULL;
	try
	{
		ret = new TKVoid();
		// Javascript ignores voids
		// we don't, so we can have
		// true and false voids,
		// allowing us to use them
		// as either undefined or
		// a bool value as required.
		Token *
			child = new TNumber(set ? "1" : "0");
		ret->Add(*child);
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}

Token &
	Generator::
	CIL(const TokenType::E_TYPE type)
{
	Token *
		ret = NULL;
	try
	{
		switch (type)
		{
			case TokenType::TC_FUNC_CALL:
				ret = new TCCall();
				break;
			case TokenType::TC_ARRAY:
				ret = new TCArray();
				break;
			case TokenType::TC_OBJECT:
				ret = new TCObject();
				break;
			default:
				ret = new TNull();
				break;
		}
	}
	catch (std::exception e)
	{
		Message::Send(Message::OUT_OF_MEMORY);
	}
	return *ret;
}
