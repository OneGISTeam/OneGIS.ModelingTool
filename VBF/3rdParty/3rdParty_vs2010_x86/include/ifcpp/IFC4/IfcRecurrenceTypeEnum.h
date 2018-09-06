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

// TYPE IfcRecurrenceTypeEnum = ENUMERATION OF	(DAILY	,WEEKLY	,MONTHLY_BY_DAY_OF_MONTH	,MONTHLY_BY_POSITION	,BY_DAY_COUNT	,BY_WEEKDAY_COUNT	,YEARLY_BY_DAY_OF_MONTH	,YEARLY_BY_POSITION);
class IFCPP_EXPORT IfcRecurrenceTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcRecurrenceTypeEnumEnum
	{
		ENUM_DAILY,
		ENUM_WEEKLY,
		ENUM_MONTHLY_BY_DAY_OF_MONTH,
		ENUM_MONTHLY_BY_POSITION,
		ENUM_BY_DAY_COUNT,
		ENUM_BY_WEEKDAY_COUNT,
		ENUM_YEARLY_BY_DAY_OF_MONTH,
		ENUM_YEARLY_BY_POSITION
	};

	IfcRecurrenceTypeEnum();
	IfcRecurrenceTypeEnum( IfcRecurrenceTypeEnumEnum e ) { m_enum = e; }
	~IfcRecurrenceTypeEnum();
	virtual const char* className() const { return "IfcRecurrenceTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcRecurrenceTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcRecurrenceTypeEnumEnum m_enum;
};

