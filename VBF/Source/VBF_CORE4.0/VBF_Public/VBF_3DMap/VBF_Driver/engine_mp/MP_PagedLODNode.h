#ifndef OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
#define OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD 1

#include "Common"
#include "MP_TileNode.h"
#include "MP_TileNodeRegistry.h"
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODPaged.h>

using namespace osgEarth;

// 当TileNodes被加到场景图中时，CMP_PagedLOD会自动注册
class CMP_PagedLOD : public osg::PagedLOD
{
public:
	CMP_PagedLOD( CMP_TileNodeRegistry* liveTiles, CMP_TileNodeRegistry* deadTiles );
	virtual ~CMP_PagedLOD();

public: // osg::Group

    // 重载Group的方法，是为了把TileNode添加到场景图时自动注册分页节点，添加到任何父节点时都会发生AddChild，
    // 但本实现DatabasePager是唯一的入口
    // DatabasePager仅是添加和移除子节点，本类还实现一些其他的方法(插入、替换等)
	bool addChild( osg::IVBF_SGNode* child );
	bool removeChildren(unsigned pos, unsigned numChildrenToRemove );

private:

	ref_ptr<CMP_TileNodeRegistry> _live, _dead;
};

#endif // OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
