#include "C_OperatorSTObject.h"

C_OperatorSTObject::C_OperatorSTObject()
{

}

C_OperatorSTObject::~C_OperatorSTObject()
{

}

vector<CVBF_STObject*> C_OperatorSTObject::intersections( vector<CVBF_STObject*> first, vector<CVBF_STObject*> second )
{
	vector<CVBF_STObject*> retVal;
	vector<CVBF_STObject*>::iterator iter_first = first.begin();
	while(iter_first != first.end()){
		vector<CVBF_STObject*>::iterator iter_second = second.begin();
		while(iter_second != second.end()){
			if((*iter_first)->GetID() == (*iter_second)->GetID()){
				retVal.push_back(*iter_first);
			}
			iter_second++;
		}
		iter_first++;
	}
	return retVal;
}

vector<CVBF_STObject*> C_OperatorSTObject::unionset( vector<CVBF_STObject*> first, vector<CVBF_STObject*> second )
{
	vector<CVBF_STObject*> retVal = first;
	vector<CVBF_STObject*>::iterator iter_second = second.begin();
	while(iter_second != second.end()){
		vector<CVBF_STObject*>::iterator iter_ret = retVal.begin();
		while(iter_ret != retVal.end()){
			if((*iter_second)->GetID() != (*iter_ret)->GetID()){
				retVal.push_back(*iter_second);
			}
			iter_ret++;
		}
		iter_second++;
	}
	return retVal;
}
