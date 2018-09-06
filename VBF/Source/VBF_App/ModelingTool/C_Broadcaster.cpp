#include "C_Broadcaster.h"

C_Broadcaster::C_Broadcaster(QObject *parent)
	: QObject(parent)
{

}

C_Broadcaster::~C_Broadcaster()
{

}

void C_Broadcaster::emit_addSTObjects( vector<CVBF_STObject*> pObjects )
{
	emit signal_STObjectAdded(pObjects);
}

void C_Broadcaster::emit_addSTObject( CVBF_STObject* pObject )
{
	vector<CVBF_STObject*> pObjects;
	pObjects.push_back(pObject);
	emit signal_STObjectAdded(pObjects);
}

void C_Broadcaster::emit_removeSTObjects( vector<string> vecStr )
{
	emit signal_STObjectRemoved(vecStr);
}

void C_Broadcaster::emit_removeSTObject( string str )
{
	vector<string> vecStr;
	vecStr.push_back(str);
	emit signal_STObjectRemoved(vecStr);
}

void C_Broadcaster::emit_editSTObjects( vector<CVBF_STObject*> pObjects )
{
	emit signal_STObjectEdited(pObjects);
}

void C_Broadcaster::emit_editSTObject( CVBF_STObject* pObject )
{
	vector<CVBF_STObject*> pObjects;
	pObjects.push_back(pObject);
	emit signal_STObjectEdited(pObjects);
}

void C_Broadcaster::emit_setSTObjectsVisibility( map<string,bool> mapVis )
{
	emit signal_STObjectVisibilityChanged(mapVis);
}

void C_Broadcaster::emit_setSTObjectVisibility( string str, bool bVisible )
{
	map<string,bool> mapVis;
	mapVis.insert(make_pair(str, bVisible));
	emit signal_STObjectVisibilityChanged(mapVis);
}

void C_Broadcaster::emit_selectSTObjects( vector<string> vecStr )
{
	emit signal_STObjectSelected(vecStr);
}

void C_Broadcaster::emit_selectSTObject( string str )
{
	vector<string> vecStr;
	vecStr.push_back(str);
	emit signal_STObjectSelected(vecStr);
}

void C_Broadcaster::emit_filterSTObjects( vector<CVBF_STObject*> pObjects )
{
	emit signal_STObjectFiltered(pObjects);
}

void C_Broadcaster::emit_setSTObjectStyle()
{
	emit signal_STObjectStyleChanged();
}

void C_Broadcaster::emit_addRelations(vector<CVBF_STObjectRelation*> pRelations)
{
	emit signal_RelationAdded(pRelations);
}

void C_Broadcaster::emit_addRelation(CVBF_STObjectRelation* pRelation)
{
	vector<CVBF_STObjectRelation*> pRelations;
	pRelations.push_back(pRelation);
	emit signal_RelationAdded(pRelations);
}

void C_Broadcaster::emit_removeRelations( vector<string> vecStr )
{
	emit signal_RelationRemoved(vecStr);
}

void C_Broadcaster::emit_removeRelation( string str )
{
	vector<string> vecStr;
	vecStr.push_back(str);
	emit signal_RelationRemoved(vecStr);
}

void C_Broadcaster::emit_setRelationsVisibility( map<string,bool> mapVis )
{
	emit signal_RelationVisibilityChanged(mapVis);
}

void C_Broadcaster::emit_setRelationVisibility( string str, bool bVisible )
{
	map<string,bool> mapVis;
	mapVis.insert(make_pair(str, bVisible));
	emit signal_RelationVisibilityChanged(mapVis);
}

void C_Broadcaster::emit_selectRelations(vector<string> vecStr)
{
	emit signal_RelationSelected(vecStr);
}

void C_Broadcaster::emit_selectRelation(string str)
{
	vector<string> vecStr;
	vecStr.push_back(str);
	emit signal_RelationSelected(vecStr);
}

void C_Broadcaster::emit_setRelationStyle()
{
	emit signal_RelationStyleChanged();
}

