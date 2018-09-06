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
class IFCPP_EXPORT IfcRecurrenceTypeEnum;
class IFCPP_EXPORT IfcDayInMonthNumber;
class IFCPP_EXPORT IfcDayInWeekNumber;
class IFCPP_EXPORT IfcMonthInYearNumber;
class IFCPP_EXPORT IfcInteger;
class IFCPP_EXPORT IfcTimePeriod;
//ENTITY
class IFCPP_EXPORT IfcRecurrencePattern : public IfcPPEntity
{ 
public:
	IfcRecurrencePattern();
	IfcRecurrencePattern( int id );
	~IfcRecurrencePattern();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcRecurrencePattern"; }


	// IfcRecurrencePattern -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcRecurrenceTypeEnum>				m_RecurrenceType;
	std::vector<shared_ptr<IfcDayInMonthNumber> >	m_DayComponent;				//optional
	std::vector<shared_ptr<IfcDayInWeekNumber> >	m_WeekdayComponent;			//optional
	std::vector<shared_ptr<IfcMonthInYearNumber> >	m_MonthComponent;			//optional
	shared_ptr<IfcInteger>							m_Position;					//optional
	shared_ptr<IfcInteger>							m_Interval;					//optional
	shared_ptr<IfcInteger>							m_Occurrences;				//optional
	std::vector<shared_ptr<IfcTimePeriod> >			m_TimePeriods;				//optional
};

