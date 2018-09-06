#ifndef C_FILTERSTOBJECTBYLIFETIME_H
#define C_FILTERSTOBJECTBYLIFETIME_H

#include "IC_FilterSTObject.h"

class AC_FilterSTObject: public IC_FilterSTObject{

public:
	AC_FilterSTObject();
	virtual ~AC_FilterSTObject();

	/*
	 * @brief ��ȡ�����������ƣ�Ҳ��Ψһ��־
	 * @return string ����������
	 */
	virtual string filterName(); 

	/*
	 * @brief �Թ�����ϵ���Ͻ��й���
	 * @param source ��Ҫ���й��˵���ģ�弯��
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObject*> ���˽������
	 */
	virtual vector<CVBF_STObject*> filter(vector<CVBF_STObject*> source, bool bTimeRegarded = true);

private:
	double m_dCurrentTime;
};

#endif