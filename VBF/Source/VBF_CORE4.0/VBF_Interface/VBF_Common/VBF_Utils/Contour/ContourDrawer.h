#if !defined(AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_)
#define AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ContourObj.h"


class CContour;


// ��ֵ�߻�����,�����ֵ�ߵĻ����Լ��������ԵĹ���
class CContourDrawer  
{
public:
	CContourDrawer(CContour* pContour);
	virtual ~CContourDrawer();

	void CreateContourObjs();
//***	void DoDraw(CDC* pDC, const CRect& drawRect);
//    void ModifyColorTable();

private:
	//-----�������---------------
//***	void CalcScaleRatioAndTranslateXY(CDC* pDC,const CRect& drawRect);
//***	void DrawGridBorder(CDC* pDC);
//***	void DrawContours(CDC* pDC);
	

	//-----���ƶ���-------------
	void RemoveAllContourObjs(); //������е�ContourObj����

private:
	CContour* m_pContourOwner; //��Ҫ���Ƶĵ�ֵ��
    std::vector<CContourObjLine*> m_vContourObjLines; //���ƶ��󼯺�

	CColorLookUpTable m_ColorTable;


	//------ʵ�����ź�ƽ��--------------
	float m_ScaleRatio; //���ű���
	float m_TranslateX; //X����ƽ����
	float m_TranslateY; //Y����ƽ����

};

#endif // !defined(AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_)
