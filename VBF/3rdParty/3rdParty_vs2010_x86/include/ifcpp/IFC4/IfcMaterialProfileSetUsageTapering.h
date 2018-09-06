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
#include "IfcMaterialProfileSetUsage.h"
class IFCPP_EXPORT IfcMaterialProfileSet;
class IFCPP_EXPORT IfcCardinalPointReference;
//ENTITY
class IFCPP_EXPORT IfcMaterialProfileSetUsageTapering : public IfcMaterialProfileSetUsage
{ 
public:
	IfcMaterialProfileSetUsageTapering();
	IfcMaterialProfileSetUsageTapering( int id );
	~IfcMaterialProfileSetUsageTapering();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcMaterialProfileSetUsageTapering"; }


	// IfcMaterialUsageDefinition -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelAssociatesMaterial> >	m_AssociatedTo_inverse;

	// IfcMaterialProfileSetUsage -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcMaterialProfileSet>					m_ForProfileSet;
	//  shared_ptr<IfcCardinalPointReference>				m_CardinalPoint;			//optional
	//  shared_ptr<IfcPositiveLengthMeasure>				m_ReferenceExtent;			//optional

	// IfcMaterialProfileSetUsageTapering -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcMaterialProfileSet>					m_ForProfileEndSet;
	shared_ptr<IfcCardinalPointReference>				m_CardinalEndPoint;			//optional
};

