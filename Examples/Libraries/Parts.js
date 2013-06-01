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
//  The Original Code is the yavascript development system - Parts.js.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _PARTS_INCLUDED
#define _PARTS_INCLUDED true

#include 'Core/Events.js'
#include 'Core/Class.js'

#include 'Utils.js'

/*

Contains generic functions for creating UI elements too small to warrant their own classes

Basically a load of helper functions

*/

var
	CParts = 
	$class(
		null,
		null,
		{
		MakeIcon :
			function (file, width, height, offset, func)
			{
				/*
				2 parameters - offset and function, assume standard icon library
				3 parameters - file, width and function, offset 0, height = width
				4 parameters - file, width, height and function, offset = 0
				5 parameters - file, width, height, offset and function
				
				file - File with the icon image in
				width - Width of the icon image
				height - Height of the icon image
				offset - A single file can have multiple icons for bandwidth reasons, this is the location in the image
				function - What to do when the icon is clicked
				*/
				if (typeof func == 'undefined')
				{
					if (typeof offset == 'undefined')
					{
						if (typeof height == 'undefined')
						{
							func = width;
							offset = -file;
							width = 16;
							file = 'Images/buttons.png';
						}
						else
						{
							func = height;
							offset = 0;
						}
						height = width;
					}
					else
					{
						func = offset;
						offset = 0;
					}
				}
				else
				{
					offset = -offset;
				}
				var
					ret = new Image(),
					s = ret.style;
				ret.src = 'Images/dot.gif';
				s.width = width + 'px';
				s.height = height + 'px';
				s.backgroundImage = 'url(' + file + ')';
				s.backgroundPosition = offset + 'px 0px';
				height = -height;
				var
					onicon = 0;
				$event('onmousedown', ret, function (event)
					{
						s.backgroundPosition = offset + 'px ' + height + 'px';
						onicon = 1;
						CParts.msAllUp = 1;
						event.stopPropagation();
					});
				$event('onmouseup', ret, function (event)
					{
						if (onicon == 1)
						{
							func();
							s.backgroundPosition = offset + 'px 0px';
							event.stopPropagation();
						}
						onicon = 0;
					});
				$event('onmouseout', ret, function ()
					{
						if (onicon == 1)
						{
							s.backgroundPosition = offset + 'px 0px';
							onicon = 2;
						}
					});
				$event('onmouseover', ret, function ()
					{
						if (!CParts.msAllUp)
						{
							onicon = 0;
						}
						if (onicon == 2)
						{
							onicon = 1;
							s.backgroundPosition = offset + 'px ' + height + 'px';
						}
					});
				return ret;
			},
		msAllUp : 0
		});

$event('onmouseup', function () { CParts.msAllUp = 0; });

#endif
