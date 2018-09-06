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
#include "IfcRelSpaceBoundary.h"
class IFCPP_EXPORT IfcRelSpaceBoundary1stLevel;
//ENTITY
class IFCPP_EXPORT IfcRelSpaceBoundary1stLevel : public IfcRelSpaceBoundary
{ 
public:
	IfcRelSpaceBoundary1stLevel();
	IfcRelSpaceBoundary1stLevel( int id );
	~IfcRelSpaceBoundary1stLevel();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcRelSpaceBoundary1stLevel"; }


	// IfcRoot -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcGloballyUniqueId>						m_GlobalId;
	//  shared_ptr<IfcOwnerHistory>							m_OwnerHistory;				//optional
	//  shared_ptr<IfcLabel>								m_Name;						//optional
	//  shared_ptr<IfcText>									m_Description;				//optional

	// IfcRelationship -----------------------------------------------------------

	// IfcRelConnects -----------------------------------------------------------

	// IfcRelSpaceBoundary -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcSpaceBoundarySelect>					m_RelatingSpace;
	//  shared_ptr<IfcElement>								m_RelatedBuildingElement;
	//  shared_ptr<IfcConnectionGeometry>					m_ConnectionGeometry;		//optional
	//  shared_ptr<IfcPhysicalOrVirtualEnum>				m_PhysicalOrVirtualBoundary;
	//  shared_ptr<IfcInternalOrExternalEnum>				m_InternalOrExternalBoundary;

	// IfcRelSpaceBoundary1stLevel -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcRelSpaceBoundary1stLevel>				m_ParentBoundary;			//optional
	// inverse attributes:
	std::vector<weak_ptr<IfcRelSpaceBoundary1stLevel> >	m_InnerBoundaries_inverse;
};

