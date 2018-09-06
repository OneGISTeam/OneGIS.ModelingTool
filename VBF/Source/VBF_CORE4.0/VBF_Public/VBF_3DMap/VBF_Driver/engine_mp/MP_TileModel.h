#ifndef OSGEARTH_ENGINE_MP_TILE_MODEL
#define OSGEARTH_ENGINE_MP_TILE_MODEL 1

#include "Common"
#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Engine/VBF_Terrain/Locator>
#include <VBF_Engine/VBF_Terrain/Layer>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <map>
#include <VBF_Aux/VBF_GLAux/VBF_ImageUtils.h>
#include "MP_ConfigOptionsTerrain.h"
#include <VBF_3DMap/VBF_Terrain/VBFO_GeoLocator.h>
using namespace osgEarth;

// 瓦片的高程数据
class CMP_TileElevationData
{
public:
	CMP_TileElevationData() { }
	virtual ~CMP_TileElevationData() { }

	CMP_TileElevationData( osgTerrain::HeightFieldLayer* pHeightFieldLayer, bool bFallbackData =false )
		: _hfLayer(pHeightFieldLayer), m_bFallbackData(bFallbackData) 
	{ 
	}

	osgTerrain::HeightFieldLayer* getHFLayer() const { return _hfLayer.get(); }
	bool isFallbackData() const { return m_bFallbackData; }

	osg::HeightField* getNeighbor(int xoffset, int yoffset) const
	{
		int idx = getNeighborIndex(xoffset, yoffset);
		return m_ipNeighbourHeightFields[idx];
	}

	void setNeighbor(int xoffset, int yoffset, osg::HeightField* hf )
	{
		int idx = getNeighborIndex(xoffset, yoffset);
		m_ipNeighbourHeightFields[idx] = hf;
	}

private:
	// 西北 = 0，北 = 1，东北 = 2，西 = 3，东 = 4，西南 = 5，南 = 6，东南 = 7
	static int getNeighborIndex(int xoffset, int yoffset)
	{
		int idx = 3*(yoffset+1)+(xoffset+1);
		if (idx > 4) idx--;
		return idx;
	}
	ref_ptr<osgTerrain::HeightFieldLayer> _hfLayer;
	bool m_bFallbackData;
	ref_ptr<osg::HeightField> m_ipNeighbourHeightFields[8];
};

// 瓦片的颜色（影像数据），仅一层的数据
class CMP_TileColorData : public IVBF_LayerObserver
{
public:
    CMP_TileColorData():IVBF_LayerObserver(true)
    {
        m_bDirty = false;
    }
    virtual ~CMP_TileColorData()
    {
        if(m_ipLayer.valid()) m_ipLayer->RemoveObserver(this);
    }

    CMP_TileColorData( CVBF_LayerTerrainImage* imageLayer, unsigned order, osg::Image* image,
        const osgTerrain::Locator* locator, int lod, const CVBF_TileKey& key, const CMP_ConfigOptionsTerrain* opt,bool bFallbackData =false ):
        IVBF_LayerObserver(true),
        m_ipLayer(imageLayer),
        m_nOrder(order),
        m_ipLocator(locator),
        m_ipImage(image),
		m_TileKey(key),
        m_nLod(lod),
        m_bFallbackData(bFallbackData),
        m_pOptionsTerrain( opt )
	{ 
        m_bDirty = false;
        m_ipLayer->AddObserver(this);
	}

	CMP_TileColorData( const CMP_TileColorData& rhs ) :
        IVBF_LayerObserver(true),
        m_ipLayer( rhs.m_ipLayer.get() ),
        m_nOrder( rhs.m_nOrder ),
        m_ipLocator( rhs.m_ipLocator.get() ),
        m_ipImage( rhs.m_ipImage.get() ),
		m_TileKey( rhs.m_TileKey ),
        m_nLod( rhs.m_nLod ),
        m_bFallbackData( rhs.m_bFallbackData ),
        m_pOptionsTerrain( rhs.m_pOptionsTerrain )
    {
        m_bDirty = false;
        if(m_ipLayer.valid()) m_ipLayer->AddObserver(this);
    }

    osgEarth::UID getUID() const { return m_ipLayer->getUID(); }

    unsigned getOrder() const { return m_nOrder; }

    const osgTerrain::Locator* getLocator() const { return m_ipLocator.get(); }

    void ReLoadImage() // 与BuildColorData.execute()重复，优化
    {
        m_ipImage = NULL;
        const CVBF_Profile* pLayerProfile = m_ipLayer->getProfile();
        CVBFO_SourceTile*   pTileSource   = m_ipLayer->getTileSource();
        if (pLayerProfile == NULL || pTileSource==NULL) return;
        OSG_NOTICE<< "ReLoad"
                  << m_TileKey.GetLOD() << "_"
                  << m_TileKey.getTileX() << "_"
                  << m_TileKey.getTileY() << "_"
                  << std::endl;

        // 判断是否存在数据，不存在则直接返回
        CVBF_GeoExtent ext = m_TileKey.getExtent();
        if (!pLayerProfile->getSRS()->isEquivalentTo( ext.getSRS()))
        {
            ext = pLayerProfile->clampAndTransformExtent( ext );
        }
        bool hasDataInExtent = pTileSource->hasDataInExtent( ext );
        if (hasDataInExtent==false) return;


        // 从图层获取数据，找不到时降低分辨率，直到找到
        bool bUseMercatorFastPath = m_pOptionsTerrain->enableMercatorFastPath() != false &&
            pLayerProfile->getSRS()->isSphericalMercator();

        CVBF_TileKey imageKey( m_TileKey );
        bool bAutoFallback = m_TileKey.GetLOD() <= 1;

        GeoImage geoImage;
        bool isFallbackData = false;
        while( imageKey.valid() && m_ipLayer->isKeyValid(imageKey) )
        {
            if ( bUseMercatorFastPath )
            {
                bool bMercFallbackData = false;
                geoImage = m_ipLayer->createImageInNativeProfile( imageKey, 0L, bAutoFallback, bMercFallbackData );
                if ( geoImage.valid() && bMercFallbackData ) isFallbackData = true;
            }
            else
            {
                geoImage = m_ipLayer->createImage( imageKey, 0L, bAutoFallback );
//                geoImage = m_ipLayer->createImage( imageKey, 0L );
            }

            if ( geoImage.valid() )break;

            imageKey = imageKey.createParentKey();
            isFallbackData = true;
        }

        if ( !geoImage.valid() ) return;

        // 把影像转换到PMA，必须在CPU上进行。由于某些还不确定的原因，在着色器中进行纹理查询之后做此项工作会失败
        if ( m_pOptionsTerrain->premultipliedAlpha() == true )
        {
            ImageUtils::convertToPremultipliedAlpha( geoImage.getImage() );
        }

        m_bFallbackData = isFallbackData;

        m_ipImage = geoImage.getImage();
    }




	void ReleaseImage()
	{
		m_ipImage = NULL;
	}
    osg::Image* getImage()
    {
        if(m_bDirty)
        {
            ReLoadImage();
            m_bDirty = false;
        }
        return m_ipImage.get();
    }

	const CVBF_TileKey& getTileKey() const { return m_TileKey; }

    const CVBF_LayerTerrainImage* GetMapLayer() const { return m_ipLayer.get(); }

    int GetLOD() const { return m_nLod; }

	bool isFallbackData() const { return m_bFallbackData; }
    virtual void Dirty()
    {
        OSG_NOTICE<< "Dirty"
                  << m_TileKey.GetLOD() << "_"
                  << m_TileKey.getTileX() << "_"
                  << m_TileKey.getTileY() << "_"
                  << std::endl;

        m_bDirty = true;
    }
    bool IsDirty() { return m_bDirty; }
	void UnDirty() 
	{ 
		m_bDirty = false; 
		ReleaseImage();
	}

private:
    ref_ptr<CVBF_LayerTerrainImage>     m_ipLayer;  // 影像数据图层
    ref_ptr<const osgTerrain::Locator>  m_ipLocator;// 位置
    ref_ptr<osg::Image>                 m_ipImage;  // 图像数据
    CVBF_TileKey                        m_TileKey;
    int                                 m_nLod;
    bool                                m_bFallbackData;
    unsigned                            m_nOrder;
    const CMP_ConfigOptionsTerrain*     m_pOptionsTerrain;
    bool                                m_bDirty;

};


// 瓦片数据模型
class CMP_TileModel : public ::CVBF_Referenced
{
public:
	CMP_TileModel() { }
	virtual ~CMP_TileModel() { }

	ref_ptr<const CVBF_Map>          _map; // observer_ptr?
	CVBF_TileKey					 m_TileKey;
	ref_ptr<CVBFO_GeoLocator>		 m_ipTileLocator;

    std::map<UID, ref_ptr<CMP_TileColorData> > m_mapColorData;  // 纹理数据
	CMP_TileElevationData            m_ElevationData; // 高程数据

	ref_ptr<osg::StateSet>			 m_ipParentStateSet;
//  float                            _sampleRatio;
};

#endif // OSGEARTH_ENGINE_MP_TILE_MODEL
