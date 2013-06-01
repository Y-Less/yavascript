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
//  The Original Code is the yavascript development system - Utils.js.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _UTILS_INCLUDED
#define _UTILS_INCLUDED true

#include 'Core/Class.js'

var
	CUtils =
	$class(
		null,
		null,
		{
		GetElementPos :
			function (element)
			{
				var
					left = 0,
					top = 0;
				do
				{
					left += element.offsetLeft;
					top += element.offsetTop;
					element = element.offsetParent;
				}
				while (element);
				return {x : left, y : top};
			},
		GetElementSize :
			function (element)
			{
				if (typeof element.offsetWidth == 'undefined')
				{
					return {x : element.style.pixelWidth, y : element.style.pixelHeight};
				}
				else
				{
					return {x : element.offsetWidth, y : element.offsetHeight};
				}
			},
		ToHex :
			function (num, pad)
			{
				var
					ret = '';
				do
				{
					ret = CUtils.HEX.substr(num & 15, 1) + ret;
					num >>= 4;
				}
				while (num > 0);
				if (pad)
				{
					while (ret.length < pad)
					{
						ret = '0' + ret;
					}
				}
				return ret;
			},
		GetMousePos :
			function (event)
			{
				if (typeof event.pageX != 'undefined')
				{
					// Firefox
					return {x : event.pageX, y : event.pageY};
				}
				if (event.clientX)
				{
					// IE
					return {x : event.clientX + document.body.scrollLeft - document.body.clientLeft, y : event.clientY + document.body.scrollTop - document.body.clientTop};
				}
				return {x : 0, y : 0};
			},
		GetElement :
			function (element)
			{
				var
					type = typeof element;
				if (type == 'undefined')
				{
					return null;
				}
				if (type == 'string')
				{
					return $(element);
				}
				if (type == 'function')
				{
					return element();
				}
				return element;
			},
		GetScrollPos :
			function ()
			{
				return {x : (document.all) ? document.body.scrollLeft : window.pageXOffset, y : (document.all) ? document.body.scrollTop : window.pageYOffset};
			},
		GetScreenSize :
			function ()
			{
				return {x : screen.width, y : screen.height};
			},
		/*
			Developed by Robert Nyman, http://www.robertnyman.com
			Code/licensing: http://code.google.com/p/getelementsbyclassname/
			Swapped tag and elm around to provide better 2-parameter support
		*/
		GetElementsByClassName :
			function (className, elm, tag)
			{
				if (document.getElementsByClassName)
				{
					CUtils.GetElementsByClassName = function (className, elm, tag)
					{
						elm = elm || document;
						var
							elements = elm.getElementsByClassName(className),
							nodeName = (tag) ? new RegExp("\\b" + tag + "\\b", "i") : null,
							returnElements = [],
							current;
						for (var i = 0, il = elements.length; i < il; i += 1)
						{
							current = elements[i];
							if (!nodeName || nodeName.test(current.nodeName))
							{
								returnElements.push(current);
							}
						}
						return returnElements;
					};
				}
				else if (document.evaluate)
				{
					CUtils.GetElementsByClassName = function (className, elm, tag)
					{
						tag = tag || "*";
						elm = elm || document;
						var
							classes = className.split(" "),
							classesToCheck = "",
							xhtmlNamespace = "http://www.w3.org/1999/xhtml",
							namespaceResolver = (document.documentElement.namespaceURI === xhtmlNamespace) ? xhtmlNamespace : null,
							returnElements = [],
							elements,
							node;
						for (var j = 0, jl = classes.length; j < jl; j += 1)
						{
							classesToCheck += "[contains(concat(' ', @class, ' '), ' " + classes[j] + " ')]";
						}
						try
						{
							elements = document.evaluate(".//" + tag + classesToCheck, elm, namespaceResolver, 0, null);
						}
						catch (e)
						{
							elements = document.evaluate(".//" + tag + classesToCheck, elm, null, 0, null);
						}
						while ((node = elements.iterateNext()))
						{
							returnElements.push(node);
						}
						return returnElements;
					};
				}
				else
				{
					CUtils.GetElementsByClassName = function (className, elm, tag)
					{
						tag = tag || "*";
						elm = elm || document;
						var
							classes = className.split(" "),
							classesToCheck = [],
							elements = (tag === "*" && elm.all) ? elm.all : elm.getElementsByTagName(tag),
							current,
							returnElements = [],
							match;
						for (var k = 0, kl = classes.length; k < kl; k += 1)
						{
							classesToCheck.push(new RegExp("(^|\\s)" + classes[k] + "(\\s|$)"));
						}
						for (var l = 0, ll = elements.length; l < ll; l += 1)
						{
							current = elements[l];
							match = false;
							for (var m = 0, ml = classesToCheck.length; m < ml; m += 1)
							{
								match = classesToCheck[m].test(current.className);
								if (!match)
								{
									break;
								}
							}
							if (match)
							{
								returnElements.push(current);
							}
						}
						return returnElements;
					};
				}
				return CUtils.GetElementsByClassName(className, elm, tag);
			},
		MAX : 2147483647,
		MIN : -2147483648,
		HEX : '0123456789ABCDEF'
		}
	);

#endif
