#ifndef OSGGA_NODE_TRACKER_MANIPULATOR
#define OSGGA_NODE_TRACKER_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorOrbit.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObserverNodePath.h>


namespace osgGA {

// 节点跟踪操作器
class OSGGA_EXPORT NodeTrackerManipulator : public OrbitManipulator
{
        typedef OrbitManipulator inherited;

    public:

        NodeTrackerManipulator( int flags = DEFAULT_SETTINGS );

        NodeTrackerManipulator( const NodeTrackerManipulator& om, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, NodeTrackerManipulator );

        void setTrackNodePath(const osg::CVBF_SGNodePath& nodePath);
        void setTrackNodePath(const osg::ObserverNodePath& nodePath) { _trackNodePath = nodePath; }
        osg::ObserverNodePath& getTrackNodePath() { return _trackNodePath; }

        void setTrackNode(osg::IVBF_SGNode* node);
        osg::IVBF_SGNode* getTrackNode() { osg::CVBF_SGNodePath nodePath; return _trackNodePath.getNodePath(nodePath) && !nodePath.empty() ? nodePath.back() : 0; }
        const osg::IVBF_SGNode* getTrackNode() const { osg::CVBF_SGNodePath nodePath; return _trackNodePath.getNodePath(nodePath) && !nodePath.empty()  ? nodePath.back() : 0; }

        enum TrackerMode
        {
            // 跟踪包围球的中心，但不旋转节点.For databases which have a CoordinateSystemNode, the orientation is kept relative the coordinate frame if the center of the node.             
            NODE_CENTER,
            
			// 跟踪包围球的中心，并绕Z轴旋转.For databases which have a CoordinateSystemNode, the orientation is kept relative the coordinate frame if the center of the node.
            NODE_CENTER_AND_AZIM,

			// 跟踪包围球的中心，并与模型一起旋转
            NODE_CENTER_AND_ROTATION
        };

        void setTrackerMode(TrackerMode mode);
        TrackerMode getTrackerMode() const { return _trackerMode; }


        enum RotationMode
        {
            // Use a trackball style manipulation of the view direction w.r.t the tracked orientation.
            TRACKBALL,
            // Allow the elevation and azimuth angles to be adjust w.r.t the tracked orientation.
            ELEVATION_AZIM
        };

        void SetRotationMode(RotationMode mode);
        RotationMode GetRotationMode() const;


        virtual void setByMatrix(const osg::Matrixd& matrix);
        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;

        virtual void setNode(osg::IVBF_SGNode*);

        //virtual void computeHomePosition();
        virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false);// 计算默认位置

        virtual bool IsFixedNearFar(){ return true;}

    protected:

        virtual bool performMovementLeftMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementMiddleMouseButton(double eventTimeDelta, double dx, double dy);
        virtual bool performMovementRightMouseButton(double eventTimeDelta, double dx, double dy);

        void computeNodeWorldToLocal(osg::Matrixd& worldToLocal) const;
        void computeNodeLocalToWorld(osg::Matrixd& localToWorld) const;

        void computeNodeCenterAndRotation(osg::Vec3d& center, osg::Quat& rotation) const;

        void computePosition(const osg::Vec3d& eye,const osg::Vec3d& lv,const osg::Vec3d& up);


        osg::ObserverNodePath   _trackNodePath;
        TrackerMode             _trackerMode;

};

}

#endif /* OSGGA_NODE_TRACKER_MANIPULATOR */
