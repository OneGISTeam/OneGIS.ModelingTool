#ifndef IC_FILTERSTOBJECT_H
#define IC_FILTERSTOBJECT_H

#include "IC_Filter.h"
#include "VBF_Common/VBF_STObject/VBF_STObject.h"

/*
 * @brief �ػ����������������ɼ̳��Ըýӿڣ��ԶԶ��󼯺Ͻ��й���
 */
class IC_FilterSTObject: public IC_Filter<CVBF_STObject>{

public:
	virtual ~IC_FilterSTObject() {};

protected:
	IC_FilterSTObject() {};
};

typedef vector<IC_FilterSTObject*> ObjectFilters;

#endif