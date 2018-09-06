#ifndef C_FILTERSTOBJECTBYLIFETIME_H
#define C_FILTERSTOBJECTBYLIFETIME_H

#include "IC_FilterSTObject.h"

class AC_FilterSTObject: public IC_FilterSTObject{

public:
	AC_FilterSTObject();
	virtual ~AC_FilterSTObject();

	/*
	 * @brief 获取过滤器的名称，也是唯一标志
	 * @return string 过滤器名称
	 */
	virtual string filterName(); 

	/*
	 * @brief 对关联关系集合进行过滤
	 * @param source 需要进行过滤的类模板集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObject*> 过滤结果集合
	 */
	virtual vector<CVBF_STObject*> filter(vector<CVBF_STObject*> source, bool bTimeRegarded = true);

private:
	double m_dCurrentTime;
};

#endif