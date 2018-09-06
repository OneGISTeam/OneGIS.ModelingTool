#ifndef OSGEARTH_ENGINE_MP_TILE_MODEL_FACTORY
#define OSGEARTH_ENGINE_MP_TILE_MODEL_FACTORY 1

#include "Common"
#include "MP_TileNode.h"
#include "MP_TileNodeRegistry.h"
#include "MP_ConfigOptionsTerrain.h"
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Common/VBF_Utils/VBF_CacheLRU.h>
#include <VBF_3DMap/VBF_Terrain/HeightFieldUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>


using namespace osgEarth;

struct HFKey 
{
	CVBF_TileKey _key;
	bool m_bFallback;
	bool m_bConvertToHAE;
	ElevationSamplePolicy _samplePolicy;

	bool operator < (const HFKey& rhs) const
	{
		if ( _key < rhs._key ) return true;
		if ( rhs._key < _key ) return false;
		if ( m_bFallback != rhs.m_bFallback ) return true;
		if ( m_bConvertToHAE != rhs.m_bConvertToHAE ) return true;
		return _samplePolicy < rhs._samplePolicy;
	}
};

struct HFValue 
{
	ref_ptr<osg::HeightField> _hf;
	bool                      m_bFallback;
};        

class CMP_HeightFieldCache : public ::CVBF_Referenced, public Revisioned
{
public:
	CMP_HeightFieldCache():
	  _cache( true, 128 )
	  {
	  }

	  bool getOrCreateHeightField( const CVBF_MapFrame& frame, const CVBF_TileKey& key, bool bFallback,
		  ref_ptr<osg::HeightField>& out_hf, bool* out_isFallback = 0L, bool  bToHAE = true,
		  ElevationSamplePolicy samplePolicy = SAMPLE_FIRST_VALID, ProgressCallback* progress =0L ) const
	  {                
		  // 检查缓存中是否存在
		  HFKey cachekey;
		  cachekey._key            = key;
		  cachekey.m_bFallback     = bFallback;
		  cachekey.m_bConvertToHAE = bToHAE;
		  cachekey._samplePolicy   = samplePolicy;

		  CVBF_CacheLRU<HFKey,HFValue>::Record rec;
		  if ( _cache.get(cachekey, rec) )
		  {
			  out_hf = rec.value()._hf.get();
			  if ( out_isFallback ) *out_isFallback = rec.value().m_bFallback;
			  return true;
		  }

		  // 缓存中不存在，创建

		  bool isFallback;
		  bool ok = frame.getHeightField( key, bFallback, out_hf, &isFallback, bToHAE, samplePolicy, progress );
		  if ( !ok ) return false;

		  // 对于Plate Carre投影，把高程值转换为度
		  const CVBF_MapInfo& mapInfo = frame.GetMapInfo();
		  if ( mapInfo.isPlateCarre() )
		  {
			  HeightFieldUtils::scaleHeightFieldToDegrees( out_hf.get() );
		  }

		  if ( out_isFallback ) *out_isFallback = isFallback;

		  // 加入缓存
		  HFValue cacheval;
		  cacheval._hf = out_hf.get();
		  cacheval.m_bFallback = isFallback;
		  _cache.insert( cachekey, cacheval );

		  return true;
	  }

	  void clear()
	  {
		  _cache.clear();
	  }

private:
	mutable CVBF_CacheLRU<HFKey,HFValue> _cache;
};


// 根据地图（map）数据模型，创建指定键值的瓦片数据模型
class CMP_TileModelFactory : public ::CVBF_Referenced
{
public:
	CMP_TileModelFactory( const CVBF_Map* map, CMP_TileNodeRegistry* liveTiles, const CMP_ConfigOptionsTerrain& terrainOptions );

	CMP_HeightFieldCache* getHeightFieldCache() const;
	virtual ~CMP_TileModelFactory() { }

	void createTileModel(const CVBF_TileKey& key, ref_ptr<CMP_TileModel>& ipTileModel_Out,
		                 bool& bHasRealData_Out, bool& bHasLodBlendedLayers_Out);

private:        

	const CVBF_Map*							m_pMap;
	ref_ptr<CMP_TileNodeRegistry>			m_pLiveTiles;
	const CMP_ConfigOptionsTerrain&			m_TerrainOptions;
	ref_ptr<CMP_HeightFieldCache>			m_pHFCache;
};


#endif // OSGEARTH_ENGINE_MP_TILE_MODEL_FACTORY
