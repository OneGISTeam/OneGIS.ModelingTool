#pragma once
#include "IC_EngineDisplay.h"
#include "IC_2DMapDoc.h"

/*
 * @brief ��ά��ʾ���棬�����ά��������ʾ
 */
class C_EngineDisplay2D: public IC_EngineDisplay
{
public:
	C_EngineDisplay2D(void);
	~C_EngineDisplay2D(void);

	/*
	 * @brief ��ȡ2D��ʾ�ĵ��ӿڣ���ͼ�ĵ����������ʾ��ͼ��
	 * @return IC_2DMapDoc* ��ά��ʾ�ĵ��ӿ�ָ��
	 */
	IC_2DMapDoc* get2DMapDoc() {return m_p2DMapDoc;}

	/*
	 * @breif ���ݶ��󴴽���ʾ����
	 * @param pObject ����ָ��
	 */
	virtual void createSymbolFromObject(CVBF_STObject* pObject);

	/*
	 * @breif ���ݶ����Ƴ���ʾ����
	 * @param pObject ����ָ��
	 */
	virtual void removeSymbolOfObject(CVBF_STObject* pObject);

	/*
	 * @breif ���ݶ����ϵ������ʾ����
	 * @param pRelation �����ϵָ��
	 */
	virtual void createSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif ���ݶ����ϵ�Ƴ���ʾ����
	 * @param pRelation �����ϵָ��
	 */
	virtual void removeSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif �����ʾ���������
	 * @param sting ��ʾ���������
	 */
	virtual string type();

	/*
	 * @breif ���������ʾ����
	 */
	virtual void clear();

private:
	IC_2DMapDoc* m_p2DMapDoc;
};

