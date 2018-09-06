#include "C_ManagerSTObjectRelation.h"

C_ManagerSTObjectRelation::C_ManagerSTObjectRelation()
{

}

C_ManagerSTObjectRelation::~C_ManagerSTObjectRelation()
{

}

void C_ManagerSTObjectRelation::addRelation( CVBF_STObjectRelation* pRelation )
{
	CVBF_STObjectRelation* pResult = findRelation(pRelation->GetID());
	if(!pResult){
		m_vect_relations.push_back(pRelation);
	}
}

void C_ManagerSTObjectRelation::addRelations( vector<CVBF_STObjectRelation*> pRelations )
{
	vector<CVBF_STObjectRelation*>::iterator iter = pRelations.begin();
	while(iter != pRelations.end()){
		addRelation(*iter);
		iter++;
	}
}

void C_ManagerSTObjectRelation::removeRelation( CVBF_STObjectRelation* pRelation )
{
	vector<CVBF_STObjectRelation*>::iterator iter = m_vect_relations.begin();
	while(iter != m_vect_relations.end()){
		if((*iter) == pRelation){
			m_vect_relations.erase(iter);
			return;
		}
		iter++;
	}
}

void C_ManagerSTObjectRelation::removeRelations( vector<CVBF_STObjectRelation*> pRelations )
{
	vector<CVBF_STObjectRelation*>::iterator iter = pRelations.begin();
	while(iter != pRelations.end()){
		removeRelation(*iter);
		iter++;
	}
}

CVBF_STObjectRelation* C_ManagerSTObjectRelation::findRelation( string ROID )
{
	vector<CVBF_STObjectRelation*>::iterator iter = m_vect_relations.begin();
	while(iter != m_vect_relations.end()){
		if((*iter)->GetID() == ROID){
			return (*iter);
		}
		iter++;
	}
	return NULL;
}

vector<CVBF_STObjectRelation*> C_ManagerSTObjectRelation::findRelations( IC_FilterSTObjectRelation* pFilter, bool bTimeRegarded )
{
	vector<CVBF_STObjectRelation*> result;
	result = pFilter->filter(m_vect_relations, bTimeRegarded);
	return result;
}

vector<CVBF_STObjectRelation*> C_ManagerSTObjectRelation::findRelations( ObjectRelationFilters filters, bool bTimeRegarded)
{
	vector<CVBF_STObjectRelation*> result;
	ObjectRelationFilters::iterator iter = filters.begin();
	while(iter != filters.end()){
		result = (*iter)->filter(result, bTimeRegarded);
		iter++;
	}
	return result;
}

bool C_ManagerSTObjectRelation::load( const string& szFilePath, vector<CVBF_STObject*> loadedObjects )
{
	return true;
}

bool C_ManagerSTObjectRelation::save( const string& szFilePath, vector<CVBF_STObject*> savedObjects )
{
	return true;
}
