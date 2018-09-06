#ifndef VBF_MANIPULATOR_TRACKER_FIX_ABSOLUTE
#define VBF_MANIPULATOR_TRACKER_FIX_ABSOLUTE 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorStandard.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObserverNodePath.h>
#include <VBF_Base/observer_ptr>

namespace osgGA {

// 节点跟踪操作器,从一架飞机看另一架飞机的效果或从地面看飞机的效果，见示例程序
class OSGGA_EXPORT CVBF_ManipulatorTrackerFixA : public StandardManipulator
{
        typedef StandardManipulator inherited;

    public:
        CVBF_ManipulatorTrackerFixA( int flags = DEFAULT_SETTINGS );
        CVBF_ManipulatorTrackerFixA( const CVBF_ManipulatorTrackerFixA& om, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, CVBF_ManipulatorTrackerFixA );


        void setTrackNode(osg::IVBF_SGNode* pINode);
        osg::IVBF_SGNode* getTrackNode() { osg::CVBF_SGNodePath nodePath; return m_TrackNodePath.getNodePath(nodePath) && !nodePath.empty() ? nodePath.back() : 0; }
        const osg::IVBF_SGNode* getTrackNode() const { osg::CVBF_SGNodePath nodePath; return m_TrackNodePath.getNodePath(nodePath) && !nodePath.empty()  ? nodePath.back() : 0; }



        enum TrackerMode
        {                  
            CAMERA_POS_FIX,    // 固定相机位置，如站在地面观察一架飞机
            CAMERA_POS_DYNAMIC // 动态相机位置，如在一架飞机上观察另一架飞机
        };
        void setTrackerMode(TrackerMode mode);
        TrackerMode getTrackerMode() const { return m_eTrackerMode; }

        virtual void SetCameraPosition(const osg::Vec3d& vEye);
        virtual void SetCameraPosition(osg::IVBF_SGNode* pINode);

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

     protected:

        virtual bool handleFrame( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool performMovementLeftMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementMiddleMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementRightMouseButton(double eventTimeDelta, double dx, double dy);

        void computeNodeWorldToLocal(osg::Matrixd& worldToLocal) const;
        void computeNodeLocalToWorld(osg::Matrixd& localToWorld) const;

        osg::Vec3d ComputeCenter() const;

        void computePosition(const osg::Vec3d& eye,const osg::Vec3d& lv,const osg::Vec3d& up);

        osg::ObserverNodePath   m_TrackNodePath;
        TrackerMode             m_eTrackerMode;
        osg::ObserverNodePath   m_EyeNodePath;

        observer_ptr<osg::IVBF_SGNode> m_opEyeNode; // 设置位置，用于CAMERA_POS_DYNAMIC模式
        osg::Vec3d m_vEye;                           // 设置位置，用于CAMERA_POS_FIX模式

        osg::Vec3d m_vCenter;
        osg::Quat  _rotation;

        double m_dDistance;

};

}

#endif /* OSGGA_NODE_TRACKER_MANIPULATOR */
