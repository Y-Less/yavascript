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
//  The Original Code is the yavascript development system - Events.js.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

/*----------------------------------------------------------------------------*-
				   =======================================
				    Yavascript Includes - Event Functions
				   =======================================
Description:
	Defines a set of cross-browser compatible event functions.
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

	The Original Code is Events.js.
Credits:
	Based on a concept by J.S. Cole
Version:
	0.1
Changelog:
	17/08/08:
		First version.
Functions:
	$event		- Adds a cross-browser compatible event handler
	$event.add	- Alias for $event
	$event._addEventListener - $event code for some browsers.
	$event._eventHandler - $event code for other browsers.
	$event.remove	- Removes an event handler
Classes:
	-
Events:
	-
Defines:
	-
-*----------------------------------------------------------------------------*/

#ifndef _CORE_EVENTS_INCLUDED
#define _CORE_EVENTS_INCLUDED true

/*----------------------------------------------------------------------------*-
Function:
	$event, $event.add
Params:
	domEvent - Name of the event to attach to.
	source (optional) - Element to attach to, default 'document'.
	func - Function to call on the event.
Return:
	-
Notes:
	Attach a function to an event in a cross-browser way.  Overrides the IE
	thing of passing 'this' as the window object instead of the object that
	fired the event.  Unfortunately this breaks removeEvent.
-*----------------------------------------------------------------------------*/

var
	$event = function (domEvent, source, func)
{
	/* if (window.addEventListener)
	{
		$event = $event._addEventListener;
	}
	else
	{ */
		/*if (window.attachEvent)
		{
		}
		else
		{*/
			$event = $event._eventHandler;
		/*}*/
	/* }
	$event.add = $event; */
	return $event(domEvent, source, func);
}

$event.add = $event;

/*----------------------------------------------------------------------------*-
Function:
	$event._eventHandler
Params:
	domEvent - Name of the event to attach to.
	source (optional) - Element to attach to, default 'document'.
	func - Function to call on the event.
Return:
	-
Notes:
	$event implementation in browsers with no addEventListener.  Detects if an
	event has already been manually applied to an element using HTML based
	listeners (i.e. onevent='code') and preserves them, calling them first as
	with addEventListener.
-*----------------------------------------------------------------------------*/

$event._eventHandler = function (domEvent, source, func)
{
	if (!func)
	{
		if (!source)
		{
			return;
		}
		func = source;
		source = document;
	}
	// Check if an event has been applied to this already
	domEvent = domEvent.substring(0, 2) == 'on' ? domEvent : 'on' + domEvent;
	var
		ev = source[domEvent];
	if (ev)
	{
		// Already has something registered
		if (!ev._has$event)
		{
			// Has a function, but not one of ours
			var
				old = ev;
			ev = function (event)
			{
				event = event || window.event;
				var
					c = ev._calls,
					i = -1,
					j = c.length,
					oldStop = event.stopPropagation,
					ret = false;
				event.cancelBubble = false;
				event.stopPropagation = function ()
				{
					event.cancelBubble = true;
				}
				if (old.call(this, event))
				{
					ret = true;
				}
				while (++i < j)
				{
					if (c[i])
					{
						if (c[i].call(this, event))
						{
							ret = true;
						}
					}
				}
				if (oldStop && event.cancelBubble)
				{
					oldStop();
				}
				return ret;
			}
			ev._calls = [];
		}
	}
	else
	{
		// Nothing registered
		ev = function (event)
		{
			event = event || window.event;
			var
				c = ev._calls,
				i = -1,
				j = c.length,
				oldStop = event.stopPropagation,
				ret = false;
			event.cancelBubble = false;
			event.stopPropagation = function ()
			{
				event.cancelBubble = true;
			}
			while (++i < j)
			{
				if (c[i])
				{
					if (c[i].call(this, event))
					{
						ret = true;
					}
				}
			}
			if (oldStop && event.cancelBubble)
			{
				oldStop();
			}
			return ret;
		}
		ev._calls = [];
	}
	ev._calls[ev._calls.length] = func;
	ev._has$event = true;
	source[domEvent] = ev;
}

/*----------------------------------------------------------------------------*-
Function:
	$event._addEventListener
Params:
	domEvent - Name of the event to attach to.
	source (optional) - Element to attach to, default 'document'.
	func - Function to call on the event.
Return:
	-
Notes:
	$event implementation in browsers with addEventListener.
-*----------------------------------------------------------------------------*/

$event._addEventListener = function (domEvent, source, func)
{
	if (!func)
	{
		if (!source)
		{
			return;
		}
		func = source;
		source = document;
	}
	var
		nf;
	if (!func._$_event_$_handler_$_)
	{
		func._$_event_$_handler_$_ = [];
	}
	if (!func._$_event_$_handler_$_[domEvent])
	{
		// Create an annonymous function to correctly pass the variables
		nf = function (event)
		{
			event = event || window.event;
			/*var
				oldStop = event.stopPropagation;
			event.cancelBubble = false;
			event.stopPropagation = function ()
			{
				event.cancelBubble = true;
			};*/
			var
				ret = func.call(source, event);
			/*if (oldStop && event.cancelBubble)
			{
				oldStop();
			}*/
			if (!ret)
			{
				// Add handling for returning false
				if (event.preventDefault)
				{
					event.preventDefault();
				}
				else
				{
					event.returnValue = false;
				}
				return false;
			}
			return true;
		}
		func._$_event_$_handler_$_[domEvent] = nf;
	}
	else
	{
		nf = func._$_event_$_handler_$_[domEvent];
	}
	// Strip 'on'
	domEvent = domEvent.substring(0, 2) == 'on' ? domEvent.substring(2) : domEvent;
	source.addEventListener(domEvent, nf, false);
}

/*----------------------------------------------------------------------------*-
Function:
	$event.remove
Params:
	domEvent - Name of the event to attach to.
	func - Function to call on the event.
	source - Element to attach to.
Return:
	-
Notes:
	Remove the given listener.
-*----------------------------------------------------------------------------*/

$event.remove = function (domEvent, source, func)
{
	if (!func)
	{
		func = source;
		source = document;
	}
	if (!source.removeEventListener)
	{
		source.removeEventListener = function (type, listener, useCapture)
		{
			type = 'on' + type;
			// Old, use custom code
			var
				old = source[type];
			// Chain the function calls so we can have more than one
			if (old)
			{
				if (old._first == listener)
				{
					old._first = null;
					return;
				}
				else
				{
					var
						list = old._calls;
					if (list)
					{
						var
							i = -1,
							j = list.length;
						while (++i < j)
						{
							if (list[i].func == listener)
							{
								list[i] = null;
								return;
							}
						}
					}
				}
			}
		}
	}
	domEvent = domEvent.substring(0, 2) == 'on' ? domEvent.substring(2) : domEvent;
	source.removeEventListener(domEvent, func._$_event_$_handler_$_[domEvent], false);
}

#endif
