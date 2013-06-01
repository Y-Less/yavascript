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
//  The Original Code is the yavascript development system - colorpick.js.   
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

// Demonstration code using yavascript
// directives for modular coding.

#include '../Libraries/DragRestrict.js'
#include '../Libraries/Window.js'

#define GRAD_HEIGHT (51)

#define GRAD_SCALE (5)

#define PICK_HEIGHT (256)
#define PICK_WIDTH (256)

var
	gBase;

function $(el)
{
	return document.getElementById(el);
}

function Gradiate(base, pos)
{
	var
		h = GRAD_HEIGHT / 2
	if (pos < h)
	{
		// Scale to 255
		return 255 - ((255 - base) * (pos / h));
	}
	else
	{
		// Scale to 0
		return base - ((base * (pos - h)) / h);
	}
}

function Scale(col, y)
{
	if (col > 127)
	{
		return col - ((y * (col - 127)) / PICK_HEIGHT);
	}
	else
	{
		return col + ((y * (127 - col)) / PICK_HEIGHT);
	}
}

function Inc(x, seg)
{
	return ((1530 * x) / PICK_WIDTH) - (255 * seg);
}

function Dec(x, seg)
{
	return (255 * (seg + 1)) - ((1530 * x) / PICK_WIDTH);
}

function GetColor(x, y)
{
	var
		r,
		g,
		b;
	// Get the color of the top of the column based on the x location
	if (x < ((PICK_WIDTH * 1) / 6))
	{
		r = 255;
		g = Inc(x, 0);
		b = 0;
	}
	else if (x < ((PICK_WIDTH * 2) / 6))
	{
		r = Dec(x, 1);
		g = 255;
		b = 0;
	}
	else if (x < ((PICK_WIDTH * 3) / 6))
	{
		r = 0;
		g = 255;
		b = Inc(x, 2);
	}
	else if (x < ((PICK_WIDTH * 4) / 6))
	{
		r = 0;
		g = Dec(x, 3);
		b = 255;
	}
	else if (x < ((PICK_WIDTH * 5) / 6))
	{
		r = Inc(x, 4);
		g = 0;
		b = 255;
	}
	else
	{
		r = 255;
		g = 0;
		b = Dec(x, 5);
	}
	// All colors are now their top color, scale to 127 vertically
	return {r : Scale(r, y), g : Scale(g, y), b : Scale(b, y)};
}

function DrawGradient(base)
{
	var
		grad = '';
	for (var i = 0; i < GRAD_HEIGHT; i++)
	{
		var
			r = Gradiate(base.r, i),
			g = Gradiate(base.g, i),
			b = Gradiate(base.b, i);
		grad += '<img src="Images/dot.gif" style="background-color: rgb(' + Math.round(r) + ',' + Math.round(g) + ',' + Math.round(b) + '); height: ' + GRAD_SCALE + 'px;">';
	}
	$('grad').innerHTML = grad;
}

$event('onload', window, function (event)
	{
		var
			// Create the window
			selection = new CWindow('Select color', 'picker'),
			image = $('pick_image'),
			// Create the picker
			pick = $('pick_pointer');//,
			pickObj = new CDragRestrict(pick),
			pos0 = CUtils.GetElementPos(image),
			pos1 = CUtils.GetElementPos(pick),
			size = CUtils.GetElementSize(pick);
		
		// Initialise the gradient bar
		gBase = GetColor(10, 10);
		DrawGradient(gBase);
		
		// Calculate the exact relative constraints
		pos0.x -= pos1.x + (size.x / 2);
		pos0.y -= pos1.y + (size.y / 2);
		
		// Set the positional constraints
		pickObj.SetArea(pos0.x + 1, pos0.y + 1, pos0.x + PICK_WIDTH - 1, pos0.y + PICK_HEIGHT - 1);
		pickObj.SetPos(pos0.x + 10, pos0.y + 10);
		
		// Add movement handler, I'll integrate this
		// into $event later for compatability
		pickObj.OnMove = function (dx, dy)
		{
			var
				epos = CUtils.GetElementPos(image),
				mpos = CUtils.GetElementPos(this.eMovable);
			gBase = GetColor(mpos.x - epos.x + size.x / 2, mpos.y - epos.y + size.x / 2);
			DrawGradient(gBase);
		}
		
		// Add an onclick to update the gradient bar
		$event('onclick', image, function (event)
			{
				var
					mpos = CUtils.GetMousePos(event);
				pickObj.SetPosAbs(mpos.x - size.x / 2, mpos.y - size.y / 2);
			});
		
		// Add an onclick to display the selected color
		$event('onclick', $('grad'), function (event)
			{
				var
					y = CUtils.GetMousePos(event).y - CUtils.GetElementPos(this).y,
					r = Math.round(Gradiate(gBase.r, y)),
					g = Math.round(Gradiate(gBase.g, y)),
					b = Math.round(Gradiate(gBase.b, y));
				alert('#' + CUtils.ToHex(r, 2) + CUtils.ToHex(g, 2) + CUtils.ToHex(b, 2) + ' (' + r + ', ' + g + ', ' + b + ')');
			});
	});
