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
	 * @brief ��̬����������������ָ�뼯�ϵĽ���
	 * @param first  ��һ�����󼯺�
	 *        second �ڶ������󼯺�  
	 * @return vector<CVBF_STObject*> �󽻼���Ľ��
	 */
	static vector<CVBF_STObject*> intersections(vector<CVBF_STObject*> first, vector<CVBF_STObject*> second);

	/*
	 * @brief ��̬����������������ָ�뼯�ϵĲ���
	 * @param first  ��һ�����󼯺�
	 *        second �ڶ������󼯺�  
	 * @return vector<CVBF_STObject*> �󲢼���Ľ��
	 */
	static vector<CVBF_STObject*> unionset(vector<CVBF_STObject*> first, vector<CVBF_STObject*> second);

};

#endif