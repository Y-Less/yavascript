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
//  The Original Code is the yavascript development system - DragRestrict.js.
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _DRAGRESTRICT_INCLUDED
#define _DRAGRESTRICT_INCLUDED true

#include 'Core/Class.js'

#include 'Dragable.js'
#include 'Utils.js'

var
	CDragRestrict =
	$class.extend(CDragable,
		null,
		{
		SetArea :
			function (minx, miny, maxx, maxy)
			{
				this.mMinX = minx;
				this.mMinY = miny;
				this.mMaxX = maxx;
				this.mMaxY = maxy;
			},
		Move:
			function (dX, dY)
			{
				// Use the supposed "real" location, not the actual one
				this.SetPos(this.mRX + dX, this.mRY + dY);
			},
		SetPos :
			function (x, y)
			{
				// Save where it should be
				this.mRX = x;
				this.mRY = y;
				// Adjust for boundaries
				if (x < this.mMinX)
				{
					x = this.mMinX;
				}
				if (y < this.mMinY)
				{
					y = this.mMinY;
				}
				if (x >= this.mMaxX)
				{
					x = this.mMaxX;
				}
				if (y >= this.mMaxY)
				{
					y = this.mMaxY;
				}
				// Call the super method to really set the location
				CDragable.prototype.SetPos.call(this, x, y);
			},
		mMinX : 0,
		mMinY : 0,
		mMaxX : CUtils.MAX,
		mMaxY : CUtils.MAX,
		mRX : 0,
		mRY : 0
		},
		null);

#endif