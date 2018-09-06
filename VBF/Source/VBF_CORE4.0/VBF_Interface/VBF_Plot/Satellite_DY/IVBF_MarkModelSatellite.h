//*******************************************************************
// FileName：IVBF_MarkModelSatellite.h
// Function：实体模型：卫星（包括卫星模型、轨道、星下点轨迹）
// Author:   杜莹
// Date:     2013-12-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SATELLITE_H__
#define __IVBF_MARK_MODEL_SATELLITE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>


//----------------------------------------------------------------
// 定义枚举：EVBF_ORBIT_TYPE
// 接口描述：轨道类型
//----------------------------------------------------------------
enum EVBF_ORBIT_TYPE
{
    VBF_ORBIT_TWOBODY,
    VBF_ORBIT_J2,
    VBF_ORBIT_J4
};

//----------------------------------------------------------------
// 定义结构体：VBF_ORBIT_ELEMENTS
// 结构体描述：卫星轨道根数
//----------------------------------------------------------------
typedef struct _tagVBFOrbitElements
{
    std::string		strNoradNo;

    // 轨道的形状参数
    double			da;			// 半长轴（轨道的形状参数，单位：km）
    double			de;			// 偏心率（轨道的形状参数）

    // 轨道的位置参数
    double			dIncl;		// 轨道倾角（轨道与赤道面的二面角，单位：角度）
    double			dRAAN;		// 升交点赤经（春分点、地心、升交点三者在地心构成的夹角，单位：角度）
    double			dw;			// 近地点幅角（轨道近地点、地心、升交点三者在地心构成的夹角，单位：角度）

    // 卫星在轨道上的位置
    double			dTA;		// 过近地点时刻

    _tagVBFOrbitElements()
    {
            strNoradNo	= "0000";
            da			= 6878.145;
            de			= 0.0;
            dIncl		= 40.0;
            dRAAN		= 0.0;
            dw			= 0.0;
            dTA			= 0.0;
    }

    _tagVBFOrbitElements& operator=(const _tagVBFOrbitElements& src)
    {
            if(this==&src) return *this;

            strNoradNo	= src.strNoradNo;
            da			= src.da;
            de			= src.de;
            dIncl		= src.dIncl;
            dRAAN		= src.dRAAN;
            dw			= src.dw;
            dTA			= src.dTA;

            return *this;
    }

} VBF_ORBIT_ELEMENTS;


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSatellite
// 接口描述：卫星（包括卫星模型、轨道、星下点轨迹）
//--------------------------------------------------------------------
class IVBF_MarkModelSatellite : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSatellite() {}

    /* 设置/获取轨道参数
            参数：orbit		 -- 卫星轨道根数
            参数：dBeginTime -- 卫星开始仿真时间
            参数：dEndTime	 -- 卫星结束仿真时间
            参数：dTimeStep   -- 卫星仿真步长
    */
    virtual void SetOrbitParams(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep)=0;
    virtual void GetOrbitParams(VBF_ORBIT_ELEMENTS& orbit, double& dBeginTime, double& dEndTime, double& dTimeStep)=0;

    // 设置/获取卫星模型的完整文件名（含路径）
    // 如果文件类型为模型文件（如.3ds, .flt, .dae等），则卫星模型类型为VBF_MARK_MESH
    // 如果文件类型为图像文件（如.tga, .png, .bmp等），则卫星模型类型为VBF_MARK_RASTER
    virtual void               SetModelFileName(const std::string& strFileName)=0;
    virtual const std::string& GetModelFileName()=0;

    // 设置/获取卫星模型在配置文件MarkStyle.xml中的编码（该函数与上面的SetModelFileName()函数只能取后调用者）
    virtual void               SetModelCode(const std::string& strCode)=0;
    virtual const std::string& GetModelCode()=0;

    // 设置/获取卫星模型是否允许设置固定大小
    virtual void EnableModelFixedSizeInPixels(bool bEnable)=0;
    virtual bool IsModelFixedSizeInPixelsEnabled()=0;

    // 设置/获取卫星模型的固定大小 (单位：像素)
    virtual void  SetModelFixedSizeInPixels(float fFixedSize)=0;
    virtual float GetModelFixedSizeInPixels()=0;

    // 设置/获取卫星模型的缩放比
    virtual void SetModelScale(float fScaleX, float fScaleY, float fScaleZ)=0;
    virtual void GetModelScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

    // 设置/获取卫星模型的包围球是否可见（仅适用于卫星模型的类型为Mesh时，默认值为true）
    virtual void SetModelBoundingSphereVisible(bool bVisible)=0;
    virtual bool IsModelBoundingSphereVisible()=0;

    // 设置/获取卫星模型的包围球颜色（仅适用于卫星模型的类型为Mesh时，默认值为白色）
    virtual void              SetModelBoundingSphereColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetModelBoundingSphereColor()=0;

    // 设置/获取卫星模型的包围球在不同Lod级别下的配置信息（仅适用于卫星模型的类型为Mesh时）
    // 参数：nLod -- 包围球的Lod级别，只能取值0,1,2，Lod越小表示距离视点越远，包围球越简略
    //      fDistMin, fDistMax -- 该Lod级别下包围球的最小最大可见距离
    //      nNumSplitRow, nNumSplitCol -- 该Lod级别下包围球的横向和纵向分割数
    virtual void SetModelBoundingSphereInfo(int nLod, float fDistMin, float fDistMax, int nNumSplitRow, int nNumSplitCol)=0;
    virtual bool GetModelBoundingSphereInfo(int nLod, float& fDistMin, float& fDistMax, int& nNumSplitRow, int& nNumSplitCol)=0;

    // 设置/获取轨道是否可见（包括轨道线和轨道垂线，默认值为true）
    virtual void SetOrbitVisible(bool bVisible)=0;
    virtual bool IsOrbitVisible()=0;

    // 设置/获取轨道线的样式
    virtual void                 SetOrbitLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetOrbitLineStyle()=0;

    // 设置/获取轨道垂线是否可见（默认值为false）
    virtual void SetVertLineVisible(bool bVisible)=0;
    virtual bool IsVertLineVisible()=0;

    // 设置/获取轨道垂线的样式
    virtual void				 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

    // 设置/获取轨道垂线的间隔点数（即每隔几个点绘制一条垂线，默认值为5）
    virtual void SetNumVertLineInterval(int num)=0;
    virtual int  GetNumVertLineInterval()=0;

    // 设置/获取星下点轨迹是否可见（默认值为false）
    virtual void SetGroundTrackVisible(bool bVisible)=0;
    virtual bool IsGroundTrackVisible()=0;

    // 设置/获取星下点轨迹的样式
    virtual void                 SetGroundTrackLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetGroundTrackLineStyle()=0;

    // 设置/获取是否显示卫星信息
    virtual void SetInfoVisible(bool bVisible)=0;
    virtual bool IsInfoVisible()=0;

    // 设置/获取卫星信息的文本样式
    virtual void                 SetInfoTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetInfoTextStyle()=0;

    // 设置/获取卫星信息的背景框样式
    virtual void                      SetInfoFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetInfoFrameStyle()=0;

    // 设置卫星各形探测器
    virtual void SetDomeSensor(double dRadius, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetFrustumDomeSensor(double dRadius, double dAngleH, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetFrustumFlatSensor(double dRadius, double dAngleH, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetRingSensor(double dRadius, double dAngleV1, double dAngleV2, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    // 控制卫星探测器显隐
    virtual void SetSensorVisible(bool bVisible) = 0;
};


#endif
