#ifndef VBF_MANIPULATOR_TRACKER_FIX_RELATIVE
#define VBF_MANIPULATOR_TRACKER_FIX_RELATIVE 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorStandard.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObserverNodePath.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>

namespace osgGA {

// 节点跟踪操作器（相对固定），例如把相机绑定在相对于飞机固定的位置，跟踪飞机。位置固定，姿态可以与飞机绑定，也可以不绑定
class OSGGA_EXPORT CVBF_ManipulatorTrackerFixR : public StandardManipulator
{
        typedef StandardManipulator inherited;

    public:
        CVBF_ManipulatorTrackerFixR( int flags = DEFAULT_SETTINGS );
        CVBF_ManipulatorTrackerFixR( const CVBF_ManipulatorTrackerFixR& om, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, CVBF_ManipulatorTrackerFixR );


        void setTrackNode(osg::IVBF_SGNode* node,IVBF_View* pIView);
        osg::IVBF_SGNode* getTrackNode() { osg::CVBF_SGNodePath nodePath; return m_TrackNodePath.getNodePath(nodePath) && !nodePath.empty() ? nodePath.back() : 0; }
        const osg::IVBF_SGNode* getTrackNode() const { osg::CVBF_SGNodePath nodePath; return m_TrackNodePath.getNodePath(nodePath) && !nodePath.empty()  ? nodePath.back() : 0; }

        enum TrackerMode
        {                  
            NODE_CENTER,             // 模型中心
            NODE_CENTER_BOUNDINGBOX, // 跟踪包围球的中心，但不与模型一起旋转
            NODE_CENTER_AND_ROTATION // 跟踪包围球的中心，并与模型一起旋转
        };
        void setTrackerMode(TrackerMode mode);
        TrackerMode getTrackerMode() const { return m_eTrackerMode; }


        virtual void  setWheelZoomFactor( double dZoomFactor );
        inline double getWheelZoomFactor() const;

        virtual void setMinimumDistance( const double& dMinDistance, bool bRelativeToModelSize = NULL );

        virtual void SetDistance( double dis ) { m_dDistance = dis; }
        virtual double GetDistance() { return m_dDistance; }

        virtual void SetAngleH( double dAngleH ) { m_dAngleH = dAngleH; }
        virtual double GetAngleH() { return m_dAngleH; }

        virtual void SetAngleV( double dAngleV ) { m_dAngleV = dAngleV; }
        virtual double GetAngleV() { return m_dAngleV; }


        virtual void setNode(osg::IVBF_SGNode*);

        virtual void setByMatrix(const osg::Matrixd& matrix);
        virtual void setByInverseMatrix( const osg::Matrixd& matrix );

        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;

        virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false);// 计算默认位置

        virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation );
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );
        virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const;
        virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const;

        virtual void zoomModel( float dy, bool pushForwardIfNeeded = true );

    protected:

        virtual bool handleFrame( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool performMovementLeftMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementMiddleMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementRightMouseButton(double eventTimeDelta, double dx, double dy);

        void computeNodeWorldToLocal(osg::Matrixd& worldToLocal) const;
        void computeNodeLocalToWorld(osg::Matrixd& localToWorld) const;

        void computeNodeCenterAndRotation(osg::Vec3d& center, osg::Quat& rotation) const;

        void computePosition(const osg::Vec3d& eye,const osg::Vec3d& lv,const osg::Vec3d& up);


        osg::ObserverNodePath   m_TrackNodePath;
        TrackerMode             m_eTrackerMode;


        double m_dAngleH;
        double m_dAngleV;
        double m_dDistance;
        double m_dMinDistance;
        bool   m_bMinDistanceRelative;// 最小距离是绝对的还是相对于模型大小的

        osg::Vec3d m_vCenter;
        osg::Quat  m_qRotation;


        double m_dZoomFactorWheel;
        observer_ptr<IVBF_View> m_opView;


};

}

#endif /* OSGGA_NODE_TRACKER_MANIPULATOR */
