#ifndef OSGEARTH_ENGINE_OSGTERRAIN_LOD_FACTOR_CALLBACK_H
#define OSGEARTH_ENGINE_OSGTERRAIN_LOD_FACTOR_CALLBACK_H 1

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>

// LOD»ìºÏÒò×Ó
struct CMP_LODFactorCallback : public osg::NodeCallback
{
	void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);
};

#endif
