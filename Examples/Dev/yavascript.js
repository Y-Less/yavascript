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
//  The Original Code is the yavascript development system - yavascript.js.  
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

/*----------------------------------------------------------------------------*-
				   ============================
				    Yavascript Includes - Core
				   ============================
Description:
	This file defines the functions for using the yavascript pre-processor
	in a Javascript development context.
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

	The Original Code is yavascript.js.
Credits:
	Based on a concept by J.S. Cole
Version:
	0.1
Changelog:
	24/04/09:
		First version.
Functions:
	-
Classes:
	-
Events:
	-
Defines:
	-
-*----------------------------------------------------------------------------*/

(function ()
{
	var
		makeArray = "abc".split(/(b)/).length === 3 ?
			function (str)
			{
				// Every ECMAScript compliant browser
				return str.split(/^\s*#\s*(\w*)(.*)\s*$/mg);
			} :
			function (str)
			{
				// Non-compliant browsers (i.e. IE)
				// Need to split out the whole thing manually
				// Note: Fix the BUG, not the BROWSER
				// http://dev.opera.com/articles/view/a-browser-sniffing-warning-the-trouble/
				var
					a = [],
					l = 0,
					p,
					r = /^\s*#\s*(\w*)(.*)\s*$/m;
				while ((p = str.search(r)) != -1)
				{
					a[l++] = str.substr(0, p);
					str = str.substr(p).replace(r, function ($0, $1, $2)
						{
							a[l++] = $1;
							a[l++] = $2;
							return '';
						});
				}
				// Append the end
				a[l] = str;
				return a;
			};
	
	// Send a message somewhere
	var
		message = window['console'] ?
			// Got a console, excellent
			window['console'].log :
			document.getElementById('error') ?
				// Got an error div, OK I guess
				(function()
				{
					var
						id = document.getElementById('error');
					return function (msg)
						{
							// Message div if there is one
							id.innerHTML = msg + '<br />' + id.innerHTML;
						};
				})() :
				// Only got alert(), not good
				alert;
	
	// Get a file for inclusion
	function doInclude(url)
	{
		// Request a file from the server
		// Use a SYNCHRONOUS request,
		// development should always be
		// done locally anyway.
		var
			httpRequest;
		if (window.XMLHttpRequest)
		{
			// Mozilla, Safari, ...
			httpRequest = new XMLHttpRequest();
			if (httpRequest.overrideMimeType)
			{
				httpRequest.overrideMimeType('text/yavascript');
			}
		} 
		else if (window.ActiveXObject)
		{
			// IE
			try
			{
				httpRequest = new ActiveXObject("Msxml2.XMLHTTP");
			} 
			catch (e)
			{
				try
				{
					httpRequest = new ActiveXObject("Microsoft.XMLHTTP");
				}
				catch (e)
				{
					return '';
				}
			}
		}
		if (!httpRequest)
		{
			return '';
		}
		httpRequest.open('GET', url, false);
		httpRequest.send('');
		if (httpRequest.readyState == 4 && httpRequest.status == 200)
		{
			return doIncludes(httpRequest.responseText, url);
		}
		else
		{
			message('Could not open file "' + url + '"');
		}
		return '';
	}
	
	function doStripComments(code)
	{
		// Take out comments first, makes it easier to sort
		// out the other bits below. Yes, this line is complex
		// it removes comments from the source, ignoring
		// ones in strings. See:
		// http://www.perlmonks.org/?node=How%20do%20I%20use%20a%20regular%20expression%20to%20strip%20C%20style%20comments%20from%20a%20file%3F
		code = code.replace(/\/\*[^*]*\*+([^\/*][^*]*\*+)*\/|([^\/"']*("[^"\\]*(\\[\d\D][^"\\]*)*"[^\/"']*|'[^'\\]*(\\[\d\D][^'\\]*)*'[^\/"']*|\/+[^*\/][^\/"']*)*)/g, function ($0, $1, $2)
			{
				return ' ' + $2 ? $2 : '';
			});
		// This removes line comments
		code = code.replace(/\/\/(.*)|\/\*[^*]*\*+([^\/*][^*]*\*+)*\/|"(\\.|[^"\\])*"|'(\\.|[^'\\])*'|[^\/"']+/g, function ($0, $1)
			{
				return $1 ? '' : $0;
			});
		// We know there are no comments now,
		// so everything here should be valid.
		return code;
	}
	
	function doIncludes(code, path)
	{
		// Do inclusions
		// Parse all files into one
		// BEFORE doing things like defines
		code = doStripComments(code);
		path = path.replace(/(.*)\/.*/, '$1');
		if (path.length)
		{
			// A path - append a slash
			path += '/';
		}
		return code.replace(/^\s*#\s*include\s(.*)\s*$/gm, function ($0, $1)
			{
				// Strip old filename
				var
					np = path + eval($1),
					done;
				// Get the relative path
				do
				{
					done = false;
					// Resolve relative paths recursively
					np = np.replace(/[^\/]+\/\.\.\//g, function ()
						{
							done = true;
							return '';
						});
				}
				while (done);
				return doInclude(np);
			});
	}
	
	function doMacroReplaces(code)
	{
		var
			d = doMacroReplaces.defs,
			loop;
		do
		{
			loop = false;
			// Do all current possible replacements
			for (var k in d)
			{
				// It doesn't like me defining the
				// regex as the array key
				code = code.replace(new RegExp(k, 'mg'), function ($0, $1, $2)
					{
						loop = true;
						return $1 + d[k] + $2;
					});
			}
		}
		while (loop)
		return code;
	}
	doMacroReplaces.defs = {};
	
	function makeName(name)
	{
		// Strip whitespace from the start
		// and end, then apply the regex bits
		return '(^|\\W)' + name.replace(/(^\s*)|(\s*$)/g, '') + '(\\W|$)';
	}
	
	// Parse a chunk of text as
	// yavascript code.
	function doYavascript(code, src)
	{
		code = doIncludes(code, src);
		// Split the code into sections
		// The sections are in the order
		// code-directive-parameters
		var
			parts = [],
			execute = true,
			es = [],
			descent = 0,
			temp = 0,
			d = doMacroReplaces.defs;
		parts = makeArray(code);
		code = '';
		// Collect all the pre-processor
		// macros together IN ORDER
		for (var i = 0, j = parts.length; i < j; ++i)
		{
			temp = parts[i];
			//message('parts[' + i + ']: ' + temp);
			if (temp)
			{
				if (i % 3)
				{
					// Get parameters
					++i;
					if (execute)
					{
						// In a true #if block
						switch (temp)
						{
							case 'define':
								// Add this macro to the list
								if (i < j && parts[i])
								{
									var
										entry = parts[i].match(/^\s+(\w+)\s+(.+)/m);
									if (entry)
									{
										// Create the regex to find this
										// complete word only.
										temp = makeName(entry[1]);
										if (d[temp])
										{
											message('Macro redefinition: ' + entry[1]);
										}
										// Save the define as the replacement
										// pattern for the search regex.
										d[temp] = entry[2];
									}
									else
									{
										message('Invalid define: \"#define ' + parts[i] + '\"');
									}
								}
								else
								{
									message('Missing #define parameters');
								}
								break;
							case 'undef':
								// Remove this macro from the list
								if (i < j && parts[i])
								{
									temp = makeName(parts[i]);
									if (d[temp])
									{
										delete d[temp];
									}
									else
									{
										message('Undefined macro: ' + parts[i]);
									}
								}
								else
								{
									message('Missing #undef parameter');
								}
								break;
							case 'if':
								++descent;
								if (i < j && parts[i])
								{
									// First, replace all the macros
									try
									{
										if (!eval(doMacroReplaces(parts[i])))
										{
											// #if failed
											execute = false;
										}
									}
									catch (e)
									{
										message('Invalid #if expression: ' + parts[i]);
										execute = false;
									}
								}
								else
								{
									message('Missing #if expression');
									execute = false;
								}
								es[es.length] = true;
								break;
							case 'ifdef':
								++descent;
								if (i < j && parts[i])
								{
									// Get the macro internal name
									//var
									//	name = '(^|\\W)' + parts[i].replace(/(^\s*)|(\s*$)/g, '') + '(\\W|$)';
									if (!d[makeName(parts[i])])
									{
										// Not defined
										execute = false;
									}
								}
								else
								{
									message('Missing #ifdef expression');
									execute = false;
								}
								es[es.length] = true;
								break;
							case 'ifndef':
								++descent;
								if (i < j && parts[i])
								{
									// Get the macro internal name
									//var
									//	name = '(^|\\W)' + parts[i].replace(/(^\s*)|(\s*$)/g, '') + '(\\W|$)';
									if (d[makeName(parts[i])])
									{
										// Not not defined
										execute = false;
									}
								}
								else
								{
									message('Missing #ifndef expression');
									execute = false;
								}
								es[es.length] = true;
								break;
							case 'else':
								// Don't run the code in here
								if (descent)
								{
									execute = false;
								}
								else
								{
									message('Unmatched #else');
								}
								break;
							case 'endif':
								if (descent)
								{
									es.pop();
									--descent;
								}
								else
								{
									message('Unmatched #endif');
								}
								break;
							case 'pragma':
								// Do nothing in JS mode
								break;
							default:
								message('Unknown directive: ' + temp);
								break;
						}
					}
					else
					{
						// Don't do anything - in a
						// series of false conditionals
						switch (temp)
						{
							case 'define':
							case 'undef':
							case 'pragma':
								// Do nothing
								break;
							case 'if':
							case 'ifdef':
							case 'ifndef':
								// #if in a #if
								es[es.length] = false;
								++descent;
								break;
							case 'else':
								// Alter the current execution
								// But don't exit the current block
								// Run the code in here
								execute = es[es.length - 1];
								break;
							case 'endif':
								--descent;
								execute = es.pop();
								break;
							default:
								message('Unknown directive: ' + temp);
								break;
						}
					}
				}
				else
				{
					if (execute)
					{
						code += doMacroReplaces(temp);
					}
					// Else it's in a false #if
				}
			}
		}
		if (descent > 0)
		{
			message('Unmatched #if');
		}
		return code;
	}
	
	// Loop through HTML script tags
	var
		scripts = document.getElementsByTagName('script');
	for (var i in scripts)
	{
		// Found a yavascript tag
		var
			s = scripts[i];
		if (s.type == 'text/yavascript')
		{
			if (s.src)
			{
				eval(doYavascript(doInclude(s.src), s.src));
			}
			else
			{
				// Do the code
				eval(doYavascript(s.innerHTML, ''));
			}
		}
	}
})();
