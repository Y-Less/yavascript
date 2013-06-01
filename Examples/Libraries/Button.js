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
//  The Original Code is the yavascript development system - Button.js.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _BUTTON_INCLUDED
#define _BUTTON_INCLUDED true

#include 'Core/Events.js'
#include 'Core/Class.js'

#define BUTTON_WIDTH  (16)
#define BUTTON_HEIGHT (16)

var
	CButton =
	$class(
		// Constructor;
		function (offset, width, height, file)
		{
			if (typeof file == 'undefined')
			{
				file = 'images/buttons.png';
				width = BUTTON_WIDTH;
				height = BUTTON_HEIGHT;
			}
			var
				mainImage = new Image();
			mainImage.src = 'images/dot.gif';
			var
				s = mainImage.style;
			s.width = width + 'px';
			s.height = height + 'px';
			s.backgroundImage = 'url(' + file + ')';
			s.backroundPosition = -offset + 'px 0px';
			$event('onmousedown', mainImage, CButton.OnMouseDown);
			$event('onmouseup', mainImage, CButton.OnMouseUp);
			this.mImage = mainImage;
		},
		{
		// Methods
		GetImage :
			function ()
			{
				return this.mImage;
			}
		},
		{
		// Static methods
		OnMouseDown :
			function (event)
			{
			},
		OnMouseUp :
			function (event)
			{
			}
		});

#endif
