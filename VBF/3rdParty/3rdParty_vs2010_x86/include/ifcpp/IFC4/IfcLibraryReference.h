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
#include "IfcLibrarySelect.h"
#include "IfcExternalReference.h"
class IFCPP_EXPORT IfcText;
class IFCPP_EXPORT IfcLanguageId;
class IFCPP_EXPORT IfcLibraryInformation;
class IFCPP_EXPORT IfcRelAssociatesLibrary;
//ENTITY
class IFCPP_EXPORT IfcLibraryReference : virtual public IfcLibrarySelect, public IfcExternalReference
{ 
public:
	IfcLibraryReference();
	IfcLibraryReference( int id );
	~IfcLibraryReference();
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map );
	virtual void setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self );
	virtual void getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes );
	virtual void unlinkFromInverseCounterparts();
	virtual const char* className() const { return "IfcLibraryReference"; }


	// IfcExternalReference -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcURIReference>									m_Location;					//optional
	//  shared_ptr<IfcIdentifier>									m_Identification;			//optional
	//  shared_ptr<IfcLabel>										m_Name;						//optional
	// inverse attributes:
	//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_ExternalReferenceForResources_inverse;

	// IfcLibraryReference -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcText>											m_Description;				//optional
	shared_ptr<IfcLanguageId>									m_Language;					//optional
	shared_ptr<IfcLibraryInformation>							m_ReferencedLibrary;		//optional
	// inverse attributes:
	std::vector<weak_ptr<IfcRelAssociatesLibrary> >				m_LibraryRefForObjects_inverse;
};

