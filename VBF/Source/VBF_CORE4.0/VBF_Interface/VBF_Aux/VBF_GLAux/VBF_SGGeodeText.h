//*******************************************************************
// FileName：VBF_SGGeodeText.h
// Function：叶节点，可绘制文本及其背景框，并完成文本的完全布告牌、固定像素大小、定位到椭球
// Author:   杜莹
// Date:     2015-12-03
//*******************************************************************

#ifndef __VBF_SGGEODE_TEXT_H__
#define __VBF_SGGEODE_TEXT_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGeometryBillboard.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Aux/VBF_GLAux/VBF_SGGeodeMatrixTransform.h>

class CVBF_SGDrawableSet;

// 定义字体映射表
typedef std::map< std::string, ref_ptr<osgText::Font> > CVBF_FontMap;


class VBF_GLAUX_EXPORT CVBF_SGGeodeText : public CVBF_SGGeodeMatrixTransform
{
private:
	typedef CVBF_SGGeodeMatrixTransform BaseClass;

public:
	CVBF_SGGeodeText();
	CVBF_SGGeodeText(const CVBF_SGGeodeText& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_SGGeodeText();

	META_Node(VBF, CVBF_SGGeodeText)

	// 初始化场景图
	void Init();

	// 设置/获取文本内容
	void               SetText(const std::string& strText);
	const std::string& GetText() { return m_strText; }

	// 设置/获取文本样式
	void                 SetTextStyle(const VBF_TEXTSTYLE& style) { m_TextStyle = style; }
	const VBF_TEXTSTYLE& GetTextStyle() { return m_TextStyle; }

	// 设置/获取文本背景框的可见性
	void SetFrameVisible(bool bVisible) { m_bFrameVisible = bVisible; }
	bool IsFrameVisible() { return m_bFrameVisible; }

	// 设置/获取文本背景框的样式
	void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style) { m_FrameStyle = style; }
	const VBF_POLYGON2DSTYLE& GetFrameStyle()	{ return m_FrameStyle; }

	// 设置/获取是否绘制背景框中的定位标识符（即文本矩形左边的小三角形，默认为true）
	void SetIndicatorVisible(bool bVisible);
	bool IsIndicatorVisible() { return (m_nTriSpace > 0); }

	// 设置/获取屏幕坐标系下的坐标（单位：像素，默认值为(0,0,-1)）
	void       SetScreenPos(const osg::Vec3d& vPos);
	const osg::Vec3d& GetScreenPos() { return m_vScreenPos; }

    // 判断某个屏幕点是否在文本框范围内
    bool Contains(float x, float y);

private:

	// 创建文本叶节点
	void CreateText();

	// 创建背景框叶节点
	void CreateFrame();

	osg::Geometry* CreateFrame_Solid();
	osg::Geometry* CreateFrame_Wireframe();
	osg::Geometry* CreateFrame_Shadow();

	// 根据文本内容和样式计算背景框尺寸
	void UpdateFrameSize(bool bForceUpdate=false);
	void UpdateFrameVerts();
	void UpdateFrameShadowVerts();

	// 更新文本样式
	void UpdateTextStyle();

	// 从映射表中获取一种字体
	osgText::Font* GetFont(const std::string& strFont);

    // 文本各个参数改变时，更新相应的场景图节点（每帧绘制前调用）
    void UpdateSG();
    void UpdateText();
    void OnUpdateTextStyle();
    void UpdateFrameStyle();

private:

	// 文本
	std::string						m_strText;		// 文本内容
	VBF_TEXTSTYLE					m_TextStyle;	// 文本样式

	// 背景框的样式
	bool							m_bFrameVisible;	// 背景框是否可见
	int								m_nFrameSizeX;		// 宽度（单位：像素）
	int								m_nFrameSizeY;		// 高度（单位：像素）
	VBF_POLYGON2DSTYLE				m_FrameStyle;

	// 小三角形与文本矩形之间的间隔（单位：像素，即等腰三角形的高，该值为0表示不绘制三角形）
	int								m_nTriSpace;

	// 背景框：以屏幕左下角点为原点，背景框左边为小三角形（等腰），右边为文本矩形
	ref_ptr<osg::Vec3Array>			m_piFrameVerts;			// 背景框的7个顶点
	ref_ptr<osg::Vec3Array>			m_piFrameShadowVerts;	// 背景框阴影的8个顶点

	// 记录各个Drawable，以便修改时使用
	ref_ptr<osg::Geometry>			m_piGeomFrameShadow;	// 背景框阴影
	ref_ptr<osg::Geometry>			m_piGeomFrameSolid;		// 背景框实体部分
	ref_ptr<osg::Geometry>			m_piGeomFrameWireframe;	// 背景框网格部分
	ref_ptr<osgText::Text>			m_piText;				// 文本

	// 文本及其背景框在屏幕坐标系下的坐标/偏移量（单位：像素，默认值为(0,0)）
	osg::Vec3d                      m_vScreenPos;		// 用户设置的屏幕坐标

	ref_ptr<CVBF_SGDrawableSet>		m_ipDrawableSet;
};

#endif 
