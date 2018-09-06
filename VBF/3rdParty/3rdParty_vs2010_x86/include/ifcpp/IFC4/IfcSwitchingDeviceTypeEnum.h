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

// TYPE IfcSwitchingDeviceTypeEnum = ENUMERATION OF	(CONTACTOR	,DIMMERSWITCH	,EMERGENCYSTOP	,KEYPAD	,MOMENTARYSWITCH	,SELECTORSWITCH	,STARTER	,SWITCHDISCONNECTOR	,TOGGLESWITCH	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcSwitchingDeviceTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcSwitchingDeviceTypeEnumEnum
	{
		ENUM_CONTACTOR,
		ENUM_DIMMERSWITCH,
		ENUM_EMERGENCYSTOP,
		ENUM_KEYPAD,
		ENUM_MOMENTARYSWITCH,
		ENUM_SELECTORSWITCH,
		ENUM_STARTER,
		ENUM_SWITCHDISCONNECTOR,
		ENUM_TOGGLESWITCH,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcSwitchingDeviceTypeEnum();
	IfcSwitchingDeviceTypeEnum( IfcSwitchingDeviceTypeEnumEnum e ) { m_enum = e; }
	~IfcSwitchingDeviceTypeEnum();
	virtual const char* className() const { return "IfcSwitchingDeviceTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcSwitchingDeviceTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcSwitchingDeviceTypeEnumEnum m_enum;
};

