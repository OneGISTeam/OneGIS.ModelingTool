//*******************************************************************
// FileName：VBF_GraphicsArc.h
// Function：二维图形：弧段
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_ARC_H__
#define __VBF_GRAPHICS_ARC_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsShape.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsArc : public CVBF_GraphicsShape
{
public:
	CVBF_GraphicsArc(const std::string& strName="");
	virtual ~CVBF_GraphicsArc();

	// 设置/获取弧段的形状参数
	void SetTess(const osg::Vec2f& ptCenter, float a, float b, float fAngle0, float fAngle1);
	void GetTess(osg::Vec2f& ptCenter, float& a, float& b, float& fAngle0, float& fAngle1)
	{
		ptCenter = m_ptOffset;
		a		 = m_fScaleX;
		b		 = m_fScaleY;
		fAngle0  = m_fAngle0;
		fAngle1  = m_fAngle1;
	}

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();

protected:

    // 创建弧段的实体和边线部分
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();

protected:

	// 圆心及半径
	float					m_fAngle0;			// 起始角
	float					m_fAngle1;			// 终止角

	// 圆周分割数
	int						m_nNumSplit;
	float					m_fDeltaTheta;		// 圆周上相邻两点之间的角度间隔

	// 与场景图有关的内容
	ref_ptr<osg::Geometry>	m_piGeomSolid;
	ref_ptr<osg::Geometry>	m_piGeomLine;
};


#endif 
