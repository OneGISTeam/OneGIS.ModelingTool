#ifndef IC_FILTERSTOBJECTRELATION_H
#define IC_FILTERSTOBJECTRELATION_H

#include "IC_Filter.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief �ػ����������ϵ������������ɼ̳��Ըýӿڣ��ԶԹ�����ϵ���й���
 */
class IC_FilterSTObjectRelation: public IC_Filter<CVBF_STObjectRelation>{

public:
	virtual ~IC_FilterSTObjectRelation() {};

protected:
	IC_FilterSTObjectRelation() {};
};

typedef vector<IC_FilterSTObjectRelation*> ObjectRelationFilters;

#endif