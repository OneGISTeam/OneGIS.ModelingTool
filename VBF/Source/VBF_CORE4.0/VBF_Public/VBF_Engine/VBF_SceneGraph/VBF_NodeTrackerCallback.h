#ifndef OSG_NODETRACKERCALLBACK
#define OSG_NODETRACKERCALLBACK 1

#include <iterator>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObserverNodePath.h>

namespace osg
{

class OSG_EXPORT NodeTrackerCallback : public NodeCallback
{
    public:

        void setTrackNodePath(const osg::CVBF_SGNodePath& nodePath) { _trackNodePath.setNodePath(nodePath); }

        void setTrackNodePath(const ObserverNodePath& nodePath) { _trackNodePath = nodePath; }

        ObserverNodePath& getTrackNodePath() { return _trackNodePath; }

        void setTrackNode(osg::IVBF_SGNode* node);
        osg::IVBF_SGNode* getTrackNode();
        const osg::IVBF_SGNode* getTrackNode() const;

        /** Update the node to track the nodepath.*/
        void update(osg::IVBF_SGNode& node);
        
		// NodeCallback接口实现
        virtual void operator()(IVBF_SGNode* node, NodeVisitor* nv);


    protected:

        ObserverNodePath _trackNodePath;

};

}

#endif
