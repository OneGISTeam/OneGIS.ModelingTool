//***************************************************************************************
// FileName��IVBF_EventHandler.h
// Function����ꡢ���̵���GUI�Ľ����¼�������ڣ�ϵͳ���ص���ÿ������ĸýӿ�����ɽ����¼��Ĵ���
// Author:   ��Ө
// Date:     2014-08-27
//***************************************************************************************

#ifndef __IVBF_EVENT_HANDLER_H__
#define __IVBF_EVENT_HANDLER_H__


#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>


class IVBF_EventHandler
{
public:
    virtual ~IVBF_EventHandler() {}

public:

    // �����¼���ڣ���GUI�Ľ��������ӿڣ�����¼���������ˣ�����true��
    // ������aa -- ����GUI�ĸ���
    //      ea  -- ��GUI��������
    virtual bool OnEvent(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa, osg::CVBF_Object* pObj, osg::NodeVisitor* nv)=0;
};



#endif
