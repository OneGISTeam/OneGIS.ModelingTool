#ifndef IC_MANAGERSTOBJECT_H 
#define IC_MANAGERSTOBJECT_H
#include "IC_ManagerSTObjectRelation.h"
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "IC_FilterSTObject.h"
#include <vector>

using namespace std;

/*
 * @brief ������ʱ�ն���������ӿڣ����ڶ����ͳһ��������
 *        ������������ƹ�ϵ����������������
 */
class IC_ManagerSTObject{

public:
	virtual ~IC_ManagerSTObject() {
		if(m_pManagerRelation){
			delete m_pManagerRelation;
		}
	};

	/*
	 * @brief ��ȡ������ʱ�ն���Ĺ�ϵ������
	 * @return IC_ManagerSTObjectRelation* ��ϵ������ָ��
	 */
	IC_ManagerSTObjectRelation* objectRelationManager() {return m_pManagerRelation;};

	/*
	 * @brief �����������Ӷ�����ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ��
	 */
	virtual void addObject(CVBF_STObject* pObject) = 0;

	/*
	 * @brief ���������������Ӷ�����ʱ�ն���
	 * @param pObjects ������ʱ�ն���ָ������
	 */
	virtual void addObjects(vector<CVBF_STObject*> pObjects) = 0;

	/*
	 * @brief �Ƴ�������ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ��
	 *        bFlag   true ��ʹ�ö��������������й���Ҳ����ǿ��ɾ��
	 *                false ������������������й�������Ҫɾ��
	 */
	virtual void removeObject(CVBF_STObject* pObject, bool bFlag = true) = 0;

	/*
	 * @brief �����Ƴ�������ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ������
	 *        bFlag   true ��ʹ�ö��������������й���Ҳ����ǿ��ɾ��
	 *                false ������������������й�������Ҫɾ��
	 */
	virtual void removeObjects(vector<CVBF_STObject*> pObjects, bool bFlag = true) = 0;

	/*
	 * @brief ���ݶ����־OID����ȡ������ʱ�ն���ָ��
	 * @param pObject ������ʱ�ն���ָ��
	 */
	virtual CVBF_STObject* findObject(string OID) = 0;

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն���
	 * @param filters ���������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ������
	 */
	virtual vector<CVBF_STObject*> findObjects(IC_FilterSTObject* pFilter, bool bTimeRegarded = true) = 0;

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն���
	 * @param filters ���������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ������
	 */
	virtual vector<CVBF_STObject*> findObjects(ObjectFilters filters, bool bTimeRegarded = true) = 0;

	/*
	 * @brief ��ȡ������ʱ�ն���ָ������
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ������
	 */
	vector<CVBF_STObject*> getObjects() {return m_vect_objects;};

	/*
	 * @brief ���ض�����ʱ�ն�����ʱĬ�Ϸ�ʽ���ļ����أ����ڿ��ܿ��Դ����ݿ�ֱ�Ӽ��أ�
	 * @param szFilePath    �����ļ�·�������ļ�����
	 *        bLoadRelation �Ƿ���ع�����ϵ��Ĭ��Ϊ����
	 * @return bool ���ؽ����trueΪ�ɹ���falseΪʧ��
	 */
	virtual bool load(const string& szFilePath, bool bLoadRelation = true) = 0;

	/*
	 * @brief ����������ʱ�ն�����ʱĬ�Ϸ�ʽ���ļ����������ڿ���ֱ�����ݿ���⣩
	 * @param szFilePath    �����ļ�·�������ļ�����
	 *        bLoadRelation �Ƿ񵼳�������ϵ��Ĭ��Ϊ����
	 * @return bool ���������trueΪ�ɹ���falseΪʧ��
	 */
	virtual bool save(const string& szFilePath, bool bSaveRelation = true) = 0;

protected:
	IC_ManagerSTObject(IC_ManagerSTObjectRelation* pManagerRelation) {m_pManagerRelation = pManagerRelation;};

protected:
	//������ʱ�ն��������ϵ������
	IC_ManagerSTObjectRelation* m_pManagerRelation;
	
	//������ʱ�ն���ָ�뼯��
	vector<CVBF_STObject*> m_vect_objects;
};


#endif