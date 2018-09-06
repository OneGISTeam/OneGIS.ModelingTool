#ifndef OSGEARTH_ENGINE_MP_ENGINE_NODE_H
#define OSGEARTH_ENGINE_MP_ENGINE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeTerrainEngine.h>
#include <VBF_3DMap/VBF_Terrain/TextureCompositor.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

#include "MP_ConfigOptionsTerrain.h"
#include "IMP_KeyNodeFactory.h"
#include "MP_TileModelFactory.h"
#include "MP_TileModelCompiler.h"
#include "MP_TileNodeRegistry.h"

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

using namespace osgEarth;

class CMP_TerrainEngineNode : public CVBFO_SGNodeTerrainEngine
{
public:
	CMP_TerrainEngineNode();
	virtual ~CMP_TerrainEngineNode();

	META_Node(osgEarth,CMP_TerrainEngineNode);

public:
	osg::IVBF_SGNode* createNode(const CVBF_TileKey& key);

public: // CVBFO_SGNodeTerrainEngine

	// for standalone tile creation outside of a terrain
	osg::IVBF_SGNode* createTile(const CVBF_TileKey& key);

public: // internal CVBFO_SGNodeTerrainEngine

	virtual void preInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );
	virtual void postInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );
	virtual void validateTerrainOptions( CVBF_OptionsTerrain& options );
	virtual const CVBF_OptionsTerrain& getTerrainOptions() const { return _terrainOptions; }
	virtual osg::BoundingSphere computeBound() const;

        //xahg h00017
        virtual void traverse( osg::NodeVisitor& nv);
        //xahg h00017

public: // CVBF_MapCallback adapter functions
	void onMapInfoEstablished( const CVBF_MapInfo& mapInfo ); // not virtual!
	void onMapModelChanged( const CVBF_MapModelChange& change ); // not virtual!

	UID getUID() const;

public: // statics    
	static void registerEngine( CMP_TerrainEngineNode* engineNode );
	static void unregisterEngine( UID uid );
	static void getEngineByUID( UID uid, ref_ptr<CMP_TerrainEngineNode>& output );

public:
	class ElevationChangedCallback : public ElevationLayerCallback
	{
	public:
		ElevationChangedCallback( CMP_TerrainEngineNode* pTerrainEngineNode );

		virtual void onVisibleChanged( CVBF_LayerTerrain* layer );

		CMP_TerrainEngineNode* m_pMPTerrainEngineNode;
		friend class CMP_TerrainEngineNode;
	};

protected:
	virtual void onVerticalScaleChanged();

	// override from CVBFO_SGNodeTerrainEngine
	virtual void updateTextureCombining() { updateShaders(); }

private:
	void init();
	void syncMapModel();

	// Reloads all the tiles in the terrain due to a data model change
	void refresh();
	void createTerrain();

	void addImageLayer( CVBF_LayerTerrainImage* layer );
	void addElevationLayer( CVBF_LayerTerrainElevation* layer );

	void removeImageLayer( CVBF_LayerTerrainImage* layerRemoved );
	void removeElevationLayer( CVBF_LayerTerrainElevation* layerRemoved );

	void moveImageLayer( unsigned int oldIndex, unsigned int newIndex );
	void moveElevationLayer( unsigned int oldIndex, unsigned int newIndex );

	void updateShaders(); 

private:
	CMP_ConfigOptionsTerrain _terrainOptions;

	class CMP_TerrainNode* m_pTerrainNode;
	UID                _uid;
	Revision           _shaderLibRev;
	bool               _batchUpdateInProgress;
	bool               _refreshRequired;
	bool               _shaderUpdateRequired;

	ref_ptr< ElevationChangedCallback > _elevationCallback;

	CVBF_MapFrame* _update_mapf; // map frame for the main/update traversal thread

	// node registry is shared across all threads.
	ref_ptr<CMP_TileNodeRegistry> _liveTiles;      // tiles in the scene graph.
	ref_ptr<CMP_TileNodeRegistry> _deadTiles;        // tiles that used to be in the scene graph.

	CVBF_PerThread< ref_ptr<IMP_KeyNodeFactory> > _perThreadKeyNodeFactories;
	IMP_KeyNodeFactory* getKeyNodeFactory();

	CVBF_Timer _timer;
	unsigned   _tileCount;
	double     _tileCreationTime;
	int        _textureImageUnit;

	osg::Uniform* _verticalScaleUniform;

	ref_ptr< CMP_TileModelFactory > _tileModelFactory;

	CMP_TerrainEngineNode( const CMP_TerrainEngineNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ) { }
};

#endif // OSGEARTH_ENGINE_MP_ENGINE_NODE_H
