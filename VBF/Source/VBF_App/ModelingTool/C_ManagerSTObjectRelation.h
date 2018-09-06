#ifndef C_MANAGERSTOBJECTRELATION_H
#define C_MANAGERSTOBJECTRELATION_H

#include "IC_ManagerSTObjectRelation.h"

class C_ManagerSTObjectRelation: public IC_ManagerSTObjectRelation{
public:
	C_ManagerSTObjectRelation();
	virtual ~C_ManagerSTObjectRelation();

	/*
	 * @brief �����������Ӷ�����ʱ�ն��������ϵ
	 * @param pObject ������ʱ�ն��������ϵָ��
	 */
	virtual void addRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief ���������������Ӷ�����ʱ�ն��������ϵ
	 * @param pObject ������ʱ�ն��������ϵָ�뼯��
	 */
	virtual void addRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief �Ƴ�������ʱ�ն��������ϵ
	 * @param pRelation ������ʱ�ն��������ϵָ��
	 */
	virtual void removeRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief �����Ƴ�������ʱ�ն��������ϵ
	 * @param pRelations ������ʱ�ն��������ϵָ�뼯��
	 */
	virtual void removeRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief ���ݹ�ϵ��־OID����ȡ������ʱ�ն��������ϵָ��
	 * @param pObject ������ʱ�ն��������ϵָ��
	 */
	virtual CVBF_STObjectRelation* findRelation(string ROID);

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն��������ϵ
	 * @param pFilter �����ϵ��������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObjectRelation*> ������ʱ�ն��������ϵָ������
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(IC_FilterSTObjectRelation* pFilter, bool bTimeRegarded = true);

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն��������ϵ
	 * @param filters �����ϵ������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObjectRelation*> ������ʱ�ն��������ϵָ������
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(ObjectRelationFilters filters,bool bTimeRegarded = true); 

	virtual bool load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects);

	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> savedObjects);
};

#endif