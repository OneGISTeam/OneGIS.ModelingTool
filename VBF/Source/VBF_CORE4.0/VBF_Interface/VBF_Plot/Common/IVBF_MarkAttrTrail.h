//*******************************************************************
// FileName：IVBF_MarkAttrTrail.h
// Function：模型属性接口：模型的运动轨迹（折线形/条带形）
// Author:   杜莹
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_H__
#define __IVBF_MARK_ATTR_TRAIL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


// 定义工具ID号
const char VBF_TOOL_MARKATTR_QUERY_TRAILPOINT[]	 = "Tool: Query Mark Attr of Trail Point";		// 属性查询：轨迹点信息



//--------------------------------------------------------------------
// 定义枚举：EVBF_TRAIL_STYLE
// 接口描述：定义轨迹的绘制方式，可以是如下枚举值的单个
//--------------------------------------------------------------------
enum EVBF_TRAIL_STYLE
{
    VBF_TRAIL_STYLE_POINT		= 0x01,		// 只绘制轨迹点
    VBF_TRAIL_STYLE_LINE		= 0x02,		// 只绘制轨迹线
    VBF_TRAIL_STYLE_COMPOSITE	= (VBF_TRAIL_STYLE_POINT | VBF_TRAIL_STYLE_LINE)	// 同时绘制轨迹点和轨迹线
};


class IVBF_MarkAttrTrail : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrTrail() {}

    // 设置/获取轨迹的绘制方式
    virtual void             SetRenderStyle(EVBF_TRAIL_STYLE nStyle)=0;
    virtual EVBF_TRAIL_STYLE GetRenderStyle()=0;

    // 设置/获取轨迹点的样式
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

    // 设置/获取轨迹线中需要保留的点数（这些点记录在内存中，不一定全部显示）
    // 注意：该点数不能小于SetNumPointsVisible()函数中设置的点数
    virtual void SetNumPointsRetained(int num)=0;
    virtual int  GetNumPointsRetained()=0;

    // 设置/获取轨迹线中参与绘制的点数
    virtual void SetNumPointsVisible(int num)=0;
    virtual int  GetNumPointsVisible()=0;

    // 设置/获取轨迹点查询信息的背景框是可见（默认值为true）
    virtual void SetQueryFrameVisible(bool bVisible)=0;
    virtual bool IsQueryFrameVisible()=0;

    // 设置/获取轨迹点查询信息的背景框样式
    virtual void                      SetQueryFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetQueryFrameStyle()=0;

    // 设置/获取轨迹点查询信息的文本样式
    virtual void                 SetQueryTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetQueryTextStyle()=0;

    // 判断是否包含指定的鼠标位置（仅限于判断轨迹点，不判断轨迹线/轨迹条）
    // 如果包含，返回该轨迹点的世界坐标和信息
    virtual bool Contains(float x, float y, osg::Vec3d& ptWorld, std::string& strInfo)=0;

	// 清空轨迹
	// 参数：bClearImmediately -- 是否立即删除，只有在Update()函数中才能设该参数为true，否则会导致绘制线程出错
	virtual void Clear(bool bClearImmediately=false)=0;
};


#endif 
