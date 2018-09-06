//*******************************************************************
// FileName：IVBF_MarkModelAirSpace.h
// Function：实体模型：空域（系统内部沿大圆线插值）
// Author:   杜莹
// Date:     2014-08-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_AIRSPACE_H__
#define __IVBF_MARK_MODEL_AIRSPACE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelAirSpace
// 接口描述：空域
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpace : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelAirSpace() {}

    // 设置/获取墙面的渐变色
    virtual void SetColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
    virtual void GetColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// 设置/获取墙面纹理的透明度（值域为[0.0, 1.0]，默认值为1.0）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

    // 设置/获取墙的顶部曲线是否可见
    virtual void SetLineVisible(bool bVisible)=0;
    virtual bool IsLineVisible()=0;

    // 设置/获取墙的顶部曲线样式
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // 清空
    virtual void Clear()=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelAirSpacePolyline
// 接口描述：折线形空域
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpacePolyline : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpacePolyline() {}

    // 添加一条折线
    // 参数：vPointsGeo -- 地理坐标中前两维表示经度和纬度，第三维表示墙顶部的高程值，第四维表示墙底部的高程值
    // 参数：nNumInter -- 相邻两点之间的插值点数， <0表示需要系统自动插值，=0表示不需要插值，>0表示按用户指定的点数进行插值
    // 参数：pImage -- 折线所在墙面的纹理图像（可以为空，一旦设置，将忽略SetColor()函数）
    // 参数：nNumTexRows, nNumTexCols -- 墙面纹理文件在横向和纵向的重复次数
    virtual void AddLine(const std::vector<osg::Vec4d>& vPointsGeo, int nNumInter=5,
                         osg::Image* pImage=NULL, int nNumTexRows=1, int nNumTexCols=1)=0;

    // 获取用户所添加的第n条折线的信息
    virtual bool GetLine(int nIndex, std::vector<osg::Vec4d>& vPointsGeo, int& nNumInter,
                         osg::Image*& pImage, int& nNumTexRows, int& nNumTexCols)=0;

    // 获取用户所添加的折线总数
    virtual int GetNumLines()=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelAirSpaceArc
// 接口描述：弧段形空域
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpaceArc : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpaceArc() {}

    // 设置/获取空域形状参数
    // 参数：ptCenterGeo -- 空域顶部所在的圆心（地理坐标）
    //      fRadius     -- 半径（单位：米）
    //      fAngleStart, fAngleEnd -- 起始和终止角度（与正北方向的夹角，单位：角度）
    //      fTheta      -- 圆上相邻两点的角度间隔（单位：角度，值域为[1, 30]）
    virtual void SetTess(const osg::Vec3d& ptCenterGeo, float fRadius, float fAngleStart, float fAngleEnd, float fTheta=5.0)=0;
    virtual void GetTess(osg::Vec3d& ptCenterGeo, float& fRadius, float& fAngleStart, float& fAngleEnd, float& fTheta)=0;

    // 设置/获取空域的整体高度，该高度值不能大于圆心点的高程值
    virtual void   SetHeight(double dHeight)=0;
    virtual double GetHeight()=0;

	// 设置/获取墙面纹理图像指针（一旦调用该函数，将忽略SetColor()函数）
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取墙面纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelAirSpaceCircle
// 接口描述：圆形空域
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpaceCircle : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpaceCircle() {}

    // 设置/获取空域形状参数
    // 参数：ptCenterGeo -- 顶部圆心（地理坐标）
    //      fRadius     -- 半径（单位：米）
    //      fTheta      -- 圆上相邻两点的角度间隔（单位：角度，值域为[1, 30]）
    virtual void SetTess(const osg::Vec3d& ptCenterGeo, float fRadius, float fTheta=5.0)=0;
    virtual void GetTess(osg::Vec3d& ptCenterGeo, float& fRadius, float& fTheta)=0;

    // 设置/获取空域的整体高度，该高度值不能大于顶部圆心点的高程值
    virtual void   SetHeight(double dHeight)=0;
    virtual double GetHeight()=0;

	// 设置/获取墙面纹理图像指针（一旦调用该函数，将忽略SetColor()函数）
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取墙面纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;
};


#endif 
