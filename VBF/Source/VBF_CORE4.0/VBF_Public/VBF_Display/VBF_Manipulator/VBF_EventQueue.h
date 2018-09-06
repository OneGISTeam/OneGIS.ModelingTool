#ifndef OSGGA_EVENTQUEUE
#define OSGGA_EVENTQUEUE 1

#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Timer.h>

#include <OpenThreads/Mutex>
#include <list>

namespace osgGA {


// 事件队列：收集和适配窗口事件
class OSGGA_EXPORT CVBF_EventQueue : public ::CVBF_Referenced
{
    public:
        CVBF_EventQueue(GUIEventAdapter::MouseYOrientation mouseYOrientation=GUIEventAdapter::Y_INCREASING_DOWNWARDS);

        typedef std::list< ref_ptr<GUIEventAdapter> > Events;
                
		// 设置事件
        void setEvents(Events& events);

		// 取出事件，队列置空
        bool takeEvents(Events& events);

		// 取出指定时间以前记录的事件
        bool takeEvents(Events& events, double cutOffTime);

		// 拷贝一份完整的事件，原事件不变
        bool copyEvents(Events& events) const;

		// 向事件队列追加事件
        void appendEvents(Events& events);

		// 向事件队列尾部添加一个事件
        void addEvent(GUIEventAdapter* pEvent);


        // 设置/获取是否将鼠标坐标转换到一个预先定义的输入区域（input range）（或者使用产生鼠标事件的窗口的局部坐标）
        void setUseFixedMouseInputRange(bool useFixedMouseInputRange) { _useFixedMouseInputRange = useFixedMouseInputRange; }
        bool getUseFixedMouseInputRange() { return _useFixedMouseInputRange; }


		// 设置事件队列关联的GC
        void setGraphicsContext(osg::GraphicsContext* context) { getCurrentEventState()->setGraphicsContext(context); }

		// 设置鼠标输入的区域
        void setMouseInputRange(float xMin, float yMin, float xMax, float yMax) { getCurrentEventState()->setInputRange(xMin, yMin, xMax, yMax); }

		// 添加resize事件到尾部，适配窗口resize事件的函数
        void windowResize(int x, int y, int width, int height) { windowResize(x,y,width,height,getTime()); }

		// 添加resize事件到尾部并给定时间，适配窗口resize事件的函数
        void windowResize(int x, int y, int width, int height, double time);

		// 添加mouse scroll wheel事件到尾部
        void mouseScroll(GUIEventAdapter::ScrollingMotion sm) { mouseScroll(sm,getTime()); }
    
        // 添加mouse scroll wheel事件到尾部并给定时间
        void mouseScroll(GUIEventAdapter::ScrollingMotion sm, double time);
               
		// 添加mouse scroll wheel事件到尾部
		void mouseScroll2D(float x, float y) { mouseScroll2D(x, y, getTime()); }
        void mouseScroll2D(float x, float y, double time);
        
		// 添加pen pressure事件到尾部
		void penPressure(float pressure) { penPressure(pressure, getTime()); }
        void penPressure(float pressure, double time);

 		// 添加pen orientation事件到尾部
		void penOrientation(float tiltX, float tiltY, float rotation) { penOrientation(tiltX, tiltY, rotation, getTime()); }
        void penOrientation(float tiltX, float tiltY, float rotation, double time);
        
 		// 适配pen proximity事件，把该事件添加到事件队列尾部
        void penProximity(GUIEventAdapter::TabletPointerType pt, bool isEntering) { penProximity(pt, isEntering, getTime()); }
        void penProximity(GUIEventAdapter::TabletPointerType pt, bool isEntering, double time);


        /** Method for updating in response to a mouse warp. Note, just moves the mouse position without creating a new event for it.*/
        void mouseWarped(float x, float y);

 		// 适配鼠标的移动事件，把该事件添加到事件队列尾部
        void mouseMotion(float x, float y, double time);
		void mouseMotion(float x, float y) { mouseMotion(x,y, getTime()); }

		// 适配鼠标键按下事件，把该事件添加到事件队列尾部。button的值为1代表左键，2为中键，3为右键
        void mouseButtonPress(float x, float y, unsigned int button, double time);
        void mouseButtonPress(float x, float y, unsigned int button) { mouseButtonPress(x, y, button, getTime()); }

		// 适配鼠标键双击事件，把该事件添加到事件队列尾部。button的值为1代表左键，2为中键，3为右键
		void mouseDoubleButtonPress(float x, float y, unsigned int button) { mouseDoubleButtonPress(x, y, button, getTime()); }
        void mouseDoubleButtonPress(float x, float y, unsigned int button, double time);
        

		// 适配鼠标键抬起事件，把该事件添加到事件队列尾部。button的值为1代表左键，2为中键，3为右键
        void mouseButtonRelease(float x, float y, unsigned int button) { mouseButtonRelease(x, y, button, getTime()); }
        void mouseButtonRelease(float x, float y, unsigned int button, double time);

		// 适配键盘按下/抬起事件（特殊的键，如Ctrl/Function等键，被适配到GUIEventAdapter::KeySymbol映射）
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
        
		// 适配close window事件
        void closeWindow() { closeWindow(getTime()); }
        void closeWindow(double time);

        // 适配quit事件
        void quitApplication() { quitApplication(getTime()); }
        void quitApplication(double time);

		// 适配frame事件
        void frame(double time);
        
		// 设置/获取开始的时间（tick）
        void setStartTick(CVBF_Timer_t tick) { _startTick = tick; }
        CVBF_Timer_t getStartTick() const { return _startTick; }

		// 获取时间
        double getTime() const { return CVBF_Timer::instance()->delta_s(_startTick, CVBF_Timer::instance()->tick()); }

		// 创建一个事件，采用当前的事件状态
        GUIEventAdapter* createEvent();
        
        // 获取当前的事件状态
        GUIEventAdapter* getCurrentEventState() { return _accumulateEventState.get(); }
        const GUIEventAdapter* getCurrentEventState() const { return _accumulateEventState.get(); }

		// 适配用户定义的事件
        void userEvent(::CVBF_Referenced* userEventData) { userEvent(userEventData, getTime()); }
        void userEvent(::CVBF_Referenced* userEventData, double time);


    protected:
        virtual ~CVBF_EventQueue();

        CVBF_EventQueue& operator = (const CVBF_EventQueue&) { return *this; } // 防止拷贝
        
        ref_ptr<GUIEventAdapter>   _accumulateEventState;

        bool                        _useFixedMouseInputRange;

        CVBF_Timer_t                _startTick;
        mutable OpenThreads::Mutex  _eventQueueMutex;
        Events                      _eventQueue;
    
};

}

#endif
