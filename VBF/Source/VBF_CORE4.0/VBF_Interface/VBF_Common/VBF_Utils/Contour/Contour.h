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


/*===================等值线类=============================*/

//该类用于保存等值线坐标,管理等值线值，等值线追踪，等值线绘制，等等....
//
//管理和编辑等值线值时，引用CContourValues类来完成
//在生成等值线时，引用CContourTracer等值线追踪类来完成追踪
//在等值线绘制时，引用CContourDrawer绘制器来绘制
//
/*==============================================================*/
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include "ContourDrawer.h"

class VBF_UTILS_EXPORT CContour
{
public:
    CContour();
	~CContour();

    //数据
    bool SetData(const char* szDataFileName) { return m_GeoData.ReadData(szDataFileName); }
    bool SetData(const char* szDataFileName, float interval_x, float  interval_y) { return m_GeoData.ReadData(szDataFileName, interval_x, interval_y); }
    CGeoData* GetData() { return &m_GeoData; }


	//----等值线值的相关操作-------------
	int GetNumberOfValues();
	void AddContourValue(float newVal);
	void DeleteContourValue(float oldVal);
	void ReplaceContourValue(float oldVal, float newVal);
	void GenerateContourValues(int numContours, float valStart, float valEnd);

	CValueList& GetValueList();
	float GetValue(int i);
	void SetValueList(CValueList& list);
	void GenerateDefaultContourValues();
	void EditContourLevels(); //编辑等值线


	//----------------------------
	void GenerateContours();
	void RemoveAllContours();



	//-----追踪结果---------
    CContourArray& GetContours() { return m_Contours; }

	//-----绘制相关---------------
//***	void Draw(CDC* pDC,const CRect& drawRect);
    bool IsHavingContours(){ return m_Contours.size()>0;}
//    void ModifyColorTable(){if(m_pContourDrawer) m_pContourDrawer->ModifyColorTable();}
    bool IsGeneratingAgain(){return m_bReGenerated;}


private:
    CContourValues	m_contourValues; // 管理等值线值
    CContourArray   m_Contours;      // 等值线追踪结果放在此中
	CContourDrawer* m_pContourDrawer;
    CGeoData        m_GeoData;

    bool m_bReGenerated; //指示绘制器是否需要重新生成Contour绘制对象的标志


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
