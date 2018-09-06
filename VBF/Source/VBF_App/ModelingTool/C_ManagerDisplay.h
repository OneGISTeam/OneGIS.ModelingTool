#pragma once
#include "IC_ManagerDisplay.h"

class C_ManagerDisplay: public IC_ManagerDisplay
{
	Q_OBJECT
public:
	C_ManagerDisplay(void);
	~C_ManagerDisplay(void);

	/*
	 * @brief ע����ʾ����
	 * @param pEngineDisplay ��ʾ����ӿ�
	 */
	virtual void registers(IC_EngineDisplay* pEngineDisplay);

	/*
	 * @brief ע����ʾ����
	 * @param pEngineDisplay ��ʾ����ӿ�
	 */
	virtual void unregisters(IC_EngineDisplay* pEngineDisplay);

	/*
	 * @brief �����ʾ���������
	 * @return int ��ʾ���������
	 */
	virtual int count();

	/*
	 * @brief ���������Ż�ȡ��ʾ����ָ��
	 * @return IC_EngineDisplay* ��ʾ����ָ��
	 */
	virtual IC_EngineDisplay* at(int index);

	/*
	 * @brief ͨ�����ͻ����ʾ���棬�ýӿ�Ҫȷ��typeΨһ����ʹ��
	 * @param type ��ʾ��������
	 * @return IC_EngineDisplay* ��ʾ����ָ��
	 */
	virtual IC_EngineDisplay* getByType(const string& type);

	/*
	 * @brief ͨ����ʾ���棬������ʾ����
	 * @param currentObjects   ���ƶ���ָ�뼯��
	 *        selectedObjects  ѡ�ж���ָ�뼯��
	 */
	virtual void update(vector<CVBF_STObject*> currentObjects, vector<CVBF_STObject*> selectedObjects);

	/*
	 * @brief ͨ����ʾ���棬������ʾ����
	 * @param currentObjects   ���ƶ����ϵָ�뼯��
	 *        selectedObjects  ѡ�ж����ϵָ�뼯��
	 */
	virtual void update(vector<CVBF_STObjectRelation*> currentRelations, vector<CVBF_STObjectRelation*> selectedRelations);
};

