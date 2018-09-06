#ifndef __VBF_3DPLOT_INNER_DATATYPES_JB_H__
#define __VBF_3DPLOT_INNER_DATATYPES_JB_H__


#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>
//------------------------------------------------------------
// 定义结构体：VBF_JBCONTOUR
// 结构体描述：符号中所有的图元组合（并设置宽度）后的轮廓
//------------------------------------------------------------
typedef struct _tagVBFJBContour : public ::CVBF_Referenced
{
    int						nIndexShape;	// 对应在m_vFillPolygons中的索引号
    bool					bFill;			// 是否填充
    bool					bInner;			// 是否为内轮廓
    osg::Vec4f				colorFill;		// 填充颜色

    // 所有轮廓点
    std::vector<osg::Vec3d>	vPoints;

    // 场景图中的几何体
    ref_ptr<osg::Geometry>	piGeomSerifInner;	// 衬线内部
    ref_ptr<osg::Geometry>	piGeomSerifOuter;	// 衬线外部
    ref_ptr<osg::Geometry>	piGeomsFill[2];		// 填充部分（两遍：第一遍的z值为m_fThickness，第二遍的z值为0.0）

    _tagVBFJBContour()
    {
        nIndexShape	= -1;
        bFill		= false;
        bInner		= true;
        colorFill	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);

        vPoints.clear();
    }

    // 获取点数
    int GetNumPoints() const  { return (int)vPoints.size(); }

} VBF_JBCONTOUR;


//------------------------------------------------------------
// 符号中需要填充图元的原始几何数据，仅用于判断轮廓是否填充
//------------------------------------------------------------
class CVBF_JbPolygon : public ::CVBF_Referenced
{
public:
    CVBF_Shape*         pShape;	// 对应军表库中的图形（外部指针）
    osg::Vec4f          color;
    vector<osg::Vec3d>  vPoints;

    // 颜色是否失效
    bool                bDirtyColor;
    CVBF_JbPolygon()
    {
        pShape = NULL;
        color  = osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
        vPoints.clear();
        bDirtyColor = false;
    }

};

//------------------------------------------------------------
// 定义结构体：VBF_JBTEXTINFO
// 结构体描述：点状军标符号中各个部分的文本信息
//------------------------------------------------------------
typedef struct _tagVBFJBTextInfo : public ::CVBF_Referenced
{
    std::string				strText;		// 文本内容
    VBF_TEXTSTYLE			style;			// 文本样式
    void*                   pShape;			// 对应军表库中的图形（外部指针）
    ref_ptr<osgText::Text>	piText;			// 场景图中的Drawable

    // 参数是否失效
    bool                    bDirtyText;     // 文本内容是否失效
    bool                    bDirtyStyle;    // 文本样式是否失效

    _tagVBFJBTextInfo()
    {
        strText     = "";
        pShape      = NULL;

        bDirtyText  = false;
        bDirtyStyle = false;
        style.nFontResX = 120;
        style.nFontResY = 120;
    }

} VBF_JBTEXTINFO;




#endif
