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
//  The Original Code is the yavascript development system - Class.js.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

/*----------------------------------------------------------------------------*-
				   =======================================
				    Yavascript Includes - Class Functions
				   =======================================
Description:
	Generic functions for using classes in code development.
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

	The Original Code is Class.js.
Credits:
	Based on a concept by J.S. Cole
Version:
	0.1
Changelog:
	17/08/08:
		First version.
Functions:
	$class			- Quickly and efficiently define a new class
	$class.extend	- Defines a new class based on an old class
	$class.isA		- Internal class.$isA function
Classes:
	-
Events:
	-
Defines:
	-
-*----------------------------------------------------------------------------*/

#ifndef _CORE_CLASS_INCLUDED
#define _CORE_CLASS_INCLUDED true

#include 'Message.js'

/*----------------------------------------------------------------------------*-
Function:
	$class
Params:
	constructor - The new class's constructor.
	properties - Instance properties and class methods.
	statics - Class properties.
Return:
	The new class.
Notes:
	This function gives a concise and simple method for defining classes
	without the need for all the prototype stuff.  The class defined is
	entirely stand-alone (i.e. doesn't inherit from another class).
-*----------------------------------------------------------------------------*/

var
	$class = function (constructor, properties, statics)
{
	// Check if the constructor exists
	if (!constructor)
	{
		constructor = new Function();
	}
	var
		prot = constructor.prototype;
	// Add all instance items to the class
	if (properties)
	{
		for (var i in properties)
		{
			prot[i] = properties[i];
		}
	}
	// All all class items to the class
	if (statics)
	{
		for (var i in statics)
		{
			constructor[i] = statics[i];
		}
	}
	prot.constructor = constructor;
	// Define $base at object and instance level
	prot.$base = null;
	constructor.$base = null;
	// Define $isA at object and instance level
	prot.$isA = $class.isA;
	constructor.$isA = $class.isA;
	return constructor;
}

/*----------------------------------------------------------------------------*-
Function:
	$class.sextend
Params:
	parent - The class on which to base this class.
	constructor - The new class's constructor.
	properties - Instance properties and class methods.
	statics - Class properties.
Return:
	The new class.
Notes:
	This function gives a concise and simple method for defining classes
	without the need for all the prototype stuff.  The class defined extends an
	existing class, i.e. it inherits the methods and members of another class.
-*----------------------------------------------------------------------------*/

$class.extend = function () //parent, constructor, properties, statics)
{
	var
		code = arguments.length - 3,
		oldProt;
	if (code < 1)
	{
		$error('Must include at least one parent class.');
		return null;
	}
	// arguments[0] is the main parent
	// The others are fake parents, i.e. their methods will get copied but not update with new ones
	// Also, I don't know how it will deal will multiple inheritance of classes with parents of their own
	if (code == 1)
	{
		// Single inheritance - easy as it's natively supported
		var
			parent = arguments[0],
			constructor = arguments[1];
		if (constructor == null)
		{
			// No constructor given, call the parent correctly
			// Annoyingly there's no easy way to pass all passed parameters
			constructor = function ()
				{
					var
						pars = '';
					for (var i = 0, j = arguments.length; i < j; i++)
					{
						pars += ', arguments[' + i + ']';
					}
					eval('parent.prototype.constructor.call(this' + pars + ');');
				};
		}
		oldProt = constructor.prototype;
		var
			prot;
		constructor.prototype = prot = new parent();
		for (var i in oldProt)
		{
			prot[i] = oldProt[i];
		}
		// We've set up the inheritance, set up the local stuff
		constructor = $class(constructor, arguments[2], arguments[3]);
		// Save the base for instances and the class
		prot.$base = parent.prototype;
		constructor.$base = parent;
		return constructor;
	}
	else
	{
		// Multiple inheritance
		var
			constructor = arguments[code],
			parent = [];
		// arguments isn't a real array so we need to do this by hand
		for (var i = 0; i < code; i++)
		{
			parent[i] = arguments[i];
		}
		if (constructor == null)
		{
			// No constructor, generate one which calls each constructor in turn
			// Because we don't know what parameters will be passed, we need to relay them all, which is awkward
			constructor = function ()
				{
					var
						pars = 'parent[i].prototype.constructor.call(this';
					for (var i = 0, j = arguments.length; i < j; i++)
					{
						pars += ', arguments[' + i + ']';
					}
					// This is done differently to the single parent method to avoid multiple concatenations
					pars += ');';
					for (var i in parent)
					{
						eval(pars);
					}
				};
		}
		oldProt = constructor.prototype;
		var
			k = code - 1;
		for (var i = 0; i < k; i++)
		{
			constructor.prototype = new parent[i]();
			var
				cp = constructor.prototype;
			//cp.constructor = constructor;
			for (var j in cp)
			{
				oldProt[j] = cp[j];
			}
		}
		constructor.prototype = new parent[k]();
		k = constructor.prototype;
		// Make this the most important class
		for (var i in oldProt)
		{
			if (typeof k[i] == 'undefined')
			{
				k[i] = oldProt[i];
			}
		}
		k.constructor = constructor;
		// We've set up the inheritance, set up the local stuff
		constructor = $class(constructor, arguments[code + 1], arguments[code + 2]);
		// Save the base for instances and the class
		constructor.prototype.$base = parent.prototype;
		constructor.$base = parent;
		return constructor;
	}
}

/*----------------------------------------------------------------------------*-
Function:
	$class.isA
Params:
	compare - Class to check against.
Return:
	-
Notes:
	Checks if a class or class instance is desended from a given class.
-*----------------------------------------------------------------------------*/

$class.isA = function (compare)
{
	var
		base = this;
	while (base)
	{
		if (base == compare)
		{
			return true;
		}
		base = base.$base;
	}
	return false;
}

#endif
