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
#include "IfcPreDefinedPropertySet.h"
class IFCPP_EXPORT IfcPositiveLengthMeasure;
class IFCPP_EXPORT IfcDoorPanelOperationEnum;
class IFCPP_EXPORT IfcNormalisedRatioMeasure;
class IFCPP_EXPORT IfcDoorPanelPositionEnum;
class IFCPP_EXPORT IfcShapeAspect;
//ENTITY
class IFCPP_EXPORT IfcDoorPanelProperties : public IfcPreDefinedPropertySet
{ 
public:
	IfcDoorPanelProperties();
	IfcDoorPanelProperties( int id );
	~IfcDoorPanelProperties();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcDoorPanelProperties"; }


	// IfcRoot -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcGloballyUniqueId>						m_GlobalId;
	//  shared_ptr<IfcOwnerHistory>							m_OwnerHistory;				//optional
	//  shared_ptr<IfcLabel>								m_Name;						//optional
	//  shared_ptr<IfcText>									m_Description;				//optional

	// IfcPropertyDefinition -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelDeclares> >				m_HasContext_inverse;
	//  std::vector<weak_ptr<IfcRelAssociates> >			m_HasAssociations_inverse;

	// IfcPropertySetDefinition -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcTypeObject> >				m_DefinesType_inverse;
	//  std::vector<weak_ptr<IfcRelDefinesByTemplate> >		m_IsDefinedBy_inverse;
	//  std::vector<weak_ptr<IfcRelDefinesByProperties> >	m_DefinesOccurrence_inverse;

	// IfcPreDefinedPropertySet -----------------------------------------------------------

	// IfcDoorPanelProperties -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcPositiveLengthMeasure>				m_PanelDepth;				//optional
	shared_ptr<IfcDoorPanelOperationEnum>				m_PanelOperation;
	shared_ptr<IfcNormalisedRatioMeasure>				m_PanelWidth;				//optional
	shared_ptr<IfcDoorPanelPositionEnum>				m_PanelPosition;
	shared_ptr<IfcShapeAspect>							m_ShapeAspectStyle;			//optional
};

