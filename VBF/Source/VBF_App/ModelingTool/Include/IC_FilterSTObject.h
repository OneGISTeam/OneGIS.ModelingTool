#ifndef IC_FILTERSTOBJECT_H
#define IC_FILTERSTOBJECT_H

#include "IC_Filter.h"
#include "VBF_Common/VBF_STObject/VBF_STObject.h"

/*
 * @brief 特化对象过滤器，子类可继承自该接口，以对对象集合进行过滤
 */
class IC_FilterSTObject: public IC_Filter<CVBF_STObject>{

public:
	virtual ~IC_FilterSTObject() {};

protected:
	IC_FilterSTObject() {};
};

typedef vector<IC_FilterSTObject*> ObjectFilters;

#endif