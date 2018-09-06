//*******************************************************************
// FileName��VBF_GraphicsPolyPolyline.h
// Function����άͼ�Σ�һ������
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLY_POLYLINE_H__
#define __VBF_GRAPHICS_POLY_POLYLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


// ���������
typedef std::vector<osg::Vec2f>  CVBF_Point2DList;


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyPolyline : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyPolyline(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyPolyline();

	// ���һ�����ߣ�����strID��ʾ���������е�ΨһID�ţ��������ظ��������ID���Ѿ����ڷ���false
	bool AddLine(const std::string& strID, const CVBF_Point2DList& vPoints);

	// ��ȡĳ�����ߵ����괮��������ߵ�ID�Ų����ڷ���false
	bool GetLine(const std::string& strID, CVBF_Point2DList& vPoints);

	// ɾ��һ�����ߣ�������ߵ�ID�Ų����ڷ���false
	bool RemoveLine(const std::string& strID);

	// ����/��ȡ�������ߵ���ʽ
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// ����/��ȡ����������Ƿ�ɼ���Ĭ��ֵΪtrue��
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // ����/��ȡ������������ʽ
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    // �������ߺ������
    osg::Geometry* CreateLine(const CVBF_Point2DList& vPoints);
    osg::Geometry* CreatePoints();

private:

	// ����ӳ���key=���ߵ�ID�ţ�value=���ߵ����괮
	typedef std::map<std::string, CVBF_Point2DList>  CVBF_LineMap;
	CVBF_LineMap				m_mapLines;

	// ����㣨��GL_POINTS��ʽ���ƣ�
	bool						m_bPointVisible;	// �Ƿ���ʾ�����
	VBF_POINTSTYLE				m_PointStyle;		// ��������ʽ

	// ���ߵ���ʽ
	VBF_LINESTYLE				m_LineStyle;
};


#endif 
