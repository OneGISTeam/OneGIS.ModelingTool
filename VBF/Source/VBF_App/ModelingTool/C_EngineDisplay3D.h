#pragma once
#include "IC_EngineDisplay.h"
#include "VBF_Plot/IVBF_3DPlotDoc.h"

/*
 * @brief ��ά��ʾ���棬������ά��������ʾ
 */
class C_EngineDisplay3D: public IC_EngineDisplay
{
public:
	C_EngineDisplay3D(void);
	~C_EngineDisplay3D(void);

	/*
	 * @brief ��ȡ3D��ͼ�ĵ��ӿڣ���ͼ�ĵ���������ͼ��ͼ��
	 * @return IVBF_3DPlotDoc* ��ά��ͼ�ĵ��ӿ�ָ��
	 */
	IVBF_3DPlotDoc* get3DPlotDoc() {return m_p3DPlotDoc;}

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
	IVBF_3DPlotDoc* m_p3DPlotDoc;
};

