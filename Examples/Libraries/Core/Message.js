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
//  The Original Code is the yavascript development system - Message.js.     
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

/*----------------------------------------------------------------------------*-
				   =========================================
				    Yavascript Includes - Message Functions
				   =========================================
Description:
	Defines a set of functions for sending messages.
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

	The Original Code is Message.js.
Credits:
	Based on a concept by J.S. Cole
Version:
	0.1
Changelog:
	17/08/08:
		First version.
Functions:
	$error		- Display an error message
	$warning	- Display a warning message
	$debug		- Display a debug message
	$info		- Display an information message
	$_info		- Internal message function
Classes:
	-
Events:
	-
Defines:
	-
-*----------------------------------------------------------------------------*/

#ifndef _CORE_MESSAGE_INCLUDED
#define _CORE_MESSAGE_INCLUDED true

#ifndef YAVASCRIPT_DEBUG_LEVEL
	#define YAVASCRIPT_DEBUG_LEVEL 5
#endif

/*----------------------------------------------------------------------------*-
Function:
	$_info
Params:
	message - Info message to display.
	level (optional) - Global message level at which to display the info.
Return:
	-
Notes:
	Handles all messages and outputs them to the console.
-*----------------------------------------------------------------------------*/

#if YAVASCRIPT_DEBUG_LEVEL > 0

// Want debugging
var
	$_info = function ()
		{
			var
				C = window['console'];
			if (C)
			{
				return function (msg, level)
					{
						// Ensure level is initialised
						level = level || 0;
						// Check if the level is wanted
						if (YAVASCRIPT_DEBUG_LEVEL >= level)
						{
							// Display the message
							C(msg);
						}
					};
			}
			else
			{
				return function (msg, level)
					{
						// Ensure level is initialised
						level = level || 0;
						// Check if the level is wanted
						if (YAVASCRIPT_DEBUG_LEVEL >= level)
						{
							// Display the message
							alert(msg);
						}
					};
			}
		}();

#else

// Don't want debugging - do nothing
function $_info() {}

#endif

/*----------------------------------------------------------------------------*-
Function:
	$error
Params:
	error - Error message to display.
	level (optional) - Global message level at which to display the error.
Return:
	-
Notes:
	Appends 'Error: ' to a message - see $_info.
-*----------------------------------------------------------------------------*/

function $error(error, level)
{
	if (!level || YAVASCRIPT_DEBUG_LEVEL >= level)
	{
		$_info('Error: ' + error, level);
		alert('Error: ' + error);
	}
}

/*----------------------------------------------------------------------------*-
Function:
	$warning
Params:
	error - Warning message to display.
	level (optional) - Global message level at which to display the warning.
Return:
	-
Notes:
	Appends 'Warning: ' to a message - see $_info.
-*----------------------------------------------------------------------------*/

function $warning(warning, level)
{
	if (!level || YAVASCRIPT_DEBUG_LEVEL >= level)
	{
		$_info('Warning: ' + warning, level);
		alert('Warning: ' + warning);
	}
}

/*----------------------------------------------------------------------------*-
Function:
	$debug
Params:
	debug - Debug message to display.
	level (optional) - Global message level at which to display the debug.
Return:
	-
Notes:
	Appends 'Debug: ' to a message - see $_info.
-*----------------------------------------------------------------------------*/

function $debug(debug, level)
{
	$_info('Debug: ' + debug, level);
}

/*----------------------------------------------------------------------------*-
Function:
	$info
Params:
	info - Info message to display.
	level (optional) - Global message level at which to display the info.
Return:
	-
Notes:
	Appends 'Info: ' to a message - see $_info.
-*----------------------------------------------------------------------------*/

function $info(info, level)
{
	$_info('Info: ' + info, level);
}

#endif
