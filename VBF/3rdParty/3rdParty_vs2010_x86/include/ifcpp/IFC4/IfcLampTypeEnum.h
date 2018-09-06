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

// TYPE IfcLampTypeEnum = ENUMERATION OF	(COMPACTFLUORESCENT	,FLUORESCENT	,HALOGEN	,HIGHPRESSUREMERCURY	,HIGHPRESSURESODIUM	,LED	,METALHALIDE	,OLED	,TUNGSTENFILAMENT	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcLampTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcLampTypeEnumEnum
	{
		ENUM_COMPACTFLUORESCENT,
		ENUM_FLUORESCENT,
		ENUM_HALOGEN,
		ENUM_HIGHPRESSUREMERCURY,
		ENUM_HIGHPRESSURESODIUM,
		ENUM_LED,
		ENUM_METALHALIDE,
		ENUM_OLED,
		ENUM_TUNGSTENFILAMENT,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcLampTypeEnum();
	IfcLampTypeEnum( IfcLampTypeEnumEnum e ) { m_enum = e; }
	~IfcLampTypeEnum();
	virtual const char* className() const { return "IfcLampTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcLampTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcLampTypeEnumEnum m_enum;
};

