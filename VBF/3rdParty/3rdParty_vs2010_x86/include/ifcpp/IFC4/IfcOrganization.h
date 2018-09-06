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
#include "IfcActorSelect.h"
#include "IfcObjectReferenceSelect.h"
#include "IfcResourceObjectSelect.h"
class IFCPP_EXPORT IfcIdentifier;
class IFCPP_EXPORT IfcLabel;
class IFCPP_EXPORT IfcText;
class IFCPP_EXPORT IfcActorRole;
class IFCPP_EXPORT IfcAddress;
class IFCPP_EXPORT IfcOrganizationRelationship;
class IFCPP_EXPORT IfcPersonAndOrganization;
//ENTITY
class IFCPP_EXPORT IfcOrganization : virtual public IfcActorSelect, virtual public IfcObjectReferenceSelect, virtual public IfcResourceObjectSelect, public IfcPPEntity
{ 
public:
	IfcOrganization();
	IfcOrganization( int id );
	~IfcOrganization();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcOrganization"; }


	// IfcOrganization -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcIdentifier>							m_Identification;			//optional
	shared_ptr<IfcLabel>								m_Name;
	shared_ptr<IfcText>									m_Description;				//optional
	std::vector<shared_ptr<IfcActorRole> >				m_Roles;					//optional
	std::vector<shared_ptr<IfcAddress> >				m_Addresses;				//optional
	// inverse attributes:
	std::vector<weak_ptr<IfcOrganizationRelationship> >	m_IsRelatedBy_inverse;
	std::vector<weak_ptr<IfcOrganizationRelationship> >	m_Relates_inverse;
	std::vector<weak_ptr<IfcPersonAndOrganization> >	m_Engages_inverse;
};

