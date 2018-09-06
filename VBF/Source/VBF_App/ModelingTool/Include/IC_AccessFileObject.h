#ifndef IC_ACCESSFILEOBJECT_H
#define IC_ACCESSFILEOBJECT_H

#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include <vector>

using namespace std;

class IC_AccessFileObject{
public:
	virtual ~IC_AccessFileObject() {};

	/*
	 * @brief �����ĵ����ؽӿڣ����ڶ�ȡ���Ͻ�����ʽ��׼�Ķ����ļ�
	 * @param szFilePath �ļ�·��
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ�뼯��
	 */
	virtual vector<CVBF_STObject*> load(const string& szFilePath) = 0;

	/*
	 * @brief �����ĵ�����ӿڣ����ڽ��ڴ��е����ݵ����ɷ��Ͻ�����ʽ��׼�Ķ����ļ�
	 * @param szFilePath �ļ�·��
	 * @return bool ��������trueΪ�ɹ��������ж���
	 *                        falseΪû�гɹ��������ж���
	 */
	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> objects) = 0;

protected:
	IC_AccessFileObject() {};
};

#endif