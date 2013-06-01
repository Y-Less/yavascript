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
//  The Original Code is the yavascript development system - Window.js.      
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

#ifndef _WINDOW_INCLUDED
#define _WINDOW_INCLUDED true

#include 'Core/Class.js'
#include 'Core/Events.js'

#include 'Dragable.js'
#include 'Parts.js'
#include 'Utils.js'

/*
All windows are contained in a div with a class of "ysi_window_outer_XXX", however this is auto-generated.  XXX is either "min" or "max" depending on wether the window is minimised or maximised
This means you can do things like:

			.ysi_window_outer_min .ysi_window_inner
			{
				border-bottom:		medium solid #C0C0C0;
				border-right:		medium solid #C0C0C0;
				border-left:		medium solid #C0C0C0;
			}
			
			.ysi_window_outer_max .ysi_window_inner
			{
				border-bottom:		medium solid #FF0000;
				border-right:		medium solid #FF0000;
				border-left:		medium solid #FF0000;
			}
			
			.ysi_window_inner
			{
				-moz-box-sizing:	border-box;
				box-sizing:			border-box;
				z-index:			1;
			}

Which will alter the borders of the main content depending on wether the window is minimise or maximised
*/

#define WINDOW_HTML '<div class="ysi_window_container"><div class="ysi_window_fit"><div class="ysi_window_content"><div class="ysi_window_inner"></div></div><div class="ysi_window_bar"><div class="ysi_window_icons"></div></div></div></div>';

var
	CWindow =
	$class.extend(CDragable,
		// Constructor
		function (title, dragHandle)
		{
			if (typeof dragHandle == 'undefined')
			{
				this.windowTitle = '';
				CDragable.prototype.constructor.call(this, title, title);
			}
			else
			{
				this.windowTitle = title;
				CDragable.prototype.constructor.call(this, dragHandle, dragHandle);
			}
		},
		{
		// Methods
		SetElements :
			function (dragHandle_IGNORE_, movableItem)
			{
				// We are making a standard window so we don't want to use the given drag handle - we want to make our own
				// However the given drag handle may be an integral child of the element so don't remove it
				var
					parent,
					window = document.createElement('div'),
					temp,
					cn = function (e)
					{
						return CUtils.GetElementsByClassName(e, window)[0];
					};
				
				window.className = 'ysi_window_outer ysi_window_outer_min';
				window.innerHTML = WINDOW_HTML;
				movableItem.parentNode.appendChild(window);
				
				cn('ysi_window_inner').appendChild(movableItem);
				
				parent = cn('ysi_window_icons');
				
				// Define a local variable with the 'this' object in to use as a closure in event handlers
				var
					lthis = this;
				
				// Minimise
				parent.appendChild(CParts.MakeIcon(32, function () { alert('click'); }));
				// Maximise
				this.bMax = CParts.MakeIcon(16, function () { lthis.Maximise(); });
				parent.appendChild(this.bMax);
				// Restore
				this.bRes = CParts.MakeIcon(48, function () { lthis.Restore(); });
				this.bRes.style.display = 'none';
				parent.appendChild(this.bRes);
				// Close
				parent.appendChild(CParts.MakeIcon(0, function () { lthis.eMovable.style.display = 'none'; }));
				
				temp = cn('ysi_window_bar');
				
				CDragable.prototype.SetElements.call(this, temp, window);
				this.maxState = false;
				
				$event('ondblclick', temp, function () { if (lthis.maxState) lthis.Restore(); else lthis.Maximise(); });
				parent = document.createElement('span');
				parent.innerHTML = this.windowTitle;
				this.eWindowTitle = parent;
				temp.appendChild(parent);
				
				parent = cn('ysi_window_content');
				parent.style.paddingTop = temp.offsetHeight + 'px';
				
				temp = CUtils.GetScreenSize();
				this.SetPos((temp.x - window.clientWidth) / 2, (temp.y - window.clientHeight) / 2);
				
				// Sometimes webkit displays the contents hanging out the bottom of the window slightly
				// It only seems to happen on page load though and only the very first time you load the page
				// I really don't know why, but maximising then minimising seems to fix it, so I've added
				// code to do that, however as I've loaded the page once already I can't test it
				this.Maximise();
				this.Restore();
			},
		Maximise :
			function ()
			{
				// Swap the icons over
				this.bRes.style.display = 'block';
				this.bMax.style.display = 'none';
				// Everything should already be mostly properly placed
				var
					m = this.eMovable,
					s = m.style,
					pos = CUtils.GetScrollPos();
				this.iOldWidth = m.clientWidth;
				this.iOldHeight = m.clientHeight;
				m.className = 'ysi_window_outer ysi_window_outer_max';
				s.left = pos.x + 'px';
				s.top = pos.y + 'px';
				s.width = '100%';
				s.height = '100%';
				this.mScroll = false;
				this.maxState = true;
			},
		Restore :
			function ()
			{
				this.bRes.style.display = 'none';
				this.bMax.style.display = 'block';
				var
					s = this.eMovable.style;
				this.eMovable.className = 'ysi_window_outer ysi_window_outer_min';
				s.left = this.mEX + 'px';
				s.top = this.mEY + 'px';
				s.width = this.iOldWidth;
				s.height = this.iOldHeight;
				this.mScroll = true;
				this.maxState = false;
			},
		SetTitle :
			function (title)
			{
				this.eWindowTitle.innerHTML = title;
			},
		GetHandle :
			function ()
			{
				return this.eMovable;
			}
		},
		// Static methods
		null);

#endif
