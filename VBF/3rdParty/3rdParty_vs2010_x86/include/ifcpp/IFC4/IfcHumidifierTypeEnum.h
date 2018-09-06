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

// TYPE IfcHumidifierTypeEnum = ENUMERATION OF	(STEAMINJECTION	,ADIABATICAIRWASHER	,ADIABATICPAN	,ADIABATICWETTEDELEMENT	,ADIABATICATOMIZING	,ADIABATICULTRASONIC	,ADIABATICRIGIDMEDIA	,ADIABATICCOMPRESSEDAIRNOZZLE	,ASSISTEDELECTRIC	,ASSISTEDNATURALGAS	,ASSISTEDPROPANE	,ASSISTEDBUTANE	,ASSISTEDSTEAM	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcHumidifierTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcHumidifierTypeEnumEnum
	{
		ENUM_STEAMINJECTION,
		ENUM_ADIABATICAIRWASHER,
		ENUM_ADIABATICPAN,
		ENUM_ADIABATICWETTEDELEMENT,
		ENUM_ADIABATICATOMIZING,
		ENUM_ADIABATICULTRASONIC,
		ENUM_ADIABATICRIGIDMEDIA,
		ENUM_ADIABATICCOMPRESSEDAIRNOZZLE,
		ENUM_ASSISTEDELECTRIC,
		ENUM_ASSISTEDNATURALGAS,
		ENUM_ASSISTEDPROPANE,
		ENUM_ASSISTEDBUTANE,
		ENUM_ASSISTEDSTEAM,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcHumidifierTypeEnum();
	IfcHumidifierTypeEnum( IfcHumidifierTypeEnumEnum e ) { m_enum = e; }
	~IfcHumidifierTypeEnum();
	virtual const char* className() const { return "IfcHumidifierTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcHumidifierTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcHumidifierTypeEnumEnum m_enum;
};

