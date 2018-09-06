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
�¼����������򿪷����ṩ�˴���ϵͳ��GUI�¼�����Ľӿڡ�GUI�¼���GUIEvent������GUIEventAdapter�ṩ�ġ�
		   �¼�������ʹ��GUIEventAdapter�����ո��£�������ʹ��GUIActionAdapter��GUIϵͳ����������ʵ��һЩ�ض��Ĳ�����

	���磺
	TrackballManipulator�ࣨ�̳���GUIEventHandler����GUIEventAdapterʵ������ʽ��������¼��ĸ��¡�
	����¼��Ľ�����handle��ɣ�����ʵ��"�׳�"�������׳�����ָ�û����¼��϶�ģ�Ͳ�ͻȻ�ɿ�����ʵ��ģ�͵ĳ�����ת���ƶ�����
	�����¼�ʱ������������GUIϵͳ��ʹ��GUIActionAdapter����������ʱ����ʹ�Լ����ظ����ã��Լ����µ�ģ�ͷ������λ�����ݡ� 

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

        // ʵ��NodeCallback�ӿ�
        virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);


        // �����¼�����GUI�Ľ��������ӿڣ�����¼���������ˣ�����true�� GUIEventAdapter���ڽ���GUI�ĸ��£�GUIActionAdapter������GUI��������
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa, osg::CVBF_Object*, osg::NodeVisitor*) { return handle(ea,aa); }

        /** ����û�б�������¼������Ѿ�����û������IgnoreHandledEventsMask��־���¼���
          * �˺�����������������Ҫ���ء���������handle(,,,)���� */
        inline bool handleWithCheckAgainstIgnoreHandledEventsMask(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa, osg::CVBF_Object* object, osg::NodeVisitor* nv)
        {
            if (!ea.IsHandled() ||  (ea.getEventType() & m_nIgnoreHandledEventsMask )==0)
            {
				// ��handle ��������ֵΪtrue ʱ����ʾ���¼��Ѿ�������ϣ������¼��������������������¼�������false��������ɺ�̵�GUIEventHandler������
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
   
        
 		// ��ȡ���ͼ��̵�ʹ��
        virtual void GetUsage(ApplicationUsage&) const {}

		// ���������������򱻺��Ե��¼�������
        void setIgnoreHandledEventsMask(unsigned int mask) { m_nIgnoreHandledEventsMask = mask; }
        unsigned int getIgnoreHandledEventsMask() const { return m_nIgnoreHandledEventsMask; };


        unsigned int GetLevel() { return m_nLevel; }

		virtual void event(osg::NodeVisitor* nv, osg::Drawable* drawable);

protected:
		// ���ĳ���¼�ֻϣ��������һ�Σ������øñ�־�Ϳ��Խ�ֹ������������������¼�
		unsigned int m_nIgnoreHandledEventsMask; // EventType

        unsigned int m_nLevel; // ���ȼ�������ԽС���ȼ�Խ��

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
