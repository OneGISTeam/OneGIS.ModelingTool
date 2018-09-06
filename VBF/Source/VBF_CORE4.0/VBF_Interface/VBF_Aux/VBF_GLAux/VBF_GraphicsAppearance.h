//*******************************************************************
// FileName：VBF_GraphicsAppearance.h
// Function：各种自定义图形的外观属性
// Author:   杜莹
// Date:     2013-11-11
//*******************************************************************

#ifndef __VBF_GRAPHICS_APPEARANCE_H__
#define __VBF_GRAPHICS_APPEARANCE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <Types/VBF_Optional.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Common/VBF_XML/tinyxml.h>

class CVBF_Config;

//---------------------------------------------------------------
// 定义类：VBF_PART_INFO
// 类描述：自定义图形外观的某个部分
//---------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_PartInfo
{
public:
	CVBF_PartInfo();
	virtual ~CVBF_PartInfo();

	// 重载赋值操作符
	CVBF_PartInfo& operator=(const CVBF_PartInfo& src);

	// 设置各种外观参数，返回值为true表示设置成功
	bool SetVisible(bool bVisible);
	bool SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	bool SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	bool SetColor(const osg::Vec4f& color);
	bool SetColor(const osg::Vec4f& color0, const osg::Vec4f& color1);
    bool SetLineStyle(const VBF_LINESTYLE& ls);
	void SetNumTexRepeats(int nNumRows, int nNumCols);

	// 判断该部分是否正在使用静态/动态纹理
	bool IsUsingStaticTexture();
	bool IsUsingDynamicTexture();

public:
	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// 几何绘制方式（实体/网格）
	EVBF_SHADE_STYLE			m_nStyleShade;		// 着色方式（颜色/纹理）

	bool						m_bExist;			// 是否存在（该值由系统自动计算，用户不可修改）
	bool						m_bVisible;			// 是否可见
	osg::Vec4f					m_color0;			// 渐变色的起始色（也即为单一色）
	CVBF_Optional<osg::Vec4f>	m_color1;			// 渐变色的结束色
    VBF_LINESTYLE				m_LineStyle;		// 网格线的粗度

	// 纹理重复次数
	int							m_nNumTexRows;		// 纹理在横向的重复次数
	int							m_nNumTexCols;		// 纹理在纵向的重复次数

	// 纹理
	bool						m_bEnableTex;		// 是否启用了纹理
	bool						m_bTexToCache;		// 是否需要将创建的纹理放入缓存
	ref_ptr<osg::Image>			m_piImage;			// 纹理图像指针
	ref_ptr<osg::Texture2D>		m_piTexture;		// 纹理指针

    // 场景图内容
    ref_ptr<osg::Drawable>      m_ipDrawableSolid;      // 填充部分
    ref_ptr<osg::Drawable>      m_ipDrawableWireframe;  // 网格线部分
};



//---------------------------------------------------------------
// 定义类：CVBF_GraphicsAppearance
// 类描述：自定义图形的外观
//---------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_GraphicsAppearance : public IVBF_GraphicsAppearance
{
public:
	CVBF_GraphicsAppearance();
	virtual ~CVBF_GraphicsAppearance();

	// 设置/获取自定义图形某个部分是否可见，默认值为true
	virtual void SetVisible(int nPart, bool bVisible);
	virtual bool IsVisible(int nPart);

	// 设置/获取某个部分的几何样式，默认为：实心+网格
	virtual void                SetGeometryStyle(int nPart, EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle(int nPart);

	// 设置/获取某个部分的着色样式，默认为：只使用颜色
	virtual void             SetShadeStyle(int nPart, EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle(int nPart);

	// 设置某个部分的单一色（该颜色作用于整个自定义图形）
	virtual void       SetColor(int nPart, const osg::Vec4f& color);
	virtual osg::Vec4f GetColor(int nPart);

	// 设置某个部分的渐变色（该颜色从自定义图形顶部平滑渐变到底部）
	virtual void SetColor(int nPart, const osg::Vec4f& color0, const osg::Vec4f& color1);
	virtual bool GetColor(int nPart, osg::Vec4f& color0, osg::Vec4f& color1);

	// 如果某个部分的样式中包含线框，设置线的粗度（线的颜色与自定义图形相同）
    virtual void  SetLineStyle(int nPart, const VBF_LINESTYLE& ls);
    virtual VBF_LINESTYLE& GetLineStyle(int nPart);

	// 设置/获取某个部分的纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nPart, int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int nPart, int& nNumRows, int& nNumCols);

	// 判断某个部分是否正在使用单一色/渐变色/静态纹理/动态纹理
	virtual bool IsUsingSingleColor(int nPart);
	virtual bool IsUsingFadedColor(int nPart);
	virtual bool IsUsingStaticTexture(int nPart);
	virtual bool IsUsingDynamicTexture(int nPart);

	// 设置/获取某个部分的纹理图像指针
	virtual void		SetTexImage(int nPart, osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage(int nPart);

public:

	// 设置/解除该外观的所有者，即所附属的实体模型
	void SetOwner(IVBF_GraphicsAppearanceOwner* pIOwner) { m_pIOwner = pIOwner; }

	// 重载赋值操作符
	CVBF_GraphicsAppearance& operator=(const CVBF_GraphicsAppearance& src);

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemAppr);
    virtual bool ReadFromXML(TiXmlElement* pElemAppr);

	// 执行json脚本
	virtual void ExecuteScript(const CVBF_Config& conf);

private:

	// 判断给定的自定义图形某个部分的索引号是否有效
	bool IsPartValid(int nPart) { return (nPart>=0 && nPart<(int)m_vPartInfos.size()); }

public:

	// 自定义图形各个部分的信息（该数组中元素的个数由各类模型自己定义）
	std::vector<CVBF_PartInfo>		m_vPartInfos;

	// 观察者（即所附属的实体模型）
	IVBF_GraphicsAppearanceOwner*	m_pIOwner;
};


//-----------------------------------------------------------------------------
// 全局函数：VBF_SetPartTexture()
// 函数描述：设置外观中某个部分的纹理
//-----------------------------------------------------------------------------
void VBF_GLAUX_EXPORT VBF_SetPartTexture(osg::StateSet* ss, CVBF_PartInfo& part);


#endif 
