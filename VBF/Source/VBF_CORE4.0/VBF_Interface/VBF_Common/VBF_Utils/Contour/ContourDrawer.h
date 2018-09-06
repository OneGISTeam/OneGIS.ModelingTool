#if !defined(AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_)
#define AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ContourObj.h"


class CContour;


// 等值线绘制器,负责等值线的绘制以及绘制属性的管理
class CContourDrawer  
{
public:
	CContourDrawer(CContour* pContour);
	virtual ~CContourDrawer();

	void CreateContourObjs();
//***	void DoDraw(CDC* pDC, const CRect& drawRect);
//    void ModifyColorTable();

private:
	//-----绘制相关---------------
//***	void CalcScaleRatioAndTranslateXY(CDC* pDC,const CRect& drawRect);
//***	void DrawGridBorder(CDC* pDC);
//***	void DrawContours(CDC* pDC);
	

	//-----绘制对象-------------
	void RemoveAllContourObjs(); //清除所有的ContourObj对象

private:
	CContour* m_pContourOwner; //所要绘制的等值线
    std::vector<CContourObjLine*> m_vContourObjLines; //绘制对象集合

	CColorLookUpTable m_ColorTable;


	//------实现缩放和平移--------------
	float m_ScaleRatio; //缩放比例
	float m_TranslateX; //X方向平移量
	float m_TranslateY; //Y方向平移量

};

#endif // !defined(AFX_CONTOURDRAWER_H__0BD72FC9_023F_4CDA_85EF_CB9EAED3883A__INCLUDED_)
