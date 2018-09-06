#ifndef OSGEARTH_MAP_H
#define OSGEARTH_MAP_H 1

#include <VBF_3DMap/VBF_Terrain/IVBF_Map.h>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapOptions.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapCallback.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainElevation.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerModel.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerMask.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>


// 包含各种图层和渲染选项，每个图层包含实际的数据。CVBF_Map是CVBFO_SGNodeMap渲染的主要数据模型。

// 通过earth文件创建图层时，可以指定多个影像数据源和多个高程数据源，数据源的顺序决定渲染顺序，
// 在earth文件中处于最前的在渲染时处于最底层渲染；所以如果有高低精度不同的影响数据或者高程数据，
// 在创建earth文件时要将粗精度的数据放在上方xml节点，高精度的放在其下面的节点；
class OSGEARTH_EXPORT CVBF_Map : public IVBF_Map
{
	friend class CVBF_MapInfo;
public:
    CVBF_Map( const CVBF_OptionsMap& options =CVBF_OptionsMap() );

public:
    // 获取控制图特征的选项
    const CVBF_OptionsMap& GetMapOptions() const { return m_MapOptions; }

    // 获取图初始创建的选项
    const CVBF_OptionsMap& getInitialMapOptions() const { return m_MapOptionsInit; }

	// 1、获取地图的总体信息

	// 获取图的master profile，该值在调用autoCalculateProfile之后才可用
    const CVBF_Profile* getProfile() const;

	// 获取空间参考
    const CVBF_SpatialReference* getSRS() const { return m_ipProfile.valid() ? m_ipProfile->getSRS() : 0L; }


	// 2、获取地图的图层

	// 2.1 Image图层  
    int getNumImageLayers() const;// 获取影像图层的数量
    Revision getImageLayers( CVBF_LayersImage& out_layers ) const;// 把影像图层的引用拷贝到输出列表，该方法是线程安全的，返回修订本（当数据拷贝时才生效）       	
    IVBF_MapLayer* getImageLayerByName( const std::string& name ) const;// 通过名字获取影像图层
    IVBF_MapLayer* getImageLayerByUID( UID layerUID ) const;// 通过ID获取影像图层
    IVBF_MapLayer* getImageLayerAt( int index ) const;// 通过索引获取影像图层

	// 2.2 高程图层
	int getNumElevationLayers() const;// 获取高程图层的数量  
	Revision getElevationLayers( CVBF_LayerTerrainElevations& out_layers ) const;// 把高程图层的引用拷贝到输出列表，该方法是线程安全的 
    IVBF_MapLayer* getElevationLayerByName( const std::string& name ) const;// 通过名字获取高程图层
    IVBF_MapLayer* getElevationLayerByUID( UID layerUID ) const;// 通过ID获取高程图层
    IVBF_MapLayer* getElevationLayerAt( int index ) const;// 通过索引获取高程图层

	// 2.3 模型图层（基本是矢量图层）
	int getNumModelLayers() const;// 通过索引获取模型图层
	Revision getModelLayers( CVBF_LayersModel& out_layers ) const;// 把模型图层的引用拷贝到输出列表，该方法是线程安全的
    IVBF_MapLayer* getModelLayerByName( const std::string& name ) const;// 通过名字获取模型图层
    IVBF_MapLayer* getModelLayerByUID( UID layerUID ) const;// 通过ID获取模型图层
    IVBF_MapLayer* getModelLayerAt( int index ) const;// 通过索引获取模型图层


    virtual bool AddModelLayer(const std::string& strFileName);
    virtual void RemoveModelLayer(const std::string& strFileName);
    virtual void AddModelLayers(const CVBF_Config& conf);// 从配置文件添加矢量图层（与earth一致）
    virtual void AddModelLayer(const CVBF_Config& conf);// 从配置文件添加矢量图层（与earth一致）
    virtual bool AddImageLayer(const std::string& strFileName);// 从配置文件添加图像图层（与earth一致）
    virtual void RemoveImageLayer(const std::string& name);
    virtual void AddImageLayers(const CVBF_Config& conf);// 从配置文件添加图像图层（与earth一致）
    virtual void AddImageLayer(const CVBF_Config& conf);// 从配置文件添加图像图层（与earth一致）
    virtual bool AddElevationLayer(const std::string& strFileName);// 从配置文件添加高程图层（与earth一致）
    virtual void RemoveElevationLayer(const std::string& name);
    virtual void AddElevationLayers(const CVBF_Config& conf);// 从配置文件添加高程图层（与earth一致）
    virtual void AddElevationLayer(const CVBF_Config& conf);// 从配置文件添加高程图层（与earth一致）


	// 2.4 Mask图层   
    int getTerrainMaskLayers( CVBF_LayersMask& out_list ) const;// 把地形Mask图层的引用拷贝到输出列表，该方法是线程安全的


	// 3、添加/移除图层
   
	// 3.0 在所有图层上的操作	
    void addMapCallback( CVBF_MapCallback* callback ) const;// 添加Map changed回调，这些回调在图层被添加、移除或调整顺序时被调用
    void removeMapCallback( CVBF_MapCallback* callback );	// 移除Map changed回调

    void beginUpdate(); // 1、开始/结束一批操作，如果想一次添加多个图层时调用，添加图层后调用 endUpdate()
    void endUpdate();	// 2、在beginUpdate()和endUpdate()之间, 不激发任何callbacks（在addMapCallback中添加的）
	
    void clear();// 清除所有图层
	
    void setLayersFromMap( const CVBF_Map* map );// 用map的图层替换this的图层（除了地形掩饰图层）


	// 3.1 Image图层    
    void addImageLayer( CVBF_LayerTerrainImage* pLayer );// 添加一个图像图层
    void insertImageLayer( CVBF_LayerTerrainImage* pLayer, unsigned int index );// 插入一个图像图层
    void removeImageLayer( CVBF_LayerTerrainImage* pLayer );// 移除一个图像图层
    void moveImageLayer( CVBF_LayerTerrainImage* pLayer, unsigned int newIndex );// 移动一个影像图层（把图层移到列表中另一个索引位置）

	// 3.2 高程图层	
    void addElevationLayer( CVBF_LayerTerrainElevation* pLayer );	// 添加一个高程图层
    void removeElevationLayer( CVBF_LayerTerrainElevation* pLayer );// 移除一个高程图层	
    void moveElevationLayer( CVBF_LayerTerrainElevation* pLayer, unsigned int newIndex );// 移动一个高程图层（把图层移到列表中另一个索引位置）

	// 3.3 模型图层	
    void addModelLayer( CVBF_LayerModel* pLayer );	// 添加一个模型图层
    void insertModelLayer( CVBF_LayerModel* pLayer, unsigned int index );// 插入一个模型图层
    void removeModelLayer( CVBF_LayerModel* pLayer );// 移除一个模型图层	
    void moveModelLayer( CVBF_LayerModel* pLayer, unsigned int newIndex );// 移动一个模型图层（把图层移到列表中另一个索引位置）

	// 3.4 Mask图层	
    void addTerrainMaskLayer( CVBF_LayerMask* pLayer );		// 添加一个地形掩饰图层
    void removeTerrainMaskLayer( CVBF_LayerMask* pLayer );	// 移除一个地形掩饰图层

    CVBF_Config GetConfigFromFile(const std::string& strFileName);

public:
	// 获取用户提供的（user-provided）选项
    const osgDB::ReaderWriter::Options* getGlobalOptions() const;
    void setGlobalOptions( const osgDB::ReaderWriter::Options* options );

	// 设置/获取名字
    void setName( const std::string& name );
    const std::string& getName() const { return m_sName; }

    // 根据TileKey获取高程图，如果需要，降低分辨率
    /** * 说明: 缺省情况下，返回大地高（HAE，height above ellipsoid）高程图，即使TileKey profile是平均海平面（MSL，mean sea level）垂直基准。
        * 这是因为该函数常用于产生一个可绘制的高程图，可以通过设置参数convertToHAE=false改变这一行为。
        *
        * 参数key：					定义高程图的区域和理想的LOD
        * 参数fallbackIfNecessary：	如果不能生成该键值对应的高程图，降低LOD，直到能够生成
        * 参数out_hf：				返回生成的高程图
        * 参数out_isFallback：		告诉调用者是否降低了分辨率
        * 参数convertToHAE：			返回的高程图是否转换为大地高
        * 参数samplePolicy：			采样（插值）策略
        * 参数progress：				(optional) progress callback.
        */
    bool getHeightField( const CVBF_TileKey& key, bool fallbackIfNeessary, 
				ref_ptr<osg::HeightField>& out_hf, bool* out_isFallback =0L, bool bToHAE =true, 
				ElevationSamplePolicy samplePolicy = SAMPLE_FIRST_VALID, ProgressCallback* progress =0L)const;

	// 设置/获取缓存，NULL表示不用缓存
    void   setCache( Cache* cache );
    Cache* getCache() const;

	// 获取数据模型的修订本号（revision #）。每次添加、移除或移动图层，修订本号都会改变。
    Revision getDataModelRevision() const;

	// 判断map的坐标系统类型是否是地心坐标系统
    bool isGeocentric() const;

    // 把一个map frame同步到地图的当前版本，如果同步发生了则返回true，否则返回false
    bool sync( class CVBF_MapFrame& frame ) const;

    // 获取地图关联的数据库选项
    const osgDB::Options* getDBOptions() const { return _dbOptions.get(); }

    const CVBF_Profile* getProfileNoVDatum() const { return m_ipProfileNoVDatum.get(); }


    enum ModelParts 
	{
        IMAGE_LAYERS     = 1 << 0,
        ELEVATION_LAYERS = 1 << 1,
        TERRAIN_LAYERS   = IMAGE_LAYERS | ELEVATION_LAYERS,
        MODEL_LAYERS     = 1 << 2,
        MASK_LAYERS      = 1 << 3,
        MASKED_TERRAIN_LAYERS = TERRAIN_LAYERS | MASK_LAYERS,
        ENTIRE_MODEL     = 0xff
    };


protected:

    virtual ~CVBF_Map();

private:
    std::string					m_sName;		// 图名

    CVBF_OptionsMap       m_MapOptions;	// 地图选项
    const CVBF_OptionsMap m_MapOptionsInit;// 初始构造时传入的选项，开始时与m_MapOptions相同，但后来m_MapOptions可能被修改


    CVBF_LayersImage			m_ImageLayers;		// 影像图层
    CVBF_LayerTerrainElevations	m_ElevationLayers;	// 高程图层
    CVBF_LayersModel			m_ModelLayers;		// 模型图层
    CVBF_LayersMask				m_TerrainMaskLayers;// 地形掩饰图层

    MapCallbackList				_mapCallbacks;		// 回调

    ref_ptr<const osgDB::ReaderWriter::Options> _globalOptions;

    CVBF_ReadWriteMutex _mapDataMutex;

    ref_ptr<const CVBF_Profile> m_ipProfile;			// 概述
    ref_ptr<const CVBF_Profile> m_ipProfileNoVDatum;	

    ref_ptr<Cache> m_ipCache;		 // 缓存
    Revision	   _dataModelRevision;

    ref_ptr<osgDB::Options> _dbOptions;

private:
    void calculateProfile();
};


#endif // OSGEARTH_MAP_H
