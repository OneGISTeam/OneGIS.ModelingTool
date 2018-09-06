#ifndef OSGEARTH_ENGINE_KEY_NODE_FACTORY
#define OSGEARTH_ENGINE_KEY_NODE_FACTORY 1


#include "Common"
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>

using namespace osgEarth;

// 根据键值创建节点的工厂
class IMP_KeyNodeFactory : public ::CVBF_Referenced
{
public:
	// 根据键值创建顶级（根）的节点
	virtual osg::IVBF_SGNode* createRootNode( const CVBF_TileKey& key ) =0;

	// 根据键值创建节点
	virtual osg::IVBF_SGNode* createNode( const CVBF_TileKey& key ) =0;

	virtual class CMP_TileModelCompiler* getCompiler() const =0;

protected:
	IMP_KeyNodeFactory(){}
	virtual ~IMP_KeyNodeFactory() { }
};


#endif // OSGEARTH_ENGINE_KEY_NODE_FACTORY
