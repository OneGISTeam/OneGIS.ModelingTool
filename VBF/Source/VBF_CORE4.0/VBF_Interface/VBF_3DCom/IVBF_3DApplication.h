//***************************************************************************************
// FileName：IVBF_3DApplication.h
// Function：三维应用层接口，主要用于应用层集成的功能
// Author:   
// Date:     2012-4-16
//***************************************************************************************
#ifndef __IVBF_3DAPPLICATION_H__
#define __IVBF_3DAPPLICATION_H__

// 定义该组件的ID号
const char VBF_COMPONENT_3DAPPLICATION[]			= "Component: 3DApplication";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DAPPLICATION[]			= "三维应用层";

// 定义命令ID号

#include <string>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_Camera.h>

class IVBF_3DApplication : public CVBF_Referenced
{
public: 	
	virtual ~IVBF_3DApplication() {}
    virtual std::string ExecuteScript( std::string jstrScript)=0;
    virtual void LocateSpaceObject(int noPlanets)=0;
    virtual void SnapCamera(const std::string& sFn)=0;
    virtual void SnapCameraWithUI(const std::string& sFn)=0;
    virtual void RecordVideoNoUI(const std::string& sFn)=0; // 屏幕录制（不带UI）
    virtual void RecordVideoWithUI(const std::string& sFn)=0; // 屏幕录制（带UI）
    virtual void StopRecordVideo()=0;  // 停止屏幕录制

};

#endif





















