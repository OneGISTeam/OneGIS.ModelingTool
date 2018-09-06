/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and/or modified under  
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
* OpenSceneGraph Public License for more details.
*/

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "model/shared_ptr.h"
#include "model/IfcPPObject.h"
#include "model/IfcPPGlobal.h"

// TYPE IfcWindowStyleOperationEnum = ENUMERATION OF	(SINGLE_PANEL	,DOUBLE_PANEL_VERTICAL	,DOUBLE_PANEL_HORIZONTAL	,TRIPLE_PANEL_VERTICAL	,TRIPLE_PANEL_BOTTOM	,TRIPLE_PANEL_TOP	,TRIPLE_PANEL_LEFT	,TRIPLE_PANEL_RIGHT	,TRIPLE_PANEL_HORIZONTAL	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcWindowStyleOperationEnum : virtual public IfcPPObject
{
public:
	enum IfcWindowStyleOperationEnumEnum
	{
		ENUM_SINGLE_PANEL,
		ENUM_DOUBLE_PANEL_VERTICAL,
		ENUM_DOUBLE_PANEL_HORIZONTAL,
		ENUM_TRIPLE_PANEL_VERTICAL,
		ENUM_TRIPLE_PANEL_BOTTOM,
		ENUM_TRIPLE_PANEL_TOP,
		ENUM_TRIPLE_PANEL_LEFT,
		ENUM_TRIPLE_PANEL_RIGHT,
		ENUM_TRIPLE_PANEL_HORIZONTAL,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcWindowStyleOperationEnum();
	IfcWindowStyleOperationEnum( IfcWindowStyleOperationEnumEnum e ) { m_enum = e; }
	~IfcWindowStyleOperationEnum();
	virtual const char* className() const { return "IfcWindowStyleOperationEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcWindowStyleOperationEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcWindowStyleOperationEnumEnum m_enum;
};

