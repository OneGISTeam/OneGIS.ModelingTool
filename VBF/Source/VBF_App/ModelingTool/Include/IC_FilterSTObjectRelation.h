#ifndef IC_FILTERSTOBJECTRELATION_H
#define IC_FILTERSTOBJECTRELATION_H

#include "IC_Filter.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief 特化对象关联关系过滤器，子类可继承自该接口，以对关联关系进行过滤
 */
class IC_FilterSTObjectRelation: public IC_Filter<CVBF_STObjectRelation>{

public:
	virtual ~IC_FilterSTObjectRelation() {};

protected:
	IC_FilterSTObjectRelation() {};
};

typedef vector<IC_FilterSTObjectRelation*> ObjectRelationFilters;

#endif