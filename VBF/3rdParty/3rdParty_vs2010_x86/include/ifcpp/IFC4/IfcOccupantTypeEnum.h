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

// TYPE IfcOccupantTypeEnum = ENUMERATION OF	(ASSIGNEE	,ASSIGNOR	,LESSEE	,LESSOR	,LETTINGAGENT	,OWNER	,TENANT	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcOccupantTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcOccupantTypeEnumEnum
	{
		ENUM_ASSIGNEE,
		ENUM_ASSIGNOR,
		ENUM_LESSEE,
		ENUM_LESSOR,
		ENUM_LETTINGAGENT,
		ENUM_OWNER,
		ENUM_TENANT,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcOccupantTypeEnum();
	IfcOccupantTypeEnum( IfcOccupantTypeEnumEnum e ) { m_enum = e; }
	~IfcOccupantTypeEnum();
	virtual const char* className() const { return "IfcOccupantTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcOccupantTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcOccupantTypeEnumEnum m_enum;
};

