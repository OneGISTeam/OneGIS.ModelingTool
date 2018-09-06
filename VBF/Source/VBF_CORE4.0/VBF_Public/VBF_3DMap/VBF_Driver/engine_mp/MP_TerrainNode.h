#ifndef OSGEARTH_ENGINE_MP_TERRAIN_NODE
#define OSGEARTH_ENGINE_MP_TERRAIN_NODE 1

#include "Common"
#include "MP_TileNodeRegistry.h"

class TileFactory;

using namespace osgEarth;

// 地形节点，是CMP_TerrainEngineNode的子节点，是CMP_TileNode mp的父节点
class CMP_TerrainNode : public osg::CVBF_SGNodeGroup
{
public:

	/**
	* Constructs a new terrain node.
	* @param[in ] deadTiles If non-NULL, the terrain node will active GL object
	*             quick-release and use this registry to track dead tiles.
	*/
	CMP_TerrainNode( CMP_TileNodeRegistry* deadTiles );

public: // osg::Node

	virtual void traverse( osg::NodeVisitor &nv );

protected:

	virtual ~CMP_TerrainNode() { }

	ref_ptr<CMP_TileNodeRegistry> _tilesToQuickRelease;
	bool _quickReleaseCallbackInstalled;
};

#endif // OSGEARTH_ENGINE_MP_TERRAIN_NODE
