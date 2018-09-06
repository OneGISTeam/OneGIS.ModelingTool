//***************************************************************************************
// FileName：IVBF_3DMarine.h
// Function：3D海洋信息接口
// Author:   杜莹
// Date:     2016-10-12
//***************************************************************************************

#ifndef __IVBF_3DMRINE_H__
#define __IVBF_3DMRINE_H__

#include <VBF_Base/VBF_Referenced.h>
#include <Types/Vec3d>
#include <vector>
#include <VBF_Aux/VBF_GLAux/VBF_GraphicsAppearance.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCylinderS.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


// 定义该组件的ID号
const char VBF_COMPONENT_3DMARINE[]		= "Component: 3DMarine";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DMARINE[]		= "三维海洋信息接口";


//-------------------------------------------------------------------------
// 三维剖面图，实际上是一个圆柱体
//-------------------------------------------------------------------------
class IVBF_3DSection : public CVBF_Referenced
{
public:
    virtual ~IVBF_3DSection() {}

    // 获取ID号
    virtual const std::string& GetID()=0;

    // 设置/获取圆柱体的圆周分割数，默认值为36
    virtual void SetNumSplit(int nNumSplit)=0;
    virtual int  GetNumSplit()=0;

    // 设置/获取圆柱体的顶面圆环分割数，默认值为6
    virtual void SetNumTopSplit(int nNumSplit)=0;
    virtual int  GetNumTopSplit()=0;

    // 设置高度数组：上边、下边、顶部
    virtual void SetTopEdgeHeights(const std::vector<double>& vHeight)=0;       // 要求：vHeight.size()=GetNumSplit()+1
    virtual void SetBottomEdgeHeights(const std::vector<double>& vHeight)=0;    // 要求：vHeight.size()=GetNumSplit()+1
    virtual void SetTopHeights(const std::vector<double>& vHeight)=0;           // 要求：vHeight.size()=GetNumTopSplit()*(GetNumSplit()+1)

    // 获取外观
    virtual IVBF_GraphicsAppearance* GetAppearance()=0;
};


//-----------------------------------------------------------------------------------------------
// 三维影像叠加图，实际上是多个带有一定间距的长方体图层上下叠加到一起，可用于表现同一地区不同时段的影像
//-----------------------------------------------------------------------------------------------
class IVBF_3DOverlap : public CVBF_Referenced
{
public:
    virtual ~IVBF_3DOverlap() {}

    // 添加/删除一个图层（图层名不允许重复）
    virtual void AddLayer(const std::string& strLayerName, osg::Image* pImage)=0;
	virtual void InsertLayer(int nIndex, const std::string& strLayerName, osg::Image* pImage)=0;
	virtual void RemoveLayer(const std::string& strLayerName)=0;

	// 获取叠加的图层总数
	virtual int GetNumLayers()=0;

    // 获取ID号
    virtual const std::string& GetID()=0;

	// 设置/获取叠加图的地理坐标范围
    virtual void SetGeoRange(double dL0, double dL1, double dB0, double dB1)=0;
	virtual void GetGeoRange(double& dL0, double& dL1, double& dB0, double& dB1)=0;

	// 通过读取tfw配准文件（角点/中心点），设置地理坐标和尺寸
	virtual bool SetGeoRangeByTfwCorner(const std::string& strFileName)=0;
	virtual bool SetGeoRangeByTfwCenter(const std::string& strFileName)=0;

	// 设置/获取相邻两层之间的垂直间隔（单位：米）
    virtual void  SetVertInterval(float fInterval)=0;
	virtual float GetVertInterval()=0;
	
	// 设置/获取每层长方体的厚度（该厚度为相对值，相对于垂直间隔，值域为[0, 0.5]）
    virtual void  SetLayerThicknessRatio(float fRatio)=0;
	virtual float GetLayerThicknessRatio()=0;

	// 设置/获取每层长方体的侧面颜色（单位：米）
    virtual void              SetSideColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetSideColor()=0;

	// 设置/获取该叠加图是否可见
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;

	// 获取该叠加图是否激活（只有被激活才可显示图例并可查看每一层）
	virtual bool IsActive()=0;
};

//-------------------------------------------------------------------------------
// 3D海洋信息接口
//-------------------------------------------------------------------------------
class IVBF_3DMarine : public CVBF_Referenced
{
public:	
    virtual ~IVBF_3DMarine() {}


	//---------------- 与圆柱形剖面图有关的函数 ------------------------------

    // 创建一个剖面图，并设置唯一ID号
    virtual IVBF_3DSection* CreateSection(const std::string& strID)=0;

    // 向子窗口中添加/移除一个剖面图
    virtual void AddSection(IVBF_3DSection* pISection)=0;
    virtual void RemoveSection(IVBF_3DSection* pISection)=0;
    virtual void RemoveSection(const std::string& strID)=0;

    // 获取已经添加的剖面图，如果尚未添加或已经被移除，返回NULL
    virtual IVBF_3DSection* GetSection(const std::string& strID)=0;

    // 设置/获取剖面图圆柱体底面长短轴的半径，二者不相等表示椭圆柱体，二者相等表示圆柱体
    virtual void SetSectionRadius(float fRadiusX, float fRadiusY)=0;
    virtual void GetSectionRadius(float& fRadiusX, float& fRadiusY)=0;

    // 设置/获取剖面图圆柱体高度
    virtual void  SetSectionHeight(float fHeight)=0;
    virtual float GetSectionHeight()=0;

    // 注意：以下子窗口均指剖面图所在的子窗口

    // 设置/获取子窗口是否可见（默认为true）
    virtual void SetSubViewVisible(bool bVisible)=0;
    virtual bool IsSubViewVisible()=0;

    // 设置/获取子窗口的标题
    virtual void SetSubViewTitle(const std::string& strTitle)=0;
    virtual const std::string& GetSubViewTitle()=0;

    // 设置/获取子窗口的尺寸（单位：像素）
    virtual void SetSubViewSize(int nSizeX, int nSizeY)=0;
    virtual void GetSubViewSize(int& nSizeX, int& nSizeY)=0;

    // 设置/获取子窗口的位置（单位：像素，原点位于视口左下角）
    virtual void SetSubViewPos(float x, float y)=0;
    virtual void GetSubViewPos(float& x, float& y)=0;

    // 设置/获取子窗口的背景色
    virtual void SetSubViewBackColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetSubViewBackColor()=0;


	//---------------- 与影像叠加图有关的函数 ------------------------------

    // 创建一个叠加图，并设置唯一ID号
    virtual IVBF_3DOverlap* CreateOverlap(const std::string& strID)=0;

    // 向子窗口中添加/移除一个叠加图
    virtual void AddOverlap(IVBF_3DOverlap* pIOverlap)=0;
    virtual void RemoveOverlap(IVBF_3DOverlap* pIOverlap)=0;
    virtual void RemoveOverlap(const std::string& strID)=0;

    // 获取已经添加的叠加图，如果尚未添加或已经被移除，返回NULL
    virtual IVBF_3DOverlap* GetOverlap(const std::string& strID)=0;

	// 设置/获取当前激活的叠加图（只有被激活的叠加图才可显示图例并可查看每一层）
	virtual void SetActiveOverlap(const std::string& strID)=0;
	virtual std::string GetActiveOverlap()=0;
};


#endif 
