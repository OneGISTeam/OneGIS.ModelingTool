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
#include "IfcMaterialDefinition.h"
class IFCPP_EXPORT IfcMaterial;
class IFCPP_EXPORT IfcNonNegativeLengthMeasure;
class IFCPP_EXPORT IfcLogical;
class IFCPP_EXPORT IfcLabel;
class IFCPP_EXPORT IfcText;
class IFCPP_EXPORT IfcInteger;
class IFCPP_EXPORT IfcMaterialLayerSet;
//ENTITY
class IFCPP_EXPORT IfcMaterialLayer : public IfcMaterialDefinition
{ 
public:
	IfcMaterialLayer();
	IfcMaterialLayer( int id );
	~IfcMaterialLayer();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcMaterialLayer"; }


	// IfcMaterialDefinition -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelAssociatesMaterial> >			m_AssociatedTo_inverse;
	//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_HasExternalReferences_inverse;
	//  std::vector<weak_ptr<IfcMaterialProperties> >				m_HasProperties_inverse;

	// IfcMaterialLayer -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcMaterial>										m_Material;					//optional
	shared_ptr<IfcNonNegativeLengthMeasure>						m_LayerThickness;
	shared_ptr<IfcLogical>										m_IsVentilated;				//optional
	shared_ptr<IfcLabel>										m_Name;						//optional
	shared_ptr<IfcText>											m_Description;				//optional
	shared_ptr<IfcLabel>										m_Category;					//optional
	shared_ptr<IfcInteger>										m_Priority;					//optional
	// inverse attributes:
	weak_ptr<IfcMaterialLayerSet>								m_ToMaterialLayerSet_inverse;
};

