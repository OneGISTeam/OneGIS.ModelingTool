//***************************************************************************************
// FileName��IVBF_3DMainCtrl.h
// Function��ͼ�μ��ɿ�ܽӿڡ�
//           �ýӿ����ϵͳ3D���ؽӿ����ݣ�����ؼ�ע�ᡢ����ַ����¼����������
// Author:   ��Ө
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_3DMAIN_CTRL_H__
#define __IVBF_3DMAIN_CTRL_H__

#include "VBF_Macros.h"
#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <string>

// ����������ID��
const char VBF_COMPONENT_3DMAIN[]	= "Component: 3DMain";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DMAIN[]	    =	"��ά����";
const char VBF_INTERFACE_3D_MAIN_MAP[]	=	"��ά��ͼ";
// ������Ϣ
const char VBF_MESSAGE_VIEW_ADDED[]	      = "Message: A View Added";	   // �����һ��osgView, nValue=ViewCount, pValue=CVBF_View*
const char VBF_MESSAGE_3DCAMERA_CHANGED[] = "Message: 3DCamera Changed";   // �����λ�ú���̬�����˱仯
const char VBF_MESSAGE_ACTIVEMAP_CHANGED[]= "Message: Active Map Changed"; // ����ĵ�ͼ�����򣩷����˱仯
const char VBF_MESSAGE_EARTHMAP_CHANGED[]= "Message: Earth Map Changed"; // ����ĵ�ͼ�����˱仯

class IVBF_View;
class IVBF_Viewer;
class IVBF_Log;
class IVBF_Map;

//----------------------------------------------------
// ����ӿڣ�IVBF_3DMainCtrl
// �ӿ�������3Dͼ�μ��ɿ�ܽӿ�
//----------------------------------------------------
class IVBF_3DMainCtrl : public IVBF_MainCtrl
{
public:
	virtual ~IVBF_3DMainCtrl() {}

	// ��ȡ��Viewer
	virtual IVBF_Viewer* GetViewer()=0;

	// ���/��ȡ3D��ͼָ��
	virtual bool	   AddView(IVBF_View* pView)=0;
    virtual void	   RemoveView(IVBF_View* pView)=0;
	virtual int		   GetNumViews()=0;
	virtual IVBF_View* GetView(int nIndex)=0;
    virtual osg::IVBF_SGNodeGroup* GetSceneGraph()=0;
    virtual osg::IVBF_SGNodeGroup* GetEarthNode()=0;
    virtual IVBF_Map* GetMainMap()=0;
    virtual void LoadMap(std::string strMapFileName)=0;
	// ��ʼִ����ѭ��
	virtual int Start()=0;

	// ��ȡ��־�ӿڵ�ָ�룬�Ա�������������д����־��Ϣ (�������Ϣ)
	virtual IVBF_Log* GetLogPtr()=0;

};



#endif
