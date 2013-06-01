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
//  The Original Code is the yavascript development system - Style.js.       
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

$include('Utils.js');

#define CSTYLE_TRANSFORM_RESOLUTION (100)
#define CSTYLE_TRANSFORM_TIME (5000)

#define CSTYLE_TYPE_XY (0)
#define CSTYLE_TYPE_COL (1)
#define CSTYLE_TYPE_NUM (2)

CStyle =
		{
		Transform :
			function (element, targets, time, resolution)
			{
				if (!resolution)
				{
					resolution = CSTYLE_TRANSFORM_RESOLUTION;
					if (!time)
					{
						time = CSTYLE_TRANSFORM_TIME;
					}
				}
				if (typeof targets == 'object')
				{
					element = GetElement(element);
					var
						s = window.getComputedStyle(element);
					for (var i in targets)
					{
						var
							c = targets[i];
						targets[i] = [];
						
					}
				}
			}
		};
