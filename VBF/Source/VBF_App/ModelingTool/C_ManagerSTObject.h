#pragma once
#include "IC_ManagerSTObject.h"
#include "C_ManagerSTObjectRelation.h"
#include "IC_AccessFileObject.h"
/*
 * @brief ������ʱ�ն�������������ڶ����ͳһ��������
 *        ������������ƹ�ϵ����������������
 */
class C_ManagerSTObject: public IC_ManagerSTObject{

public:
	C_ManagerSTObject();

	/*
	 * @brief �����������Ӷ�����ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ��
	 */
	virtual void addObject(CVBF_STObject* pObject);

	/*
	 * @brief ���������������Ӷ�����ʱ�ն���
	 * @param pObjects ������ʱ�ն���ָ������
	 */
	virtual void addObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief �Ƴ�������ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ��
	 *        bFlag   true ��ʹ�ö��������������й���Ҳ����ǿ��ɾ��
	 *                false ������������������й�������Ҫɾ��
	 */
	virtual void removeObject(CVBF_STObject* pObject, bool bFlag = true);

	/*
	 * @brief �����Ƴ�������ʱ�ն���
	 * @param pObject ������ʱ�ն���ָ������
	 *        bFlag   true ��ʹ�ö��������������й���Ҳ����ǿ��ɾ��
	 *                false ������������������й�������Ҫɾ��
	 */
	virtual void removeObjects(vector<CVBF_STObject*> pObjects, bool bFlag = true);

	/*
	 * @brief ���ݶ����־OID����ȡ������ʱ�ն���ָ��
	 * @param pObject ������ʱ�ն���ָ��
	 */
	virtual CVBF_STObject* findObject(string OID);

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն���
	 * @param filters ���������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ������
	 */
	virtual vector<CVBF_STObject*> findObjects(IC_FilterSTObject* pFilter, bool bTimeRegarded = true);

	/*
	 * @brief ���ݹ���������ȡ������ʱ�ն���
	 * @param filters ���������������
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 *        bFlag   true�����󽻣�false������  
	 * @return vector<CVBF_STObject*> ������ʱ�ն���ָ������
	 */
	virtual vector<CVBF_STObject*> findObjects(ObjectFilters filters, bool bTimeRegarded = true);

	/*
	 * @brief ���ض�����ʱ�ն�����ʱĬ�Ϸ�ʽ���ļ����أ����ڿ��ܿ��Դ����ݿ�ֱ�Ӽ��أ�
	 * @param szFilePath    �����ļ�·�������ļ�����
	 *        bLoadRelation �Ƿ���ع�����ϵ��Ĭ��Ϊ����
	 * @return bool ���ؽ����trueΪ�ɹ���falseΪʧ��
	 */
	virtual bool load(const string& szFilePath, bool bLoadRelation = true);

	/*
	 * @brief ����������ʱ�ն�����ʱĬ�Ϸ�ʽ���ļ����������ڿ���ֱ�����ݿ���⣩
	 * @param szFilePath    �����ļ�·�������ļ�����
	 *        bLoadRelation �Ƿ񵼳�������ϵ��Ĭ��Ϊ����
	 * @return bool ���������trueΪ�ɹ���falseΪʧ��
	 */
	virtual bool save(const string& szFilePath, bool bSaveRelation = true);

protected:
	IC_AccessFileObject* m_pAccessFileObject;
};
