#ifndef OSGGA_EVENTQUEUE
#define OSGGA_EVENTQUEUE 1

#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Timer.h>

#include <OpenThreads/Mutex>
#include <list>

namespace osgGA {


// �¼����У��ռ������䴰���¼�
class OSGGA_EXPORT CVBF_EventQueue : public ::CVBF_Referenced
{
    public:
        CVBF_EventQueue(GUIEventAdapter::MouseYOrientation mouseYOrientation=GUIEventAdapter::Y_INCREASING_DOWNWARDS);

        typedef std::list< ref_ptr<GUIEventAdapter> > Events;
                
		// �����¼�
        void setEvents(Events& events);

		// ȡ���¼��������ÿ�
        bool takeEvents(Events& events);

		// ȡ��ָ��ʱ����ǰ��¼���¼�
        bool takeEvents(Events& events, double cutOffTime);

		// ����һ���������¼���ԭ�¼�����
        bool copyEvents(Events& events) const;

		// ���¼�����׷���¼�
        void appendEvents(Events& events);

		// ���¼�����β�����һ���¼�
        void addEvent(GUIEventAdapter* pEvent);


        // ����/��ȡ�Ƿ��������ת����һ��Ԥ�ȶ������������input range��������ʹ�ò�������¼��Ĵ��ڵľֲ����꣩
        void setUseFixedMouseInputRange(bool useFixedMouseInputRange) { _useFixedMouseInputRange = useFixedMouseInputRange; }
        bool getUseFixedMouseInputRange() { return _useFixedMouseInputRange; }


		// �����¼����й�����GC
        void setGraphicsContext(osg::GraphicsContext* context) { getCurrentEventState()->setGraphicsContext(context); }

		// ����������������
        void setMouseInputRange(float xMin, float yMin, float xMax, float yMax) { getCurrentEventState()->setInputRange(xMin, yMin, xMax, yMax); }

		// ���resize�¼���β�������䴰��resize�¼��ĺ���
        void windowResize(int x, int y, int width, int height) { windowResize(x,y,width,height,getTime()); }

		// ���resize�¼���β��������ʱ�䣬���䴰��resize�¼��ĺ���
        void windowResize(int x, int y, int width, int height, double time);

		// ���mouse scroll wheel�¼���β��
        void mouseScroll(GUIEventAdapter::ScrollingMotion sm) { mouseScroll(sm,getTime()); }
    
        // ���mouse scroll wheel�¼���β��������ʱ��
        void mouseScroll(GUIEventAdapter::ScrollingMotion sm, double time);
               
		// ���mouse scroll wheel�¼���β��
		void mouseScroll2D(float x, float y) { mouseScroll2D(x, y, getTime()); }
        void mouseScroll2D(float x, float y, double time);
        
		// ���pen pressure�¼���β��
		void penPressure(float pressure) { penPressure(pressure, getTime()); }
        void penPressure(float pressure, double time);

 		// ���pen orientation�¼���β��
		void penOrientation(float tiltX, float tiltY, float rotation) { penOrientation(tiltX, tiltY, rotation, getTime()); }
        void penOrientation(float tiltX, float tiltY, float rotation, double time);
        
 		// ����pen proximity�¼����Ѹ��¼���ӵ��¼�����β��
        void penProximity(GUIEventAdapter::TabletPointerType pt, bool isEntering) { penProximity(pt, isEntering, getTime()); }
        void penProximity(GUIEventAdapter::TabletPointerType pt, bool isEntering, double time);


        /** Method for updating in response to a mouse warp. Note, just moves the mouse position without creating a new event for it.*/
        void mouseWarped(float x, float y);

 		// ���������ƶ��¼����Ѹ��¼���ӵ��¼�����β��
        void mouseMotion(float x, float y, double time);
		void mouseMotion(float x, float y) { mouseMotion(x,y, getTime()); }

		// �������������¼����Ѹ��¼���ӵ��¼�����β����button��ֵΪ1���������2Ϊ�м���3Ϊ�Ҽ�
        void mouseButtonPress(float x, float y, unsigned int button, double time);
        void mouseButtonPress(float x, float y, unsigned int button) { mouseButtonPress(x, y, button, getTime()); }

		// ��������˫���¼����Ѹ��¼���ӵ��¼�����β����button��ֵΪ1���������2Ϊ�м���3Ϊ�Ҽ�
		void mouseDoubleButtonPress(float x, float y, unsigned int button) { mouseDoubleButtonPress(x, y, button, getTime()); }
        void mouseDoubleButtonPress(float x, float y, unsigned int button, double time);
        

		// ��������̧���¼����Ѹ��¼���ӵ��¼�����β����button��ֵΪ1���������2Ϊ�м���3Ϊ�Ҽ�
        void mouseButtonRelease(float x, float y, unsigned int button) { mouseButtonRelease(x, y, button, getTime()); }
        void mouseButtonRelease(float x, float y, unsigned int button, double time);

		// ������̰���/̧���¼�������ļ�����Ctrl/Function�ȼ��������䵽GUIEventAdapter::KeySymbolӳ�䣩
        void keyPress(int key, int unmodifiedKey = 0) { keyPress(key, getTime(), unmodifiedKey); }
        void keyPress(int key, double time, int unmodifiedKey = 0);
        void keyRelease(int key, int unmodifiedKey = 0) { keyRelease(key, getTime(), unmodifiedKey); }
        void keyRelease(int key, double time, int unmodifiedKey = 0);
            

        GUIEventAdapter* touchBegan(unsigned int id, GUIEventAdapter::TouchPhase phase, float x, float y, double time);
        GUIEventAdapter* touchBegan(unsigned int id, GUIEventAdapter::TouchPhase phase,  float x, float y) 
		{
            return touchBegan(id, phase, x, y, getTime());
        }
        
        GUIEventAdapter*  touchMoved(unsigned int id, GUIEventAdapter::TouchPhase phase,  float x, float y, double time);
        GUIEventAdapter*  touchMoved(unsigned int id, GUIEventAdapter::TouchPhase phase,  float x, float y) 
		{
            return touchMoved(id, phase, x, y, getTime());
        }
        
        GUIEventAdapter*  touchEnded(unsigned int id, GUIEventAdapter::TouchPhase phase,  float x, float y, unsigned int tap_count, double time);
        GUIEventAdapter*  touchEnded(unsigned int id, GUIEventAdapter::TouchPhase phase,  float x, float y, unsigned int tap_count) 
		{
            return touchEnded(id, phase, x, y, tap_count, getTime());
        }
        
		// ����close window�¼�
        void closeWindow() { closeWindow(getTime()); }
        void closeWindow(double time);

        // ����quit�¼�
        void quitApplication() { quitApplication(getTime()); }
        void quitApplication(double time);

		// ����frame�¼�
        void frame(double time);
        
		// ����/��ȡ��ʼ��ʱ�䣨tick��
        void setStartTick(CVBF_Timer_t tick) { _startTick = tick; }
        CVBF_Timer_t getStartTick() const { return _startTick; }

		// ��ȡʱ��
        double getTime() const { return CVBF_Timer::instance()->delta_s(_startTick, CVBF_Timer::instance()->tick()); }

		// ����һ���¼������õ�ǰ���¼�״̬
        GUIEventAdapter* createEvent();
        
        // ��ȡ��ǰ���¼�״̬
        GUIEventAdapter* getCurrentEventState() { return _accumulateEventState.get(); }
        const GUIEventAdapter* getCurrentEventState() const { return _accumulateEventState.get(); }

		// �����û�������¼�
        void userEvent(::CVBF_Referenced* userEventData) { userEvent(userEventData, getTime()); }
        void userEvent(::CVBF_Referenced* userEventData, double time);


    protected:
        virtual ~CVBF_EventQueue();

        CVBF_EventQueue& operator = (const CVBF_EventQueue&) { return *this; } // ��ֹ����
        
        ref_ptr<GUIEventAdapter>   _accumulateEventState;

        bool                        _useFixedMouseInputRange;

        CVBF_Timer_t                _startTick;
        mutable OpenThreads::Mutex  _eventQueueMutex;
        Events                      _eventQueue;
    
};

}

#endif
