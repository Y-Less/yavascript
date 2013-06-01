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
//  The Original Code is the yavascript development system - main.cpp.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include <iostream>
#include <fstream>

#include "Source/Compiler.h"
#include "Source/Message.h"
#include "Source/Optimiser.h"

// Auto-incrementing build versioning
// http://www.codeproject.com/KB/dotnet/build_versioning.aspx
#include "version.info"

// For consistency and brackets
#define VERSION_MAJOR (MAJORVERSION)
#define VERSION_MINOR (MINORVERSION)
#define VERSION_BUILD (BUILDNUMBER)

int main(int argc, char * argv [])
{
	try
	{
		std::cout
			<< std::endl
			<< "=======================" << std::endl
			<< "| yavascript Compiler |" << std::endl
			<< "=======================" << std::endl
			<< "|  Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_BUILD << "  |" << std::endl
			<< "=======================" << std::endl
			<< std::endl;
		//std::iostream
		//	o();
		Compiler &
			c = Compiler::Get();
		if (!c.Options(argc, argv))
		{
			std::cout
				<< "Usage: yavascript -f [filename] -o [output] (-t [target]) (-w [warning to ignore])" << std::endl
				<< "Targets: web" << std::endl
				<< "Warnings: shadow, eos" << std::endl;
			return 0;
		}
		Token &
			tree = c.Parse();
		c.GetPreprocessor().CheckEnd();
		if (Message::GetErrorCount())
		{
			// Don't generate source if
			// the read failed as it'll
			// contain gibberish.
			std::cout
				<< std::endl
				<< "Compilation failed" << std::endl;
		}
		else
		{
			// Optimise and output
			Optimiser::Do(tree).Release(c.GetOutput());
			std::cout
				<< std::endl
				<< "Compilation complete" << std::endl;
		}
	}
	catch (char * c)
	{
		std::cout
			<< std::endl
			<< "Compilation aborted" << c << std::endl;
	}
	std::cout
		<< std::endl
		<< " - " << Message::GetErrorCount() << " Errors" << std::endl
		<< " - " << Message::GetWarnCount() << " Warnings" << std::endl;
	return 0;
}
