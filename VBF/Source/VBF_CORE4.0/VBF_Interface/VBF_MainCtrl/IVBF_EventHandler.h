//***************************************************************************************
// FileName：IVBF_EventHandler.h
// Function：鼠标、键盘等与GUI的交互事件处理入口，系统主控调用每个组件的该接口来完成交互事件的处理
// Author:   杜莹
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

    // 处理事件入口，与GUI的交互的主接口，如果事件被处理过了，返回true。
    // 参数：aa -- 接收GUI的更新
    //      ea  -- 向GUI发送请求
    virtual bool OnEvent(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa, osg::CVBF_Object* pObj, osg::NodeVisitor* nv)=0;
};



#endif
