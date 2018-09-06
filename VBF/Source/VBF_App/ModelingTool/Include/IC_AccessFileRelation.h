#ifndef IC_ACCESSFILERELATION_H
#define IC_ACCESSFILERELATION_H

#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief ������ϵ�ļ����ʽӿڣ��ýӿڵĵ���һ������IC_AccessFileObject�������֮��
 */
class IC_AccessFileRelation{

public:
	virtual ~IC_AccessFileRelation() {};

	/*
	 * @brief ����������ʱ�ն��������ϵ
	 * @param szFilePath ������ϵ�ļ�·��
	 *        saveObjects �ѵ����Ķ�����ʱ�ն���ָ�뼯��
	 *        relations  ������ϵָ�뼯��
	 * @return bool ���������trueΪ�ɹ���falseΪ���ɹ�
	 */
	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> saveObjects, vector<CVBF_STObjectRelation*> relations) = 0;

	/*
	 * @brief ���ض�����ʱ�ն��������ϵ
	 * @param szFilePath ������ϵ�ļ�·��
	 *        loadedObjects �Ѽ��صĶ�����ʱ�ն���ָ�뼯��
	 * @return vector<CVBF_STObjectRelation*> ���سɹ��Ķ�����ʱ�ն��������ϵ����
	 */
	virtual vector<CVBF_STObjectRelation*> load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects) = 0;

protected:
	IC_AccessFileRelation() {};

};

#endif