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
//  The Original Code is the yavascript development system - Timers.js.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

/*----------------------------------------------------------------------------*-
				   =======================================
				    Yavascript Includes - Timer Functions
				   =======================================
Description:
	Defines a set of cross-browser timer functions for passing parameters in IE.
Legal:
	Copyright (C) 2007 Alex "Y_Less" Cole. All Rights Reserved.
	
	The contents of this file are subject to the Mozilla Public License
	Version 1.1 (the "License"); you may not use this file except in
	compliance with the License. You may obtain a copy of the License at
	http://www.mozilla.org/MPL/

	Software distributed under the License is distributed on an "AS IS"
	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
	License for the specific language governing rights and limitations
	under the License.

	The Original Code is Timers.js.
Credits:
	Based on a concept by J.S. Cole
Version:
	0.1
Changelog:
	17/08/08:
		First version.
Functions:
	$timeout	- Cross browser setTimeout code to pass variables
	$interval	- Cross browser setInterval code to pass variables
Classes:
	-
Events:
	-
Defines:
	-
-*----------------------------------------------------------------------------*/

#ifndef _CORE_TIMERS_INCLUDED
#define _CORE_TIMERS_INCLUDED true

/*----------------------------------------------------------------------------*-
Function:
	$timeout
Params:
	func - Code to call.
	delay - Delay to call code after.
	... - Parameters to pass.
Return:
	-
Notes:
	Wrapper for setTimeout to support passing parameters in IE.
-*----------------------------------------------------------------------------*/

var
	$timeout = function (func, delay)
{
	if (arguments.length > 2 && typeof func != 'string')
	{
		// Ideally detect which sort of setTimeout they have first, if FF's type just call directly
		var
			uq = '' + new Date().getTime() + (100 * Math.random());
		$timeout.pars[uq] = [];
		var
			p = $timeout.pars[uq],
			i = 2,
			l = 0,
			j = arguments.length,
			code = 'var p = $timeout.pars["' + uq + '"]; p[' + l + '](';
		p[l++] = func;
		while (i < j)
		{
			code += 'p[' + l + ']';
			p[l++] = arguments[i];
			if (++i < j)
			{
				code += ',';
			}
		}
		setTimeout(code + '); delete $timeout.pars["' + uq + '"];', delay);
	}
	else
	{
		setTimeout(func, delay);
	}
}

$timeout.pars = {};

/*----------------------------------------------------------------------------*-
Function:
	$interval
Params:
	func - Code to call.
	interval - Delay to call code after.
	... - Parameters to pass.
Return:
	-
Notes:
	Wrapper for setInterval to support passing parameters in IE.
-*----------------------------------------------------------------------------*/

var
	$interval = function (func, interval)
{
	if (arguments.length > 2 && typeof func != 'string')
	{
		// Ideally detect which sort of setTimeout they have first, if FF's type just call directly
		var
			uq = '' + new Date().getTime() + (100 * Math.random());
		$interval.pars[uq] = [];
		var
			p = $interval.pars[uq],
			i = 2,
			l = 0,
			j = arguments.length,
			code = 'var p = $interval.pars["' + uq + '"]; p[' + l + '](';
		p[l++] = func;
		while (i < j)
		{
			code += 'p[' + l + ']';
			p[l++] = arguments[i];
			if (++i < j)
			{
				code += ',';
			}
		}
		setInterval(code + '); delete $interval.pars["' + uq + '"];', interval);
	}
	else
	{
		setInterval(func, interval);
	}
}

$interval.pars = {};

// Test if we can pass variables with setTimeout
// HOPEFULLY this will be instant
setTimeout(function (a) { if (a) { $timeout = setTimeout; $interval = setInterval; } }, 0, true);

#endif
