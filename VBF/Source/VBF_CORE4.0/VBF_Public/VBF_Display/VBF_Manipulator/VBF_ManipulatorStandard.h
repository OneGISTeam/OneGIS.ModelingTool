#ifndef VBF_CAMERA_MANIPULATOR_H
#define VBF_CAMERA_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>


namespace osgGA {

// 基本操作器，提供了控制相机的基本操作
class OSGGA_EXPORT StandardManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
        typedef IVBF_CameraManipulatorImpl<IVBF_CameraManipulator> inherited;
    public:
        enum UserInteractionFlags
        {
            UPDATE_MODEL_SIZE       = 0x01,
            COMPUTE_HOME_USING_BBOX = 0x02,
            PROCESS_MOUSE_WHEEL     = 0x04,
            SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT = 0x08,

            DEFAULT_SETTINGS = UPDATE_MODEL_SIZE /*| COMPUTE_HOME_USING_BBOX*/ | PROCESS_MOUSE_WHEEL
        };

        StandardManipulator( int flags = DEFAULT_SETTINGS );
        StandardManipulator( const StandardManipulator& m, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        virtual const char* className() const { return "StandardManipulator"; }

		// 2、设置/获取操作器关联的节点
        virtual void setNode( osg::IVBF_SGNode* );
        virtual const osg::IVBF_SGNode* getNode() const { return m_ipNode.get(); }
		virtual osg::IVBF_SGNode* getNode() { return m_ipNode.get(); }

        virtual void home( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void home( double );

        virtual void init( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handle( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void GetUsage( ::ApplicationUsage& usage ) const;


		// 1、设置操作器的位置

		// 根据眼睛的位置和方向设置操作器
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation ) = 0;

		// 根据眼睛的位置、旋转中心（观察点）、向上向量设置操作器
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up ) = 0;
		
		// 获取操作器中眼睛的位置和方向
        virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const = 0;

        // 获取操作器中眼睛的位置、旋转中心（观察点）、向上向量
        virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const = 0;



		// 设置/获取是否固定Z（"UP"）轴
        virtual void setVerticalAxisFixed( bool value );
        inline bool getVerticalAxisFixed() const { return m_bVerticalAxisFixed; }
		
		// 设置/获取相机是否支持被抛出（抛出，是指用户按下键拖动模型并突然松开，以实现模型的持续旋转或移动）
		inline bool GetAllowThrow() const { return m_bAllowThrow; }
        virtual void SetAllowThrow( bool bAllowThrow );

		// 动画相关
        virtual void setAnimationTime( double t );
        double getAnimationTime() const;
        bool isAnimating() const;
        virtual void finishAnimation();

    protected:
		// 处理各种鼠标与键盘事件
        virtual bool handleFrame( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleResize( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMouseMove( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us ) { return false; }
        virtual bool handleMouseDrag( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMousePush( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMouseRelease( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleKeyDown( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
		virtual bool handleKeyUp( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us ) { return false; }
        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us ) { return false; }
        virtual bool handleMouseDeltaMovement( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

		// 移动相机
        virtual bool performMovement();
        virtual bool performMovementLeftMouseButton( double eventTimeDelta, double dx, double dy ){ return false; } // 通过左键移动相机
        virtual bool performMovementMiddleMouseButton( double eventTimeDelta, double dx, double dy ){ return false; } // 通过中键（或左右同时）移动相机
        virtual bool performMovementRightMouseButton( double eventTimeDelta, double dx, double dy ){ return false; }// 通过右键移动相机
        virtual bool performMouseDeltaMovement( float dx, float dy ) { return false; } // 通过鼠标相对移动的量移动相机
        virtual bool performAnimationMovement( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
    
		
		virtual void applyAnimationStep( double currentProgress, double prevProgress );

        void flushMouseEventStack();// 重设最近的两次鼠标事件		
        void addMouseEvent(const GUIEventAdapter& ea);// 添加最近的鼠标事件（只保留2个）

        virtual bool isMouseMoving() const; // 判断鼠标是否在移动（速度大于阈值才认为是在移动）
        float getThrowScale( double eventTimeDelta ) const;
        virtual void centerMousePointer( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );




        void rotateYawPitch( osg::Quat& rotation, double yaw, double pitch, const osg::Vec3d& localUp = osg::Vec3d( 0.,0.,0.) );
        void fixVerticalAxis( osg::Quat& rotation, const osg::Vec3d& localUp, bool disallowFlipOver );
        void fixVerticalAxis( const osg::Vec3d& forward, const osg::Vec3d& up, osg::Vec3d& newUp, const osg::Vec3d& localUp, bool disallowFlipOver );
         

		void fixVerticalAxis( osg::Vec3d& eye, osg::Quat& rotation, bool disallowFlipOver );     
		virtual bool setCenterByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

		// 鼠标点与几何体进行相交检测，并把通过动画把相机移到最适合观察的位置，没选中则返回false
		virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us ) { return false; }

        
        bool m_bThrown;		// 是否相机抛出
        bool m_bAllowThrow;	// 是否允许相机抛出

        float m_fMouseCenterX, m_fMouseCenterY; // 鼠标位置（鼠标相应区域的中点）

		// 最近的两次鼠标事件
        ref_ptr< const osgGA::GUIEventAdapter > m_ipEventAdapter1;
        ref_ptr< const osgGA::GUIEventAdapter > m_ipEventAdapter0;

               
        double m_dTimeOneFrame; // 绘制一帧的大概时间，用于计算相机抛出过程中 移动/旋转 的增量
        double m_dTimeLastFrame; // 最后一帧的起始时间，用于桢相关为true时，匹配刷新率与移动/旋转速率

        
        ref_ptr< osg::IVBF_SGNode > m_ipNode; // 场景数据
        double m_dModelSize;

        bool m_bVerticalAxisFixed;	// 是否固定"UP"轴

        // 动画数据
        class OSGGA_EXPORT AnimationData : public ::CVBF_Referenced 
		{
        public:
            double _animationTime;
            bool   _isAnimating;
            double _startTime;
            double _phase;

            AnimationData()
			{
				_isAnimating = false;
			}
			void start( const double startTime )
			{
				_isAnimating = true;
				_startTime = startTime;
				_phase = 0.;
			}
        };

        virtual void allocAnimationData() { m_ipAnimationData = new AnimationData(); }

        ref_ptr< AnimationData > m_ipAnimationData; // 操作器动画

		int m_nUserInteractionFlags;

};


}

#endif // VBF_CAMERA_MANIPULATOR_H
