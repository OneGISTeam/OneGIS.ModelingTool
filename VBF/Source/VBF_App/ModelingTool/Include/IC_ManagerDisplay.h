#ifndef IC_MANAGERDISPLAY_H
#define IC_MANAGERDISPLAY_H

#include <QObject>
#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"
#include "IC_EngineDisplay.h"

using namespace std;

class IC_EngineDisplay;
/*
 * @brief ��ʾ����������Ҫ������ʾ���漰��ʾ�����Ĺ���
 */
class IC_ManagerDisplay: public QObject{
public:
	virtual ~IC_ManagerDisplay() {};

	/*
	 * @brief ע����ʾ����
	 * @param pEngineDisplay ��ʾ����ӿ�
	 */
	virtual void registers(IC_EngineDisplay* pEngineDisplay) = 0;

	/*
	 * @brief ע����ʾ����
	 * @param pEngineDisplay ��ʾ����ӿ�
	 */
	virtual void unregisters(IC_EngineDisplay* pEngineDisplay) = 0;

	/*
	 * @brief �����ʾ���������
	 * @return int ��ʾ���������
	 */
	virtual int count() = 0;

	/*
	 * @brief ���������Ż�ȡ��ʾ����ָ��
	 * @return IC_EngineDisplay* ��ʾ����ָ��
	 */
	virtual IC_EngineDisplay* at(int index) = 0;

	/*
	 * @brief ͨ�����ͻ����ʾ���棬�ýӿ�Ҫȷ��typeΨһ����ʹ��
	 * @param type ��ʾ��������
	 * @return IC_EngineDisplay* ��ʾ����ָ��
	 */
	virtual IC_EngineDisplay* getByType(const string& type) = 0;

	/*
	 * @brief ͨ����ʾ���棬������ʾ����
	 * @param currentObjects   ���ƶ���ָ�뼯��
	 *        selectedObjects  ѡ�ж���ָ�뼯��
	 */
	virtual void update(vector<CVBF_STObject*> currentObjects, vector<CVBF_STObject*> selectedObjects) = 0;

	/*
	 * @brief ͨ����ʾ���棬������ʾ����
	 * @param currentObjects   ���ƶ����ϵָ�뼯��
	 *        selectedObjects  ѡ�ж����ϵָ�뼯��
	 */
	virtual void update(vector<CVBF_STObjectRelation*> currentRelations, vector<CVBF_STObjectRelation*> selectedRelations) = 0;

protected:
	IC_ManagerDisplay() {};
	vector<IC_EngineDisplay*> m_vect_engines;
};

#endif