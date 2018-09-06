//***************************************************************************************
// FileName：IVBF_3DDisplay.h
// Function：三维显示控制接口，主要用于获取和显示参数有关的信息和对场景进行控制
// Author:   杜莹
// Date:     2006-4-22
//***************************************************************************************
#ifndef __IVBF_3DDISPLAY_H__
#define __IVBF_3DDISPLAY_H__


#include <Types/Vec3d>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>
#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

// 定义该组件的ID号
const char VBF_COMPONENT_3DDISPLAY[]			= "Component: 3DDisplay";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DDISPLAY[]			= "三维显示控制管理";

// 定义3D模块中消息的ID号
const char VBF_MESSAGE_3DVIEWPORT_INITED[]		= "Message: 3DViewport Inited";
const char VBF_MESSAGE_3DVIEWPORT_RESIZED[]		= "Message: 3DViewport Resized";



//-----------------------------------------------------------------------------
// 枚举的各种操作器方式
//-----------------------------------------------------------------------------
enum VBF_MANIPULATOR_TYPE
{
	// 地形操作器
	VBF_MANIP_EARTH_VBF = 0,
	VBF_MANIP_EARTH_FE,

	// 全局操作器
	VBF_MANIP_TRACKBALL,
	VBF_MANIP_ANIMATION, 
    VBF_MANIP_SPHERICAL,

	// 驾驶操作器
	VBF_MANIP_DRIVE,
	VBF_MANIP_FIRST_PERSON,
	VBF_MAINP_FLY,

	// 跟踪
	VBF_MANIP_TRACK_FIXA,
	VBF_MANIP_TRACK_FIXR,
	VBF_MAINP_TRACK_NODE,

	// 锁定操作器，即可作跟踪，也可作驾驶
	VBF_MANIP_FE_LOCK,

	// 室内漫游操作器
	VBF_MANIP_INDOOR_ROAMING
};


class IVBF_View;
class IVBF_AutoAnimCompleteCB : public CVBF_Referenced
{
public:
    virtual void completed() = 0;
};

class IVBF_CameraManipulatorChangeCB : public CVBF_Referenced
{
public:

	virtual void CameraManiChanged(IVBF_CameraManipulator* manipulator) = 0;
};


class IVBF_3DDisplay
{
public: 	
	virtual ~IVBF_3DDisplay() {}

public:

	// 选择操作器
 	virtual IVBF_CameraManipulator* SetAndGetManipulator(VBF_MANIPULATOR_TYPE manipulatorType)= 0;
 	virtual VBF_MANIPULATOR_TYPE GetManipulatorType()=0;
    virtual void SetCameraManiChangeCallback(IVBF_CameraManipulatorChangeCB*) = 0;
	// 获取操作器
	virtual IVBF_CameraManipulator* GetManipulator(VBF_MANIPULATOR_TYPE manipulatorType)= 0;

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





















