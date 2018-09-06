#ifndef OSGGA_GUIEVENTHANDLER
#define OSGGA_GUIEVENTHANDLER 1

#include <vector>

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Base/VBF_ApplicationUsage.h>

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>



namespace osgGA{

/**
事件处理器：向开发者提供了窗体系统的GUI事件处理的接口。GUI事件（GUIEvent）是由GUIEventAdapter提供的。
		   事件处理器使用GUIEventAdapter来接收更新，还可以使用GUIActionAdapter向GUI系统发送请求，以实现一些特定的操作。

	例如：
	TrackballManipulator类（继承自GUIEventHandler）以GUIEventAdapter实例的形式接收鼠标事件的更新。
	鼠标事件的解析由handle完成，并可实现"抛出"操作（抛出，是指用户按下键拖动模型并突然松开，以实现模型的持续旋转或移动）。
	解析事件时，将发送请求到GUI系统（使用GUIActionAdapter），启动定时器并使自己被重复调用，以计算新的模型方向或者位置数据。 

*/
class OSGGA_EXPORT GUIEventHandler : public osg::NodeCallback, public osg::Drawable::EventCallback
{
public:
        GUIEventHandler()
		{
			m_nIgnoreHandledEventsMask = GUIEventAdapter::NONE; 
            m_nLevel = 1000;
		}
        GUIEventHandler(const GUIEventHandler& eh,const osg::CopyOp& copyop): osg::NodeCallback(eh, copyop), osg::Drawable::EventCallback(eh, copyop)          
		{
			m_nIgnoreHandledEventsMask = eh.m_nIgnoreHandledEventsMask;
            m_nLevel = eh.m_nLevel;
		}

        META_Object(osgGA,GUIEventHandler);

        // 实现NodeCallback接口
        virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);


        // 处理事件，与GUI的交互的主接口，如果事件被处理过了，返回true。 GUIEventAdapter用于接收GUI的更新；GUIActionAdapter用于向GUI发送请求
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa, osg::CVBF_Object*, osg::NodeVisitor*) { return handle(ea,aa); }

        /** 处理还没有被处理的事件或者已经处理但没有设置IgnoreHandledEventsMask标志的事件。
          * 此函数是内联函数，不要重载。可以重载handle(,,,)函数 */
        inline bool handleWithCheckAgainstIgnoreHandledEventsMask(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa, osg::CVBF_Object* object, osg::NodeVisitor* nv)
        {
            if (!ea.IsHandled() ||  (ea.getEventType() & m_nIgnoreHandledEventsMask )==0)
            {
				// 当handle 函数返回值为true 时，表示此事件已经处理完毕，其它事件处理器不会再理会这个事件；返回false则继续交由后继的GUIEventHandler对象处理。
                bool bHandled = handle(ea,aa,object,nv);
                if (bHandled) ea.setHandled(true);
                return bHandled;
            }
            else return false;         
        }

        inline bool handleWithCheckAgainstIgnoreHandledEventsMask(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa)
        {
            if (!ea.IsHandled() || (ea.getEventType() & m_nIgnoreHandledEventsMask)==0)
            {
                bool handled = handle(ea,aa);
                if (handled) ea.setHandled(true);
                return handled;
            }
            else return false;      
        }

        /** Deprecated, Handle events, return true if handled, false otherwise. */
        virtual bool handle(const GUIEventAdapter&,::IVBF_GUIActionAdapter&) { return false; }
   
        
 		// 获取鼠标和键盘的使用
        virtual void GetUsage(ApplicationUsage&) const {}

		// 设置如果被处理过则被忽略的事件的掩码
        void setIgnoreHandledEventsMask(unsigned int mask) { m_nIgnoreHandledEventsMask = mask; }
        unsigned int getIgnoreHandledEventsMask() const { return m_nIgnoreHandledEventsMask; };


        unsigned int GetLevel() { return m_nLevel; }

		virtual void event(osg::NodeVisitor* nv, osg::Drawable* drawable);

protected:
		// 如果某个事件只希望被处理一次，则设置该标志就可以禁止后续处理器处理此类事件
		unsigned int m_nIgnoreHandledEventsMask; // EventType

        unsigned int m_nLevel; // 优先级，数字越小优先级越高

};

}


inline bool IsLButtonDown(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::PUSH && ea.getButton()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
}
inline bool IsLButtonUp(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::RELEASE && ea.getButton()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
}
inline bool IsRButtonDown(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::PUSH && ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON);
}
inline bool IsRButtonUp(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::RELEASE && ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON);
}
inline bool IsMouseMove(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::MOVE);
}
inline bool IsMouseScroll(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::SCROLL);
}
inline bool IsScrollUp(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getScrollingMotion()==osgGA::GUIEventAdapter::SCROLL_UP);
}
inline bool IsKeyDown(const osgGA::GUIEventAdapter& ea)
{
    return (ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN);
}
#endif
