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

// TYPE IfcExternalSpatialElementTypeEnum = ENUMERATION OF	(EXTERNAL	,EXTERNAL_EARTH	,EXTERNAL_WATER	,EXTERNAL_FIRE	,USERDEFINED	,NOTDEFIEND);
class IFCPP_EXPORT IfcExternalSpatialElementTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcExternalSpatialElementTypeEnumEnum
	{
		ENUM_EXTERNAL,
		ENUM_EXTERNAL_EARTH,
		ENUM_EXTERNAL_WATER,
		ENUM_EXTERNAL_FIRE,
		ENUM_USERDEFINED,
		ENUM_NOTDEFIEND
	};

	IfcExternalSpatialElementTypeEnum();
	IfcExternalSpatialElementTypeEnum( IfcExternalSpatialElementTypeEnumEnum e ) { m_enum = e; }
	~IfcExternalSpatialElementTypeEnum();
	virtual const char* className() const { return "IfcExternalSpatialElementTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcExternalSpatialElementTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcExternalSpatialElementTypeEnumEnum m_enum;
};

