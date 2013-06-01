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
//  The Original Code is the yavascript development system - Test.js.        
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

CTest =
	$class(
		null,
		{
		Flash :
			function ()
			{
				this.flashState = true;
				$interval(CTest._Flash, 1000, this);
			}
		},
		{
		_Flash :
			function (obj)
			{
				CTest.__Flash.call(obj);
			},
		__Flash :
			function ()
			{
				if (this.flashState)
				{
					this.flashState = false;
					this.eMovable.style.display = 'block';
				}
				else
				{
					this.flashState = true;
					this.eMovable.style.display = 'none';
				}
			}
		});
