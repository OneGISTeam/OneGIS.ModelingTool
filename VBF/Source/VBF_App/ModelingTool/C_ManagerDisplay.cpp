#include "C_ManagerDisplay.h"


C_ManagerDisplay::C_ManagerDisplay(void)
{
}


C_ManagerDisplay::~C_ManagerDisplay(void)
{
}

void C_ManagerDisplay::registers( IC_EngineDisplay* pEngineDisplay )
{
	if(!getByType(pEngineDisplay->type()))
		m_vect_engines.push_back(pEngineDisplay);
}

void C_ManagerDisplay::unregisters( IC_EngineDisplay* pEngineDisplay )
{
	vector<IC_EngineDisplay*>::iterator iter = m_vect_engines.begin();
	while(iter != m_vect_engines.end()){
		if((*iter) == pEngineDisplay){
			m_vect_engines.erase(iter);
			return;
		}
		iter++;
	}
}

int C_ManagerDisplay::count()
{
	return m_vect_engines.size();
}

IC_EngineDisplay* C_ManagerDisplay::at( int index )
{
	return m_vect_engines[index];
}

IC_EngineDisplay* C_ManagerDisplay::getByType( const string& type )
{
	vector<IC_EngineDisplay*>::iterator iter = m_vect_engines.begin();
	while(iter != m_vect_engines.end()){
		if((*iter)->type() == type){
			return (*iter);
		}
		iter++;
	}
	return NULL;
}

void C_ManagerDisplay::update( vector<CVBF_STObject*> currentObjects, vector<CVBF_STObject*> selectedObjects )
{
	//循环遍历显示引擎，先调用引擎的clear清楚所有内容，再调用createXXX函数创建显示符号
}

void C_ManagerDisplay::update(vector<CVBF_STObjectRelation*> currentRelations, vector<CVBF_STObjectRelation*> selectedRelations)
{

}
