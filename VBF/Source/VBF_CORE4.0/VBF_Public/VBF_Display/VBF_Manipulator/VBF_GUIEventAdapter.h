#ifndef OSGGA_EVENT
#define OSGGA_EVENT 1 

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/GraphicsContext.h>
#include <VBF_Display/VBF_Manipulator/Export>

namespace osgGA{


/** 
	GUI事件：鼠标/键盘事件，包括各种事件类型（PUSH，RELEASE，DOUBLECLICK，DRAG，MOVE，
	        KEYDOWN，KEYUP，FRAME，RESIZE，SCROLLUP，SCROLLDOWN，SCROLLLEFT）。
			依据GUIEventAdapter事件类型的不同，其实例可能还有更多的相关属性。
			例如X，Y坐标与鼠标事件相关。KEYUP和KEYDOWN事件则与一个按键值（例如"a"，"F1"）相关联。 
*/
class OSGGA_EXPORT GUIEventAdapter : public osg::CVBF_Object
{
public:
        enum MouseButtonMask 
		{ 
            LEFT_MOUSE_BUTTON    = 1<<0,	// 鼠标左键
            MIDDLE_MOUSE_BUTTON  = 1<<1,	// 鼠标中键
            RIGHT_MOUSE_BUTTON   = 1<<2		// 鼠标右键
        };

        enum EventType 
		{
            NONE                = 0,
            PUSH                = 1<<0,		// 鼠标按下
            RELEASE             = 1<<1,		// 鼠标松开
            DOUBLECLICK         = 1<<2,		// 鼠标双击
            DRAG                = 1<<3,		// 鼠标拖动
            MOVE                = 1<<4,		// 鼠标移动
            KEYDOWN             = 1<<5,		// 键盘按下
            KEYUP               = 1<<6,		// 键盘抬起
            FRAME               = 1<<7,     // 每帧都会触发的事件
            RESIZE              = 1<<8,		// 窗口大小变换
            SCROLL              = 1<<9,		// 鼠标滚轮
            PEN_PRESSURE        = 1<<10,	// 光标笔按下
            PEN_ORIENTATION     = 1<<11,	// 光标笔运动方向
            PEN_PROXIMITY_ENTER = 1<<12,	// 光标笔开始
            PEN_PROXIMITY_LEAVE = 1<<13,	// 光标笔结束
            CLOSE_WINDOW        = 1<<14,	// 窗口关闭
            QUIT_APPLICATION    = 1<<15,	// 程序退出
            USER                = 1<<16
        };

        enum KeySymbol
        {
            KEY_Space           = 0x20,

            KEY_0               = '0',
            KEY_1               = '1',
            KEY_2               = '2',
            KEY_3               = '3',
            KEY_4               = '4',
            KEY_5               = '5',
            KEY_6               = '6',
            KEY_7               = '7',
            KEY_8               = '8',
            KEY_9               = '9',
            KEY_A               = 'a',
            KEY_B               = 'b',
            KEY_C               = 'c',
            KEY_D               = 'd',
            KEY_E               = 'e',
            KEY_F               = 'f',
            KEY_G               = 'g',
            KEY_H               = 'h',
            KEY_I               = 'i',
            KEY_J               = 'j',
            KEY_K               = 'k',
            KEY_L               = 'l',
            KEY_M               = 'm',
            KEY_N               = 'n',
            KEY_O               = 'o',
            KEY_P               = 'p',
            KEY_Q               = 'q',
            KEY_R               = 'r',
            KEY_S               = 's',
            KEY_T               = 't',
            KEY_U               = 'u',
            KEY_V               = 'v',
            KEY_W               = 'w',
            KEY_X               = 'x',
            KEY_Y               = 'y',
            KEY_Z               = 'z',

            KEY_Exclaim         = 0x21,
            KEY_Quotedbl        = 0x22,
            KEY_Hash            = 0x23,
            KEY_Dollar          = 0x24,
            KEY_Ampersand       = 0x26,
            KEY_Quote           = 0x27,
            KEY_Leftparen       = 0x28,
            KEY_Rightparen      = 0x29,
            KEY_Asterisk        = 0x2A,
            KEY_Plus            = 0x2B,
            KEY_Comma           = 0x2C,
            KEY_Minus           = 0x2D,
            KEY_Period          = 0x2E,
            KEY_Slash           = 0x2F,
            KEY_Colon           = 0x3A,
            KEY_Semicolon       = 0x3B,
            KEY_Less            = 0x3C,
            KEY_Equals          = 0x3D,
            KEY_Greater         = 0x3E,
            KEY_Question        = 0x3F,
            KEY_At              = 0x40,
            KEY_Leftbracket     = 0x5B,
            KEY_Backslash       = 0x5C,
            KEY_Rightbracket    = 0x5D,
            KEY_Caret           = 0x5E,
            KEY_Underscore      = 0x5F,
            KEY_Backquote       = 0x60,

            KEY_BackSpace       = 0xFF08,        /* back space, back char */
            KEY_Tab             = 0xFF09,
            KEY_Linefeed        = 0xFF0A,        /* Linefeed, LF */
            KEY_Clear           = 0xFF0B,
            KEY_Return          = 0xFF0D,        /* Return, enter */
            KEY_Pause           = 0xFF13,        /* Pause, hold */
            KEY_Scroll_Lock     = 0xFF14,
            KEY_Sys_Req         = 0xFF15,
            KEY_Escape          = 0xFF1B,
            KEY_Delete          = 0xFFFF,        /* Delete, rubout */


            /* Cursor control & motion */

            KEY_Home            = 0xFF50,
            KEY_Left            = 0xFF51,        /* Move left, left arrow */
            KEY_Up              = 0xFF52,        /* Move up, up arrow */
            KEY_Right           = 0xFF53,        /* Move right, right arrow */
            KEY_Down            = 0xFF54,        /* Move down, down arrow */
            KEY_Prior           = 0xFF55,        /* Prior, previous */
            KEY_Page_Up         = 0xFF55,
            KEY_Next            = 0xFF56,        /* Next */
            KEY_Page_Down       = 0xFF56,
            KEY_End             = 0xFF57,        /* EOL */
            KEY_Begin           = 0xFF58,        /* BOL */


            /* Misc Functions */

            KEY_Select          = 0xFF60,        /* Select, mark */
            KEY_Print           = 0xFF61,
            KEY_Execute         = 0xFF62,        /* Execute, run, do */
            KEY_Insert          = 0xFF63,        /* Insert, insert here */
            KEY_Undo            = 0xFF65,        /* Undo, oops */
            KEY_Redo            = 0xFF66,        /* redo, again */
            KEY_Menu            = 0xFF67,        /* On Windows, this is VK_APPS, the context-menu key */
            KEY_Find            = 0xFF68,        /* Find, search */
            KEY_Cancel          = 0xFF69,        /* Cancel, stop, abort, exit */
            KEY_Help            = 0xFF6A,        /* Help */
            KEY_Break           = 0xFF6B,
            KEY_Mode_switch     = 0xFF7E,        /* Character set switch */
            KEY_Script_switch   = 0xFF7E,        /* Alias for mode_switch */
            KEY_Num_Lock        = 0xFF7F,

            /* Keypad Functions, keypad numbers cleverly chosen to map to ascii */

            KEY_KP_Space        = 0xFF80,        /* space */
            KEY_KP_Tab          = 0xFF89,
            KEY_KP_Enter        = 0xFF8D,        /* enter */
            KEY_KP_F1           = 0xFF91,        /* PF1, KP_A, ... */
            KEY_KP_F2           = 0xFF92,
            KEY_KP_F3           = 0xFF93,
            KEY_KP_F4           = 0xFF94,
            KEY_KP_Home         = 0xFF95,
            KEY_KP_Left         = 0xFF96,
            KEY_KP_Up           = 0xFF97,
            KEY_KP_Right        = 0xFF98,
            KEY_KP_Down         = 0xFF99,
            KEY_KP_Prior        = 0xFF9A,
            KEY_KP_Page_Up      = 0xFF9A,
            KEY_KP_Next         = 0xFF9B,
            KEY_KP_Page_Down    = 0xFF9B,
            KEY_KP_End          = 0xFF9C,
            KEY_KP_Begin        = 0xFF9D,
            KEY_KP_Insert       = 0xFF9E,
            KEY_KP_Delete       = 0xFF9F,
            KEY_KP_Equal        = 0xFFBD,        /* equals */
            KEY_KP_Multiply     = 0xFFAA,
            KEY_KP_Add          = 0xFFAB,
            KEY_KP_Separator    = 0xFFAC,       /* separator, often comma */
            KEY_KP_Subtract     = 0xFFAD,
            KEY_KP_Decimal      = 0xFFAE,
            KEY_KP_Divide       = 0xFFAF,

            KEY_KP_0            = 0xFFB0,
            KEY_KP_1            = 0xFFB1,
            KEY_KP_2            = 0xFFB2,
            KEY_KP_3            = 0xFFB3,
            KEY_KP_4            = 0xFFB4,
            KEY_KP_5            = 0xFFB5,
            KEY_KP_6            = 0xFFB6,
            KEY_KP_7            = 0xFFB7,
            KEY_KP_8            = 0xFFB8,
            KEY_KP_9            = 0xFFB9,
            
            /*
             * Auxiliary Functions; note the duplicate definitions for left and right
             * function keys;  Sun keyboards and a few other manufactures have such
             * function key groups on the left and/or right sides of the keyboard.
             * We've not found a keyboard with more than 35 function keys total.
             */

            KEY_F1              = 0xFFBE,
            KEY_F2              = 0xFFBF,
            KEY_F3              = 0xFFC0,
            KEY_F4              = 0xFFC1,
            KEY_F5              = 0xFFC2,
            KEY_F6              = 0xFFC3,
            KEY_F7              = 0xFFC4,
            KEY_F8              = 0xFFC5,
            KEY_F9              = 0xFFC6,
            KEY_F10             = 0xFFC7,
            KEY_F11             = 0xFFC8,
            KEY_F12             = 0xFFC9,
            KEY_F13             = 0xFFCA,
            KEY_F14             = 0xFFCB,
            KEY_F15             = 0xFFCC,
            KEY_F16             = 0xFFCD,
            KEY_F17             = 0xFFCE,
            KEY_F18             = 0xFFCF,
            KEY_F19             = 0xFFD0,
            KEY_F20             = 0xFFD1,
            KEY_F21             = 0xFFD2,
            KEY_F22             = 0xFFD3,
            KEY_F23             = 0xFFD4,
            KEY_F24             = 0xFFD5,
            KEY_F25             = 0xFFD6,
            KEY_F26             = 0xFFD7,
            KEY_F27             = 0xFFD8,
            KEY_F28             = 0xFFD9,
            KEY_F29             = 0xFFDA,
            KEY_F30             = 0xFFDB,
            KEY_F31             = 0xFFDC,
            KEY_F32             = 0xFFDD,
            KEY_F33             = 0xFFDE,
            KEY_F34             = 0xFFDF,
            KEY_F35             = 0xFFE0,

            /* Modifiers */

            KEY_Shift_L         = 0xFFE1,        /* Left shift */
            KEY_Shift_R         = 0xFFE2,        /* Right shift */
            KEY_Control_L       = 0xFFE3,        /* Left control */
            KEY_Control_R       = 0xFFE4,        /* Right control */
            KEY_Caps_Lock       = 0xFFE5,        /* Caps lock */
            KEY_Shift_Lock      = 0xFFE6,        /* Shift lock */

            KEY_Meta_L          = 0xFFE7,        /* Left meta */
            KEY_Meta_R          = 0xFFE8,        /* Right meta */
            KEY_Alt_L           = 0xFFE9,        /* Left alt */
            KEY_Alt_R           = 0xFFEA,        /* Right alt */
            KEY_Super_L         = 0xFFEB,        /* Left super */
            KEY_Super_R         = 0xFFEC,        /* Right super */
            KEY_Hyper_L         = 0xFFED,        /* Left hyper */
            KEY_Hyper_R         = 0xFFEE         /* Right hyper */
        };


        enum ModKeyMask // 功能键
        {
            MODKEY_LEFT_SHIFT  = 0x0001,
            MODKEY_RIGHT_SHIFT = 0x0002,
            MODKEY_LEFT_CTRL   = 0x0004,
            MODKEY_RIGHT_CTRL  = 0x0008,
            MODKEY_LEFT_ALT    = 0x0010,
            MODKEY_RIGHT_ALT   = 0x0020,
            MODKEY_LEFT_META   = 0x0040,
            MODKEY_RIGHT_META  = 0x0080,
            MODKEY_LEFT_SUPER  = 0x0100,
            MODKEY_RIGHT_SUPER = 0x0200,
            MODKEY_LEFT_HYPER  = 0x0400,
            MODKEY_RIGHT_HYPER = 0x0800,
            MODKEY_NUM_LOCK    = 0x1000,
            MODKEY_CAPS_LOCK   = 0x2000,
            MODKEY_CTRL        = (MODKEY_LEFT_CTRL|MODKEY_RIGHT_CTRL),
            MODKEY_SHIFT       = (MODKEY_LEFT_SHIFT|MODKEY_RIGHT_SHIFT),
            MODKEY_ALT         = (MODKEY_LEFT_ALT|MODKEY_RIGHT_ALT),
            MODKEY_META        = (MODKEY_LEFT_META|MODKEY_RIGHT_META),
            MODKEY_SUPER       = (MODKEY_LEFT_SUPER|MODKEY_RIGHT_SUPER),
            MODKEY_HYPER       = (MODKEY_LEFT_HYPER|MODKEY_RIGHT_HYPER)
        };

        enum MouseYOrientation
        {
            Y_INCREASING_UPWARDS,
            Y_INCREASING_DOWNWARDS
        };

        enum ScrollingMotion 
        {
            SCROLL_NONE,
            SCROLL_LEFT,
            SCROLL_RIGHT,
            SCROLL_UP,
            SCROLL_DOWN,
            SCROLL_2D
        };

        enum TabletPointerType 
        {
            UNKNOWN = 0,
            PEN,
            PUCK,
            ERASER
        };
        
        enum TouchPhase 
        {
            TOUCH_UNKNOWN,
            TOUCH_BEGAN,
            TOUCH_MOVED,
            TOUCH_STATIONERY,
            TOUCH_ENDED
        };
        
        class TouchData : public ::CVBF_Referenced 
		{
        public:
            struct TouchPoint 
			{
                unsigned int id;
                TouchPhase phase;
                float x, y;
                
                unsigned int tapCount;
                TouchPoint() : id(0), phase(TOUCH_UNKNOWN), x(0.0f), y(0.0f), tapCount(0) {}
                TouchPoint(unsigned int in_id, TouchPhase in_phase, float in_x, float in_y, unsigned int in_tap_count) 
                :    id(in_id), 
                    phase(in_phase),
                    x(in_x), 
                    y(in_y), 
                    tapCount(in_tap_count) 
                {
                }
            };
                        
            typedef std::vector<TouchPoint> TouchSet;
            
            typedef TouchSet::iterator iterator;
            typedef TouchSet::const_iterator const_iterator;
            
            TouchData() : CVBF_Referenced() {}
            
            unsigned int getNumTouchPoints() const { return _touches.size(); }
                        
            iterator begin() { return _touches.begin(); }
            const_iterator begin() const { return _touches.begin(); }
            
            iterator end() { return _touches.end(); }
            const_iterator end() const { return _touches.end(); }
            
            const TouchPoint get(unsigned int i) const { return _touches[i]; }
                    
        protected:
            
            void addTouchPoint(unsigned int id, TouchPhase phase, float x, float y, unsigned int tap_count) 
			{
                _touches.push_back(TouchPoint(id, phase, x, y, tap_count));
            }
            
            TouchSet _touches;
            
        friend class GUIEventAdapter;    
        };
        
    public:

        GUIEventAdapter();
        GUIEventAdapter(const GUIEventAdapter& rhs, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgGA, GUIEventAdapter);
        


 		// 设置/获取事件是否已经被事件处理器处理过
        void setHandled(bool handled) const { _handled = handled; }
        bool IsHandled() const { return _handled; }

		// 设置/获取事件的类型
        void setEventType(EventType Type) { _eventType = Type; }
        virtual EventType getEventType() const { return _eventType; }

		// 设置/获取事件的时间（秒）
        void setTime(double time) { _time = time; }
        double getTime() const { return _time; }

		// 获取时间（废弃的）
        double time() const { return _time; }

		// 设置/获取图形环境
        void setGraphicsContext(osg::GraphicsContext* context) { _context = context; }
        const osg::GraphicsContext* getGraphicsContext() const { return _context.get(); }
        

		// 设置窗口的位置矩形
        void setWindowRectangle(int x, int y, int width, int height, bool updateMouseRange = true);

        // 获取事件所在窗口原点的XY值
        int getWindowX() const { return _windowX; }
        int getWindowY() const { return _windowY; }

        // 获取事件所在窗口的宽度和高度
        int getWindowWidth() const { return _windowWidth; }
        int getWindowHeight() const { return _windowHeight; }


        // 设置/获取key按下，如果和此GUIEventAdapter不相称则返回-1
        inline void setKey(int key) { _key = key; }
        virtual int getKey() const { return _key; }


		// 设置/获取virtual key按下
        void setUnmodifiedKey(int key) { _unmodifiedKey = key; }
        int getUnmodifiedKey() const { return _unmodifiedKey; }
        
  		// 设置/获取鼠标键按下/释放，如果和此GUIEventAdapter不相称则返回-1
        void setButton(int button) { _button = button; }
        int getButton() const { return _button; }

		// 设置鼠标输入的范围
        void setInputRange(float Xmin, float Ymin, float Xmax, float Ymax);

        // 获取鼠标的最大/最小X值
        float getXmin() const { return _Xmin; }
        float getXmax() const { return _Xmax; }

        // 获取鼠标的最大/最小Y值
        float getYmin() const { return _Ymin; }
        float getYmax() const { return _Ymax; }

 		// 设置/获取鼠标当前的X值
        void setX(float x) { _mx = x; }
        float getX() const { return _mx; }

        // 设置/获取鼠标当前的Y值
        void setY(float y) { _my = y; }
        float getY() const { return _my; }


		// 获取当前鼠标的规范化的X值（-1.0到1.0，-1表示窗口的最左边，1表示最右边，0表示中间）
        inline float getXnormalized() const { return 2.0f*(getX()-getXmin())/(getXmax()-getXmin())-1.0f; }

		// 获取当前鼠标的规范化的Y值（-1.0到1.0，-1表示窗口的最下边，1表示最上边，0表示中间）
        inline float getYnormalized() const
        {
            if (_mouseYOrientation==Y_INCREASING_UPWARDS) return 2.0f*(getY()-getYmin())/(getYmax()-getYmin())-1.0f;
            else return -(2.0f*(getY()-getYmin())/(getYmax()-getYmin())-1.0f);
        }

        // 设置/获取鼠标Y轴的方向 (向上或向下)
        void setMouseYOrientation(MouseYOrientation myo) { _mouseYOrientation = myo; }
        MouseYOrientation getMouseYOrientation() const { return _mouseYOrientation; }

        // 设置/获取当前鼠标键的掩码（MouseButtonMask）
        void setButtonMask(int mask) { _buttonMask = mask; }
        int getButtonMask() const { return _buttonMask; }

		// 设置/获取功能键（Alt等）的掩码
        void setModKeyMask(int mask) { _modKeyMask = mask; }
        int getModKeyMask() const { return _modKeyMask; }

        /// set scrolling motion (for EventType::SCROLL).
        void setScrollingMotion(ScrollingMotion motion) { _scrolling.motion = motion; }
        ScrollingMotion getScrollingMotion() const { return _scrolling.motion; }

        /// set the scrolling delta to x,y and the scrolling motion to SCROLL_2D.
        void setScrollingMotionDelta(float x, float y) 
		{
            _scrolling.motion = SCROLL_2D;
            _scrolling.deltaX = x;
            _scrolling.deltaY = y;
        }

        /// get the scrolling x-delta.
        float getScrollingDeltaX() const { return _scrolling.deltaX; }

        /// get the scrolling y-delta.
        float getScrollingDeltaY() const { return _scrolling.deltaY; }




        /// set the tablet pen pressure (range 0..1).
        void setPenPressure(float pressure) { _tabletPen.pressure = pressure; }
        float getPenPressure()  const { return _tabletPen.pressure; }

        /// set the tablet pen tiltX in degrees.
        void setPenTiltX(float tiltX) { _tabletPen.tiltX = tiltX; }
        float getPenTiltX()  const { return _tabletPen.tiltX; }

        /// set the tablet pen tiltY in degrees.
        void setPenTiltY(float tiltY) { _tabletPen.tiltY = tiltY; }
        float getPenTiltY()  const { return _tabletPen.tiltY; }

        // 设置/获取tablet pen绕Z轴旋转的角度（单位：度）
        void setPenRotation(float rotation) { _tabletPen.rotation = rotation; }
        float getPenRotation()  const { return _tabletPen.rotation; }

        /// set the tablet pointer type.
        void setTabletPointerType(TabletPointerType pt) { _tabletPen.tabletPointerType = pt; }
        TabletPointerType getTabletPointerType() const { return _tabletPen.tabletPointerType; }

        /// set the orientation from a tablet input device as a matrix.
        const osg::Matrix getPenOrientation() const;





        void addTouchPoint(unsigned int id, TouchPhase phase, float x, float y, unsigned int tapCount = 0);        
        TouchData* getTouchData() const { return _touchData.get(); }
        bool isMultiTouchEvent() const { return (_touchData.valid()); }
        
    protected:

        /** Force users to create on heap, so that multiple referencing is safe.*/
        virtual ~GUIEventAdapter();

        mutable bool _handled;        
        EventType _eventType;
        double _time;

        observer_ptr<osg::GraphicsContext> _context;
        int _windowX;
        int _windowY;
        int _windowWidth;
        int _windowHeight;
        int _key;
        int _unmodifiedKey;
        int _button;
        float _Xmin,_Xmax;
        float _Ymin,_Ymax;
        float _mx;
        float _my;
        int _buttonMask;
        int _modKeyMask;
        MouseYOrientation _mouseYOrientation;

        struct Scrolling 
		{
            ScrollingMotion motion;
            float deltaX;
            float deltaY;

            Scrolling() : motion(SCROLL_NONE), deltaX(0), deltaY(0) {}
            Scrolling(const Scrolling& rhs) : motion(rhs.motion), deltaX(rhs.deltaX), deltaY(rhs.deltaY) {}
        };
        Scrolling _scrolling;

        struct TabletPen 
		{
            float pressure;
            float tiltX;
            float tiltY;
            float rotation;
            TabletPointerType tabletPointerType;

            TabletPen() : pressure(0), tiltX(0), tiltY(0), rotation(0), tabletPointerType(UNKNOWN) {}
            TabletPen(const TabletPen& rhs) : pressure(rhs.pressure), tiltX(rhs.tiltX), tiltY(rhs.tiltY), rotation(rhs.rotation), tabletPointerType(rhs.tabletPointerType) {}
        };
        TabletPen _tabletPen;
                
        ref_ptr<TouchData> _touchData; 
};

}

#endif
