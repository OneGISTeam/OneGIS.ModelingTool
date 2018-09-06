// ContourObj.h: interface for the CContourObjLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTOUROBJ_H__AC6A2306_787D_4F9D_9CDD_21E0B7EC14E3__INCLUDED_)
#define AFX_CONTOUROBJ_H__AC6A2306_787D_4F9D_9CDD_21E0B7EC14E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*===================��ֵ�߻��ƶ�����===========================*

  һ��CContourObjLine����һ����ֵ�����ߵĻ��ƣ�
    
   ���Ƶ����ݰ���: ������ �� �������

                |-->����
    ������------|
                |-->��ɫ
   
	            |-->ǰ��ɫ
    �������----|
	            |-->����ɫ
                |
                |-->�������

   jeny_man@163.com
*==============================================================*/

#include "VBF_Common/VBF_Utils/Contour/GeoStruct.h"
#include "VBF_Common/VBF_Utils/Contour/ColorLookUpTable.h"


class CContourObjLine  
{
public:
	CContourObjLine(CCurve*  pCoord, float value);
	~CContourObjLine();
	
public:
//***	void Draw(CDC* pDC, const CColorLookUpTable& clrTbl, float scaleRatio, float moveDeltX, float moveDeltY);

	
private:
	CContourObjLine& operator=(const CContourObjLine&); //not implemented
	CContourObjLine(const CContourObjLine&);            //not implemented

//***	void DrawContours(CDC* pDC, float scaleRatio, float moveDeltX, float moveDeltY);
	
private:
	//------������Ϣ------------------
	CCurve*	m_pCoord; //�õ�ֵ�ߵ�������,ָ���ⲿ������
	float	m_Value; //�õ�ֵ������Ӧ��ֵ
	COLORREF m_LineColor;
};

#endif // !defined(AFX_CONTOUROBJ_H__AC6A2306_787D_4F9D_9CDD_21E0B7EC14E3__INCLUDED_)
