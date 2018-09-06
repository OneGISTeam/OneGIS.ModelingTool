#ifndef IC_MANAGERSTOBJECTRELATION_H 
#define IC_MANAGERSTOBJECTRELATION_H

#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"
#include "IC_FilterSTObjectRelation.h"
#include "IC_AccessFileRelation.h"

using namespace std;

/*
 * @brief ������ʱ�ն���������ӿڣ����ڶ����ͳһ��������
 */
class IC_ManagerSTObjectRelation{

public:
	virtual ~IC_ManagerSTObjectRelation() {};

	/*
	 * @brief �����������Ӷ�����ʱ�ն��������ϵ
	 * @param pObject ������ʱ�ն��������ϵָ��
	 */
	virtual void addRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @brief ���������������Ӷ�����ʱ�ն��������ϵ
	 * @param pObject ������ʱ�ն��������ϵָ�뼯��
	 */
	virtual void addRelations(vector<CVBF_STObjectRelation*> pRelations) = 0;

	/*
	 * @brief �Ƴ�������ʱ�ն��������ϵ
	 * @param pRelation ������ʱ�ն��������ϵָ��
	 */
	virtual void removeRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @brief �����Ƴ�������ʱ�ն��������ϵ
	 * @param pRelations ������ʱ�ն��������ϵָ�뼯��
	 */
	virtual void removeRelations(vector<CVBF_STObjectRelation*> pRelations) = 0;

	/*
	 * @brief ���ݹ�ϵ��־OID����ȡ������ʱ�ն��������ϵָ��
	 * @param pObject ������ʱ�ն��������ϵָ��
	 */
	virtual CVBF_STObjectRelation* findRelation(string ROID) = 0;

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն��������ϵ
	 * @param pFilter �����ϵ��������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObjectRelation*> ������ʱ�ն��������ϵָ������
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(IC_FilterSTObjectRelation* pFilter, bool bTimeRegarded = true) = 0;

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն��������ϵ
	 * @param filters �����ϵ������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObjectRelation*> ������ʱ�ն��������ϵָ������
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(ObjectRelationFilters filters, bool bTimeRegarded = true) = 0; 

	/*
	 * @brief ��ȡ������ʱ�ն��������ϵ����
	 * @return vector<CVBF_STObjectRelation*> ������ϵ����
	 */
	virtual vector<CVBF_STObjectRelation*> getRelations() {return m_vect_relations;};

	virtual bool load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects) = 0;

	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> savedObjects) = 0;

protected:
	IC_ManagerSTObjectRelation() {};

	//���������ϵ����
	vector<CVBF_STObjectRelation*> m_vect_relations;

	IC_AccessFileRelation* m_pAccessFileRelation;
};


#endif