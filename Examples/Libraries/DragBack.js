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
//  The Original Code is the yavascript development system - DragBack.js.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _DRAGBACK_INCLUDED
#define _DRAGBACK_INCLUDED true

#include 'Core/Class.js'

#include 'Dragable.js'

var
	CDragBack =
	$class.extend(CDragable,
		null,
		{
		SetPos :
			function (x, y)
			{
				var
					pos = x + 'px ' + y + 'px';
				this.mEX = x;
				this.mEY = y;
				this.eMovable.style.backgroundPosition = pos;
			},
		SetElements :
			function (dragHandle, movableItem)
			{
				// Disable the annoying image toolbar in IE as this image is designed to be mouse-overed
				movableItem.galleryimg = 'no';
				CDragable.prototype.SetElements.call(this, dragHandle, movableItem);
			}
		},
		null);

#endif
