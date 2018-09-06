#ifndef OSGEARTH_MASK_NODE_H
#define OSGEARTH_MASK_NODE_H 1

//!!!#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>


class OSGEARTH_EXPORT CVBFO_SGNodeMask : public osg::CVBF_SGNodeGroup
{
public:
    CVBFO_SGNodeMask();
    CVBFO_SGNodeMask( const CVBFO_SGNodeMask& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL );

    META_Node(osgEarth, CVBFO_SGNodeMask);

    virtual ~CVBFO_SGNodeMask() { }
};


#endif // OSGEARTH_MASK_NODE_H


