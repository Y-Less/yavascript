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
//  The Original Code is the yavascript development system - TNumber.cpp.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#include "TNumber.h"

#include <math.h>

double
	TNumber::
	GetNumeric() const
{
	double
		value = 0.0;
	long
		exp = 0,
		dp = 0;
	bool
		decimal = false,
		exponent = false;
	char *
		str = GetString();
	char
		ch;
	while ((ch = *str++))
	{
		switch (ch)
		{
			case '.':
				decimal = true;
				break;
			case 'e':
			case 'E':
				exponent = true;
				break;
			default:
				if (decimal)
				{
					value = value + ((ch - '0') / dp++);
				}
				else if (exponent)
				{
					exp = (exp * 10) + (ch - '0');
				}
				else
				{
					value = (value * 10) + (ch - '0');
				}
				break;
		}
	}
	if (exp)
	{
		return value * pow(10.0, exp);
	}
	else
	{
		return value;
	}
}
