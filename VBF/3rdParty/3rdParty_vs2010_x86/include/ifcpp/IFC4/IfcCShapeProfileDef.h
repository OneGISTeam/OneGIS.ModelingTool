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
#include "IfcParameterizedProfileDef.h"
class IFCPP_EXPORT IfcPositiveLengthMeasure;
class IFCPP_EXPORT IfcNonNegativeLengthMeasure;
//ENTITY
class IFCPP_EXPORT IfcCShapeProfileDef : public IfcParameterizedProfileDef
{ 
public:
	IfcCShapeProfileDef();
	IfcCShapeProfileDef( int id );
	~IfcCShapeProfileDef();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcCShapeProfileDef"; }


	// IfcProfileDef -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcProfileTypeEnum>								m_ProfileType;
	//  shared_ptr<IfcLabel>										m_ProfileName;				//optional
	// inverse attributes:
	//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_HasExternalReference_inverse;
	//  std::vector<weak_ptr<IfcProfileProperties> >				m_HasProperties_inverse;

	// IfcParameterizedProfileDef -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcAxis2Placement2D>								m_Position;					//optional

	// IfcCShapeProfileDef -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcPositiveLengthMeasure>						m_Depth;
	shared_ptr<IfcPositiveLengthMeasure>						m_Width;
	shared_ptr<IfcPositiveLengthMeasure>						m_WallThickness;
	shared_ptr<IfcPositiveLengthMeasure>						m_Girth;
	shared_ptr<IfcNonNegativeLengthMeasure>						m_InternalFilletRadius;		//optional
};

