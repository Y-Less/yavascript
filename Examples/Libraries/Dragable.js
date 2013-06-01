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
//  The Original Code is the yavascript development system - Dragable.js.    
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _DRAGABLE_INCLUDED
#define _DRAGABLE_INCLUDED true

#include 'Core/Events.js'
#include 'Core/Class.js'

#include 'Utils.js'

// CDragable abstract class
var
	CDragable =
	$class(
		// Constructor
		function (dragHandle, movableItem)
		{
			dragHandle = CUtils.GetElement(dragHandle);
			movableItem = CUtils.GetElement(movableItem);
			if (dragHandle)
			{
				// Check wether the drag movable item exists
				// If not make the thing that moves the thing you drag
				if (movableItem)
				{
					this.SetElements(dragHandle, movableItem);
				}
				else
				{
					this.SetElements(dragHandle, dragHandle);
				}
			}
		},
		{
		// Methods
		SetElements :
			function (dragHandle, movableItem)
			{
				dragHandle.oParent = this;
				movableItem.style.position = 'relative';
				$event('onmousedown', dragHandle, CDragable.OnMouseDown);
				this.eElement = dragHandle;
				this.eMovable = movableItem;
				this.UpdatePos();
			},
		OnDragStart :
			function (x, y)
			{
				this.mX = x;
				this.mY = y;
				if (this.OnStart)
				{
					this.OnStart();
				}
			},
		OnDragStop :
			function ()
			{
				// Do nothing, optional extendable method
				if (this.OnStop)
				{
					this.OnStop();
				}
			},
		OnDragMove :
			function (x, y)
			{
				this.Move(x - this.mX, y - this.mY);
				this.mX = x;
				this.mY = y;
			},
		Move :
			function (dX, dY)
			{
				// Don't pass the real position as there will be an offset
				this.SetPos(this.mEX + dX, this.mEY + dY);
			},
		SetPos :
			function (x, y)
			{
				var
					s = this.eMovable.style,
					dx = x - this.mEX,
					dy = y - this.mEY;
				this.mEX = x;
				this.mEY = y;
				s.left = x + 'px';
				s.top = y + 'px';
				if (this.OnMove)
				{
					this.OnMove(dx, dy);
				}
			},
		SetPosAbs :
			function (x, y)
			{
				var
					rpos = CUtils.GetElementPos(this.eMovable);
				this.Move(x - rpos.x, y - rpos.y);
			},
		GetPos :
			function ()
			{
				return {x : this.mEX, y : this.mEY};
			},
		UpdatePos :
			function ()
			{
				var
					pos = CUtils.GetElementPos(this.eMovable),
					t = this.OnMove;
				this.OnMove = null;
				// This will result in a move of 0 but that's the whole point;
				// we use a method call, not a direct set here to allow
				// subclasses to work
				this.SetPosAbs(pos.x, pos.y);
				this.OnMove = t;
			},
		// Instance members
		mX : 0,
		mY : 0,
		mEX : 0,
		mEY : 0,
		mScroll : true
		},
		{
		// Static methods
		OnMouseDown :
			function (event)
			{
				var
					pos = CUtils.GetMousePos(event),
					d = CDragable.msDrag;
				if (d)
				{
					d.OnDragStop();
				}
				d = this.oParent;
				if (d.mScroll)
				{
					d.OnDragStart(pos.x, pos.y);
				}
				else
				{
					d = null;
				}
				CDragable.msDrag = d;
				//event.stopPropagation();
				//event.cancelBubble = true;
				return false;
			},
		OnMouseUp :
			function (event)
			{
				if (CDragable.msDrag)
				{
					CDragable.msDrag.OnDragStop();
					CDragable.msDrag = null;
				}
				//event.stopPropagation();
				return false;
			},
		OnMouseMove :
			function (event)
			{
				if (CDragable.msDrag)
				{
					var
						pos = CUtils.GetMousePos(event);
					CDragable.msDrag.OnDragMove(pos.x, pos.y);
					return false;
				}
				return true;
			},
		// Global current item handle
		msDrag : null
		});

$event('onmouseup', CDragable.OnMouseUp);

$event('onmousemove', CDragable.OnMouseMove);

#endif
