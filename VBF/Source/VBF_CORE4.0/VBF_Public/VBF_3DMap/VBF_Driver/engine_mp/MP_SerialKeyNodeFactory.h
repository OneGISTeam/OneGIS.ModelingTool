#ifndef OSGEARTH_ENGINE_MP_SERIAL_KEY_NODE_FACTORY
#define OSGEARTH_ENGINE_MP_SERIAL_KEY_NODE_FACTORY 1

#include "Common"
#include "IMP_KeyNodeFactory.h"
#include "MP_TerrainNode.h"
#include "MP_TileModelFactory.h"
#include "MP_TileNodeRegistry.h"
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>

using namespace osgEarth;

class CMP_SerialKeyNodeFactory : public IMP_KeyNodeFactory
{
public:
	CMP_SerialKeyNodeFactory( CMP_TileModelFactory*  modelFactory, CMP_TileModelCompiler* modelCompiler,
							  CMP_TileNodeRegistry*  liveTiles, CMP_TileNodeRegistry*  deadTiles,
							  const CMP_ConfigOptionsTerrain& options, const CVBF_MapInfo& mapInfo,
							  CMP_TerrainNode* terrain, UID engineUID );

	virtual ~CMP_SerialKeyNodeFactory() {}

	// IMP_KeyNodeFactory函数重载
	osg::IVBF_SGNode* createRootNode( const CVBF_TileKey& key ); // 创建根节点
	osg::IVBF_SGNode* createNode( const CVBF_TileKey& key );	 // 创建一般节点

	CMP_TileModelCompiler* getCompiler() const { return m_piModelCompiler.get(); }

protected:
	void addTile(CMP_TileModel* model, bool bTileHasRealData, bool bTileHasLodBlending, osg::IVBF_SGNodeGroup* parent );

protected:
	ref_ptr<CMP_TileModelFactory>		m_piModelFactory;
	ref_ptr<CMP_TileModelCompiler>		m_piModelCompiler;
	ref_ptr<CMP_TileNodeRegistry>		m_piLiveTiles;
	ref_ptr<CMP_TileNodeRegistry>		m_piDeadTiles;
	const CMP_ConfigOptionsTerrain&		m_Optinos;
	const CVBF_MapInfo					m_MapInfo;
	ref_ptr< CMP_TerrainNode >			m_piTerrainNode;
	UID									m_nEngineUID;
};

#endif // OSGEARTH_ENGINE_MP_SERIAL_KEY_NODE_FACTORY
