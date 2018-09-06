#ifndef VBF_MANIPULATOR_TRACKER_FIX_ABSOLUTE
#define VBF_MANIPULATOR_TRACKER_FIX_ABSOLUTE 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorStandard.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObserverNodePath.h>
#include <VBF_Base/observer_ptr>

namespace osgGA {

// �ڵ���ٲ�����,��һ�ܷɻ�����һ�ܷɻ���Ч����ӵ��濴�ɻ���Ч������ʾ������
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
            CAMERA_POS_FIX,    // �̶����λ�ã���վ�ڵ���۲�һ�ܷɻ�
            CAMERA_POS_DYNAMIC // ��̬���λ�ã�����һ�ܷɻ��Ϲ۲���һ�ܷɻ�
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

        virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false);// ����Ĭ��λ��

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

        observer_ptr<osg::IVBF_SGNode> m_opEyeNode; // ����λ�ã�����CAMERA_POS_DYNAMICģʽ
        osg::Vec3d m_vEye;                           // ����λ�ã�����CAMERA_POS_FIXģʽ

        osg::Vec3d m_vCenter;
        osg::Quat  _rotation;

        double m_dDistance;

};

}

#endif /* OSGGA_NODE_TRACKER_MANIPULATOR */
