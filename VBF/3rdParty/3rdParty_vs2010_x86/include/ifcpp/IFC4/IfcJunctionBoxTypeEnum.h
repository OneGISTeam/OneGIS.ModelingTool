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

// TYPE IfcJunctionBoxTypeEnum = ENUMERATION OF	(DATA	,POWER	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcJunctionBoxTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcJunctionBoxTypeEnumEnum
	{
		ENUM_DATA,
		ENUM_POWER,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcJunctionBoxTypeEnum();
	IfcJunctionBoxTypeEnum( IfcJunctionBoxTypeEnumEnum e ) { m_enum = e; }
	~IfcJunctionBoxTypeEnum();
	virtual const char* className() const { return "IfcJunctionBoxTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcJunctionBoxTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcJunctionBoxTypeEnumEnum m_enum;
};

