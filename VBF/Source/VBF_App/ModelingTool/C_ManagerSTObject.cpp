#include "C_ManagerSTObject.h"
#include "C_OperatorSTObject.h"

C_ManagerSTObject::C_ManagerSTObject()
	:IC_ManagerSTObject(new C_ManagerSTObjectRelation())
{

}

void C_ManagerSTObject::addObject( CVBF_STObject* pObject )
{
	CVBF_STObject* pResult = findObject(pObject->GetID());
	if(!pResult){
		m_vect_objects.push_back(pObject);
	}
}

void C_ManagerSTObject::addObjects( vector<CVBF_STObject*> pObjects )
{
	vector<CVBF_STObject*>::iterator iter = pObjects.begin();
	while(iter != pObjects.end()){
		addObject(*iter);
		iter++;
	}
}

void C_ManagerSTObject::removeObject( CVBF_STObject* pObject, bool bFlag /*= true*/ )
{
	//先查找是否是其他对象的子对象
	vector<CVBF_STObject*>::iterator iter = m_vect_objects.begin();
	//临时存放pObject的迭代器位置
	vector<CVBF_STObject*>::iterator temp_iter;
	while(iter != m_vect_objects.end()){
		if((*iter) == pObject){
			temp_iter = iter;
		}

		CVBF_STObjectPart* pPart = (*iter)->Parts().FindPart(pObject);
		if(pPart){
			if(bFlag){
				(*iter)->Parts().RemovePart(pPart);
			}else{
				return ;
			}
		}
		iter++;
	}

	//查找是否是某些对象的关联对象
	vector<CVBF_STObjectRelation*> relations = m_pManagerRelation->getRelations();
	vector<CVBF_STObjectRelation*>::iterator iter_relation = relations.begin();
	while(iter_relation != relations.end()){
		CVBF_STONode* pNode = (*iter_relation)->FindNode(pObject);
		if(pNode){
			if(bFlag){
				CVBF_STOEdges& edges = (*iter_relation)->FindEdge(pNode);
				edges.Edges().Clear(true);
				edges.HalfEdges().Clear(true);

				(*iter_relation)->Nodes().Remove(pNode);
			}else{
				return;
			}
		}
		iter_relation++;
	}

	//删除该对象
	m_vect_objects.erase(temp_iter);
}

void C_ManagerSTObject::removeObjects( vector<CVBF_STObject*> pObjects, bool bFlag /*= true*/ )
{
	vector<CVBF_STObject*>::iterator iter = pObjects.begin();
	while(iter != pObjects.end()){
		removeObjects(pObjects, bFlag);
		iter++;
	}
}

CVBF_STObject* C_ManagerSTObject::findObject( string OID )
{
	vector<CVBF_STObject*>::iterator iter = m_vect_objects.begin();
	while(iter != m_vect_objects.end()){
		if((*iter)->GetID() == OID){
			return *iter;
		}
		iter++;
	}
	return NULL;
}

vector<CVBF_STObject*> C_ManagerSTObject::findObjects( IC_FilterSTObject* pFilter, bool bTimeRegarded )
{
	return pFilter->filter(m_vect_objects, bTimeRegarded);
}

vector<CVBF_STObject*> C_ManagerSTObject::findObjects( ObjectFilters filters,bool bTimeRegarded)
{
/*	vector<CVBF_STObject*> filteredObjects;
	ObjectFilters::iterator iter = filters.begin();
	while(iter != filters.end()-1){
		filteredObjects = (*iter)->filter(m_vect_objects, bTimeRegarded);
		if(bFlag){
			filteredObjects = C_OperatorSTObject::intersections(filteredObjects, (*(iter+1))->filter(m_vect_objects));
		}else{
			filteredObjects = C_OperatorSTObject::unionset(filteredObjects, (*(iter+1))->filter(m_vect_objects));
		}
		iter++;
	}
	return filteredObjects;*/
	ObjectFilters::iterator iter = filters.begin();
	vector<CVBF_STObject*> filteredObjects;
	while(iter != filters.end()){
		filteredObjects = (*iter)->filter(filteredObjects, bTimeRegarded);
		iter++;
	}
	return filteredObjects;
}

bool C_ManagerSTObject::load( const string& szFilePath, bool bLoadRelation /*= true*/ )
{
	return true;
}

bool C_ManagerSTObject::save(const string& szFilePath, bool bSaveRelation /*= true*/)
{
	return true;
}
