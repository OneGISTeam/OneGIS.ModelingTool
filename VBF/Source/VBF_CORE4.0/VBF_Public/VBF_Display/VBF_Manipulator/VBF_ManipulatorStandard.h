#ifndef VBF_CAMERA_MANIPULATOR_H
#define VBF_CAMERA_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>


namespace osgGA {

// �������������ṩ�˿�������Ļ�������
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

		// 2������/��ȡ�����������Ľڵ�
        virtual void setNode( osg::IVBF_SGNode* );
        virtual const osg::IVBF_SGNode* getNode() const { return m_ipNode.get(); }
		virtual osg::IVBF_SGNode* getNode() { return m_ipNode.get(); }

        virtual void home( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void home( double );

        virtual void init( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handle( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void GetUsage( ::ApplicationUsage& usage ) const;


		// 1�����ò�������λ��

		// �����۾���λ�úͷ������ò�����
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation ) = 0;

		// �����۾���λ�á���ת���ģ��۲�㣩�������������ò�����
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up ) = 0;
		
		// ��ȡ���������۾���λ�úͷ���
        virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const = 0;

        // ��ȡ���������۾���λ�á���ת���ģ��۲�㣩����������
        virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const = 0;



		// ����/��ȡ�Ƿ�̶�Z��"UP"����
        virtual void setVerticalAxisFixed( bool value );
        inline bool getVerticalAxisFixed() const { return m_bVerticalAxisFixed; }
		
		// ����/��ȡ����Ƿ�֧�ֱ��׳����׳�����ָ�û����¼��϶�ģ�Ͳ�ͻȻ�ɿ�����ʵ��ģ�͵ĳ�����ת���ƶ���
		inline bool GetAllowThrow() const { return m_bAllowThrow; }
        virtual void SetAllowThrow( bool bAllowThrow );

		// �������
        virtual void setAnimationTime( double t );
        double getAnimationTime() const;
        bool isAnimating() const;
        virtual void finishAnimation();

    protected:
		// ����������������¼�
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

		// �ƶ����
        virtual bool performMovement();
        virtual bool performMovementLeftMouseButton( double eventTimeDelta, double dx, double dy ){ return false; } // ͨ������ƶ����
        virtual bool performMovementMiddleMouseButton( double eventTimeDelta, double dx, double dy ){ return false; } // ͨ���м���������ͬʱ���ƶ����
        virtual bool performMovementRightMouseButton( double eventTimeDelta, double dx, double dy ){ return false; }// ͨ���Ҽ��ƶ����
        virtual bool performMouseDeltaMovement( float dx, float dy ) { return false; } // ͨ���������ƶ������ƶ����
        virtual bool performAnimationMovement( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
    
		
		virtual void applyAnimationStep( double currentProgress, double prevProgress );

        void flushMouseEventStack();// �����������������¼�		
        void addMouseEvent(const GUIEventAdapter& ea);// ������������¼���ֻ����2����

        virtual bool isMouseMoving() const; // �ж�����Ƿ����ƶ����ٶȴ�����ֵ����Ϊ�����ƶ���
        float getThrowScale( double eventTimeDelta ) const;
        virtual void centerMousePointer( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );




        void rotateYawPitch( osg::Quat& rotation, double yaw, double pitch, const osg::Vec3d& localUp = osg::Vec3d( 0.,0.,0.) );
        void fixVerticalAxis( osg::Quat& rotation, const osg::Vec3d& localUp, bool disallowFlipOver );
        void fixVerticalAxis( const osg::Vec3d& forward, const osg::Vec3d& up, osg::Vec3d& newUp, const osg::Vec3d& localUp, bool disallowFlipOver );
         

		void fixVerticalAxis( osg::Vec3d& eye, osg::Quat& rotation, bool disallowFlipOver );     
		virtual bool setCenterByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

		// �����뼸��������ཻ��⣬����ͨ������������Ƶ����ʺϹ۲��λ�ã�ûѡ���򷵻�false
		virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us ) { return false; }

        
        bool m_bThrown;		// �Ƿ�����׳�
        bool m_bAllowThrow;	// �Ƿ���������׳�

        float m_fMouseCenterX, m_fMouseCenterY; // ���λ�ã������Ӧ������е㣩

		// �������������¼�
        ref_ptr< const osgGA::GUIEventAdapter > m_ipEventAdapter1;
        ref_ptr< const osgGA::GUIEventAdapter > m_ipEventAdapter0;

               
        double m_dTimeOneFrame; // ����һ֡�Ĵ��ʱ�䣬���ڼ�������׳������� �ƶ�/��ת ������
        double m_dTimeLastFrame; // ���һ֡����ʼʱ�䣬���������Ϊtrueʱ��ƥ��ˢ�������ƶ�/��ת����

        
        ref_ptr< osg::IVBF_SGNode > m_ipNode; // ��������
        double m_dModelSize;

        bool m_bVerticalAxisFixed;	// �Ƿ�̶�"UP"��

        // ��������
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

        ref_ptr< AnimationData > m_ipAnimationData; // ����������

		int m_nUserInteractionFlags;

};


}

#endif // VBF_CAMERA_MANIPULATOR_H
