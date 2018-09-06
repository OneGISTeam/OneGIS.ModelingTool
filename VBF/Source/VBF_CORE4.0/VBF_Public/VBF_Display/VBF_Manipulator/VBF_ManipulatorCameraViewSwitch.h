#ifndef OSGGA_VIEWLISTMANIPULATOR
#define OSGGA_VIEWLISTMANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <Types/VBF_Quat.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformCameraView.h>

namespace osgGA{

class OSGGA_EXPORT CameraViewSwitchManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:
        CameraViewSwitchManipulator() {}
        virtual const char* className() const { return "CameraViewSwitcher"; }

        // 设置/获取矩阵操作器的位置（使用4x4矩阵/逆矩阵）
        virtual void setByMatrix(const osg::Matrixd& /*matrix*/) {}
        virtual void setByInverseMatrix(const osg::Matrixd& /*matrix*/) {}

        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;// 典型的用法是作为model view matrix


        /** Attach a node to the manipulator. 
            Automatically detaches previously attached node.
            setNode(NULL) detaches previously nodes.
            Is ignored by manipulators which do not require a reference model.*/
        virtual void setNode(osg::IVBF_SGNode*);

        /** Return node if attached.*/
        virtual const osg::IVBF_SGNode* getNode() const { return m_ipNode.get();}
        virtual osg::IVBF_SGNode* getNode() { return m_ipNode.get();}
        

        virtual void init(const GUIEventAdapter& /*ea*/,::IVBF_GUIActionAdapter& /*aa*/) { _currentView = 0; }
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        // 获取该操作器鼠标和键盘的用法
        virtual void GetUsage(::ApplicationUsage& usage) const;

       typedef std::vector< ref_ptr<osg::IVBF_SGNodeGroupTransformCameraView> > CameraViewList;

    protected:

        virtual ~CameraViewSwitchManipulator() {}

       ref_ptr<osg::IVBF_SGNode>       m_ipNode;

       CameraViewList _cameraViews;
       unsigned int _currentView;
};

}

#endif

