#ifndef OSGGA_ORBIT_MANIPULATOR
#define OSGGA_ORBIT_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorStandard.h>


namespace osgGA {

// �������������������Ĳ���Ϊ���������ġ��۲���롢����
class OSGGA_EXPORT OrbitManipulator : public StandardManipulator
{
        typedef StandardManipulator inherited;

    public:

        OrbitManipulator( int flags = DEFAULT_SETTINGS );
        OrbitManipulator( const OrbitManipulator& om, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, OrbitManipulator );

        virtual void setByMatrix( const osg::Matrixd& matrix );
        virtual void setByInverseMatrix( const osg::Matrixd& matrix );
        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;

        virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation );
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );
        virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const;
        virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const;

        void setHeading( double azimuth );
        double getHeading() const;
        void setElevation( double elevation );
        double getElevation() const;

        virtual void setCenter( const osg::Vec3d& center );
        const osg::Vec3d& getCenter() const;
        virtual void setRotation( const osg::Quat& rotation );
        const osg::Quat& getRotation() const;
        virtual void setDistance( double distance );
        double getDistance() const;

        virtual void setTrackballSize( const double& size );
        inline double getTrackballSize() const;
        virtual void setWheelZoomFactor( double wheelZoomFactor );
        inline double getWheelZoomFactor() const;

        virtual void setMinimumDistance( const double& minimumDistance, bool relativeToModelSize = NULL );
        double getMinimumDistance( bool *relativeToModelSize = NULL ) const;

        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const;
        virtual float getFusionDistanceValue() const;

    protected:

        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool performMovementLeftMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMovementMiddleMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMovementRightMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMouseDeltaMovement( float dx, float dy );
        virtual void applyAnimationStep( double currentProgress, double prevProgress );

        virtual void rotateTrackball( float px0, float py0, float px1, float py1, float scale );
        virtual void rotateWithFixedVertical( float dx, float dy );
        virtual void rotateWithFixedVertical( float dx, float dy, const osg::Vec3f& up );
        virtual void panModel( float dx, float dy, float dz = 0.f );
        virtual void zoomModel( float dy, bool pushForwardIfNeeded = true );
        void trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y );
        float tb_project_to_sphere( float r, float x, float y );
        virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        osg::Vec3d m_vCenter;
        osg::Quat  _rotation;
        double     m_dDistance;

        double _trackballSize;
        double _wheelZoomFactor;

        double _minimumDistance;
		bool  m_bMinDistanceRelative;// ��С�����Ǿ��ԵĻ��������ģ�ʹ�С��

        class OrbitAnimationData : public AnimationData 
		{
        public:
            osg::Vec3d _movement;
            void start( const osg::Vec3d& movement, double startTime );
        };
        virtual void allocAnimationData() { m_ipAnimationData = new OrbitAnimationData(); }
};



// ��ȡtrackball�Ĵ�С�������ģ�͵Ĵ�С��
inline double OrbitManipulator::getTrackballSize() const  { return _trackballSize; }
// ��ȡ������������
inline double OrbitManipulator::getWheelZoomFactor() const  { return _wheelZoomFactor; }


}

#endif /* OSGGA_ORBIT_MANIPULATOR */
