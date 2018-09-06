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

// TYPE IfcBeamTypeEnum = ENUMERATION OF	(BEAM	,JOIST	,HOLLOWCORE	,LINTEL	,SPANDREL	,T_BEAM	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcBeamTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcBeamTypeEnumEnum
	{
		ENUM_BEAM,
		ENUM_JOIST,
		ENUM_HOLLOWCORE,
		ENUM_LINTEL,
		ENUM_SPANDREL,
		ENUM_T_BEAM,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcBeamTypeEnum();
	IfcBeamTypeEnum( IfcBeamTypeEnumEnum e ) { m_enum = e; }
	~IfcBeamTypeEnum();
	virtual const char* className() const { return "IfcBeamTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcBeamTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcBeamTypeEnumEnum m_enum;
};

