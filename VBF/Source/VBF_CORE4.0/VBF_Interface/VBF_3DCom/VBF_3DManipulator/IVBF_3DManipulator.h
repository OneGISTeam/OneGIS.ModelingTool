//***************************************************************************************
// FileName：IVBF_3DDisplay.h
// Function：三维显示控制接口，主要用于获取和显示参数有关的信息和对场景进行控制
// Author:   杜莹
// Date:     2006-4-22
//***************************************************************************************
#ifndef __IVBF_3DDISPLAY_H__11
#define __IVBF_3DDISPLAY_H__11


#include <Types/Vec3d>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>
#include <VBF_Display/VBF_Manipulator/IVBF_DriveManipulator.h>
#include <VBF_Display/VBF_Manipulator/IVBF_TrackManipulator.h>


// 定义该组件的ID号
const char VBF_COMPONENT_3DMANIPULATOR[]			= "Component: 3DManipulator";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DMANIPULATOR[]			= "三维相机操作器管理";

// 定义3D模块中消息的ID号
extern const char VBF_MESSAGE_3DVIEWPORT_INITED[];//		= "Message: 3DViewport Inited";
extern const char VBF_MESSAGE_3DVIEWPORT_RESIZED[];//		= "Message: 3DViewport Resized";




class IVBF_View;

class IVBF_3DManipulator
{
public: 	
	virtual ~IVBF_3DManipulator() {}

public:
	// 切换驾驶操作器
	virtual IVBF_DriveManipulator* SetAndGetDriveManipulator(int nTypeDriveManip) = 0;
	
	// 切换跟踪操作器
	virtual IVBF_TrackManipulator* SetAndGetTrackManipulator(IVBF_TrackManipulator::ETrackManip nTypeTrackManip) = 0;



    // 设置/获取当前视点
    virtual void SetViewpoint( const CVBF_Viewpoint& vp, double duration_s=0.0, bool bAutoRotate=false ,IVBF_ManipulatorCB* pCB = NULL) = 0;
    virtual CVBF_Viewpoint GetViewpoint()=0;

    // 定位到指定坐标范围处
    // 参数：dL0, dB0, dL1, dB1 -- 地理坐标的最小经纬度（单位：度）
    //     dHeading -- 定位后的航向角（单位：角度）
    //     dPitch   -- 定位后的俯仰角（单位：角度）
    //     dDuration -- 定位所需要的时间（单位：秒）
    //     bAutoRotate -- 定位后是否自动旋转
    virtual void Locate(double dL0, double dB0, double dL1, double dB1, double dHeading=0.0,
                        double dPitch=-90.0, double dDuration=0.0, bool bAutoRotate=false, IVBF_ManipulatorCB* pCB=NULL)=0;

    virtual void  StartAutoAnimPath( const char* szName )=0;
    virtual void  EndAutoAnimPath()=0;
//!!
    /*
	// 获取当前视点的世界坐标
	virtual const osg::Vec3d& GetEyePtInWorld()=0;

	virtual double GetEyeHeight()=0;


	virtual double  GetAngleH()=0;				// 获取水平视角 (即方位角，单位：角度)
	virtual double  GetAngleV()=0;				// 获取垂直视角 (单位：角度，水平为0，向上为-90，向下为90)

    // 获取显示分辨率(米/像素)、比例尺
    virtual double GetResolution(IVBF_View* pIView=NULL)=0;
    virtual double GetScale(IVBF_View* pIView=NULL,unsigned int DPI = 96)=0;
    virtual void   SetScale(double dL,double dB,double dScale,IVBF_View* pIView=NULL,unsigned int DPI=96)=0;

    // 获取显示分辨率的向量(米/像素)，用法为：float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;
*/
    // 保存当前视点到xml文件中，返回值为false表示保存失败
    // 参数：strXmlFileName -- xml文件名（完整路径）
    //      strViewpointName -- 视点的名称，可以为空字符串
    //      bAppend        -- 如果文件已存在，是否采用追加模式
    virtual bool SaveViewpoint(const std::string& strXmlFileName, const std::string& strViewpointName, bool bAppend=true)=0;

    // 从视点xml文件中获取某个视点，返回值为false表示获取失败
    // 参数：strXmlFileName -- xml文件名（完整路径）
    //      strViewpointName -- 视点的名称，可以为空字符串
    virtual bool GetViewpointFromFile(const std::string& strXmlFileName, const std::string& strViewpointName, CVBF_Viewpoint& viewpoint)=0;
};


#endif





















