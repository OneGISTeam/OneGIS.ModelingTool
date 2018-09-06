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

// TYPE IfcWorkCalendarTypeEnum = ENUMERATION OF	(FIRSTSHIFT	,SECONDSHIFT	,THIRDSHIFT	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcWorkCalendarTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcWorkCalendarTypeEnumEnum
	{
		ENUM_FIRSTSHIFT,
		ENUM_SECONDSHIFT,
		ENUM_THIRDSHIFT,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcWorkCalendarTypeEnum();
	IfcWorkCalendarTypeEnum( IfcWorkCalendarTypeEnumEnum e ) { m_enum = e; }
	~IfcWorkCalendarTypeEnum();
	virtual const char* className() const { return "IfcWorkCalendarTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcWorkCalendarTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcWorkCalendarTypeEnumEnum m_enum;
};

