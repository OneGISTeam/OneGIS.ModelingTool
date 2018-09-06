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
#include "IfcPreDefinedProperties.h"
class IFCPP_EXPORT IfcLengthMeasure;
class IFCPP_EXPORT IfcReinforcingBarRoleEnum;
class IFCPP_EXPORT IfcSectionProperties;
class IFCPP_EXPORT IfcReinforcementBarProperties;
//ENTITY
class IFCPP_EXPORT IfcSectionReinforcementProperties : public IfcPreDefinedProperties
{ 
public:
	IfcSectionReinforcementProperties();
	IfcSectionReinforcementProperties( int id );
	~IfcSectionReinforcementProperties();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcSectionReinforcementProperties"; }


	// IfcPropertyAbstraction -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_HasExternalReferences_inverse;

	// IfcPreDefinedProperties -----------------------------------------------------------

	// IfcSectionReinforcementProperties -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcLengthMeasure>								m_LongitudinalStartPosition;
	shared_ptr<IfcLengthMeasure>								m_LongitudinalEndPosition;
	shared_ptr<IfcLengthMeasure>								m_TransversePosition;		//optional
	shared_ptr<IfcReinforcingBarRoleEnum>						m_ReinforcementRole;
	shared_ptr<IfcSectionProperties>							m_SectionDefinition;
	std::vector<shared_ptr<IfcReinforcementBarProperties> >		m_CrossSectionReinforcementDefinitions;
};

