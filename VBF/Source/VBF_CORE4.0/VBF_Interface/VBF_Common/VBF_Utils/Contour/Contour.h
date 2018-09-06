// Contour.h: interface for the CContour class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_)
#define AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ContourValues.h"
#include "GeoStruct.h"
#include "GeoData.h"


/*===================��ֵ����=============================*/

//�������ڱ����ֵ������,�����ֵ��ֵ����ֵ��׷�٣���ֵ�߻��ƣ��ȵ�....
//
//����ͱ༭��ֵ��ֵʱ������CContourValues�������
//�����ɵ�ֵ��ʱ������CContourTracer��ֵ��׷���������׷��
//�ڵ�ֵ�߻���ʱ������CContourDrawer������������
//
/*==============================================================*/
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include "ContourDrawer.h"

class VBF_UTILS_EXPORT CContour
{
public:
    CContour();
	~CContour();

    //����
    bool SetData(const char* szDataFileName) { return m_GeoData.ReadData(szDataFileName); }
    bool SetData(const char* szDataFileName, float interval_x, float  interval_y) { return m_GeoData.ReadData(szDataFileName, interval_x, interval_y); }
    CGeoData* GetData() { return &m_GeoData; }


	//----��ֵ��ֵ����ز���-------------
	int GetNumberOfValues();
	void AddContourValue(float newVal);
	void DeleteContourValue(float oldVal);
	void ReplaceContourValue(float oldVal, float newVal);
	void GenerateContourValues(int numContours, float valStart, float valEnd);

	CValueList& GetValueList();
	float GetValue(int i);
	void SetValueList(CValueList& list);
	void GenerateDefaultContourValues();
	void EditContourLevels(); //�༭��ֵ��


	//----------------------------
	void GenerateContours();
	void RemoveAllContours();



	//-----׷�ٽ��---------
    CContourArray& GetContours() { return m_Contours; }

	//-----�������---------------
//***	void Draw(CDC* pDC,const CRect& drawRect);
    bool IsHavingContours(){ return m_Contours.size()>0;}
//    void ModifyColorTable(){if(m_pContourDrawer) m_pContourDrawer->ModifyColorTable();}
    bool IsGeneratingAgain(){return m_bReGenerated;}


private:
    CContourValues	m_contourValues; // �����ֵ��ֵ
    CContourArray   m_Contours;      // ��ֵ��׷�ٽ�����ڴ���
	CContourDrawer* m_pContourDrawer;
    CGeoData        m_GeoData;

    bool m_bReGenerated; //ָʾ�������Ƿ���Ҫ��������Contour���ƶ���ı�־


private:
	CContour(const CContour& rhs); //not implimented
	CContour& operator=(const CContour& rhs);//not implimented
};

inline int CContour::GetNumberOfValues()
{
	return m_contourValues.GetNumberOfValues();
}

inline void CContour::AddContourValue(float newVal)
{
	m_contourValues.AddValue(newVal);
}

inline void CContour::DeleteContourValue(float oldVal)
{
	m_contourValues.DeleteValue(oldVal);
}

inline void CContour::ReplaceContourValue(float oldVal, float newVal)
{
	m_contourValues.ReplaceValue(oldVal,newVal);
}

inline void CContour::GenerateContourValues(int numContours, float valStart, float valEnd)
{
	m_contourValues.GenerateValues(numContours,valStart,valEnd);
}

inline CValueList& CContour::GetValueList()
{ 
	return m_contourValues.GetValueList(); 
}

inline float CContour::GetValue(int i)
{
	return m_contourValues.GetValue(i);
}

inline void CContour::SetValueList(CValueList& list)
{
	m_contourValues.RemoveAllValues();

    for(int i=0;i<list.size();i++)
    {
        m_contourValues.AddValue(list[i]);
    }

}


#endif // !defined(AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_)
