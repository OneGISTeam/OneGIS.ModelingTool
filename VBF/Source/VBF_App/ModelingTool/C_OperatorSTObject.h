#ifndef C_OPERATORSTOBJECT_H
#define C_OPERATORSTOBJECT_H

#include "VBF_Common/VBF_STObject/VBF_Export.h"
#include "VBF_Common/VBF_STObject/VBF_STObject.h"

using namespace std;

class C_OperatorSTObject{

public:
	C_OperatorSTObject();
	~C_OperatorSTObject();

	/*
	 * @brief 静态函数，求两个对象指针集合的交集
	 * @param first  第一个对象集合
	 *        second 第二个对象集合  
	 * @return vector<CVBF_STObject*> 求交集后的结果
	 */
	static vector<CVBF_STObject*> intersections(vector<CVBF_STObject*> first, vector<CVBF_STObject*> second);

	/*
	 * @brief 静态函数，求两个对象指针集合的并集
	 * @param first  第一个对象集合
	 *        second 第二个对象集合  
	 * @return vector<CVBF_STObject*> 求并集后的结果
	 */
	static vector<CVBF_STObject*> unionset(vector<CVBF_STObject*> first, vector<CVBF_STObject*> second);

};

#endif