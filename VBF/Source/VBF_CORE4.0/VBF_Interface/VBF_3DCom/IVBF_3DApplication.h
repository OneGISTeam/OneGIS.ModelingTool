//***************************************************************************************
// FileName��IVBF_3DApplication.h
// Function����άӦ�ò�ӿڣ���Ҫ����Ӧ�ò㼯�ɵĹ���
// Author:   
// Date:     2012-4-16
//***************************************************************************************
#ifndef __IVBF_3DAPPLICATION_H__
#define __IVBF_3DAPPLICATION_H__

// ����������ID��
const char VBF_COMPONENT_3DAPPLICATION[]			= "Component: 3DApplication";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DAPPLICATION[]			= "��άӦ�ò�";

// ��������ID��

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
    virtual void RecordVideoNoUI(const std::string& sFn)=0; // ��Ļ¼�ƣ�����UI��
    virtual void RecordVideoWithUI(const std::string& sFn)=0; // ��Ļ¼�ƣ���UI��
    virtual void StopRecordVideo()=0;  // ֹͣ��Ļ¼��

};

#endif





















