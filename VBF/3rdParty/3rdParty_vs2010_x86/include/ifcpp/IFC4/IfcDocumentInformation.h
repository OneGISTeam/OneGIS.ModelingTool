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
#include "IfcDocumentSelect.h"
#include "IfcExternalInformation.h"
class IFCPP_EXPORT IfcIdentifier;
class IFCPP_EXPORT IfcLabel;
class IFCPP_EXPORT IfcText;
class IFCPP_EXPORT IfcURIReference;
class IFCPP_EXPORT IfcActorSelect;
class IFCPP_EXPORT IfcDateTime;
class IFCPP_EXPORT IfcDate;
class IFCPP_EXPORT IfcDocumentConfidentialityEnum;
class IFCPP_EXPORT IfcDocumentStatusEnum;
class IFCPP_EXPORT IfcRelAssociatesDocument;
class IFCPP_EXPORT IfcDocumentReference;
class IFCPP_EXPORT IfcDocumentInformationRelationship;
//ENTITY
class IFCPP_EXPORT IfcDocumentInformation : virtual public IfcDocumentSelect, public IfcExternalInformation
{ 
public:
	IfcDocumentInformation();
	IfcDocumentInformation( int id );
	~IfcDocumentInformation();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcDocumentInformation"; }


	// IfcExternalInformation -----------------------------------------------------------

	// IfcDocumentInformation -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcIdentifier>									m_Identification;
	shared_ptr<IfcLabel>										m_Name;
	shared_ptr<IfcText>											m_Description;				//optional
	shared_ptr<IfcURIReference>									m_Location;					//optional
	shared_ptr<IfcText>											m_Purpose;					//optional
	shared_ptr<IfcText>											m_IntendedUse;				//optional
	shared_ptr<IfcText>											m_Scope;					//optional
	shared_ptr<IfcLabel>										m_Revision;					//optional
	shared_ptr<IfcActorSelect>									m_DocumentOwner;			//optional
	std::vector<shared_ptr<IfcActorSelect> >					m_Editors;					//optional
	shared_ptr<IfcDateTime>										m_CreationTime;				//optional
	shared_ptr<IfcDateTime>										m_LastRevisionTime;			//optional
	shared_ptr<IfcIdentifier>									m_ElectronicFormat;			//optional
	shared_ptr<IfcDate>											m_ValidFrom;				//optional
	shared_ptr<IfcDate>											m_ValidUntil;				//optional
	shared_ptr<IfcDocumentConfidentialityEnum>					m_Confidentiality;			//optional
	shared_ptr<IfcDocumentStatusEnum>							m_Status;					//optional
	// inverse attributes:
	std::vector<weak_ptr<IfcRelAssociatesDocument> >			m_DocumentInfoForObjects_inverse;
	std::vector<weak_ptr<IfcDocumentReference> >				m_HasDocumentReferences_inverse;
	std::vector<weak_ptr<IfcDocumentInformationRelationship> >	m_IsPointedTo_inverse;
	std::vector<weak_ptr<IfcDocumentInformationRelationship> >	m_IsPointer_inverse;
};

