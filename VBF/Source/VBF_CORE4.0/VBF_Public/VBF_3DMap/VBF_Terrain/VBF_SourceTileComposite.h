#ifndef OSGEARTH_COMPOSITE_TILE_SOURCE_H
#define OSGEARTH_COMPOSITE_TILE_SOURCE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>


// 用于配置复合瓦片数据源
class OSGEARTH_EXPORT CVBF_OptionsDriverSourceTileComposite : public CVBF_OptionsDriverSourceTile
{
public:
    CVBF_OptionsDriverSourceTileComposite( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );
    virtual ~CVBF_OptionsDriverSourceTileComposite() { }

    // 添加一个图像图层的配置信息
    void add( const ImageLayerOptions& options );

public:
    virtual CVBF_Config getConfig() const;
protected:
    virtual void mergeConfig( const CVBF_Config& conf );
private:
    void fromConfig( const CVBF_Config& conf );

    struct Component 
	{
        CVBF_Optional<ImageLayerOptions> _imageLayerOptions;
        ref_ptr<CVBFO_SourceTile>        _tileSourceInstance;
    };

    typedef std::vector<Component> ComponentVector;
    ComponentVector _components;

    friend class CVBFO_SourceTileComposite;
};

// 复合的瓦片数据源（由1个或多个瓦片数据源组成，供图层使用）
class OSGEARTH_EXPORT CVBFO_SourceTileComposite : public CVBFO_SourceTile
{
public:
    CVBFO_SourceTileComposite( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );
    virtual ~CVBFO_SourceTileComposite() { }

	// 添加一个已经存在的瓦片数据源，只能在初始化（initialized）前添加（在加入Map之前），否则返回false 
    bool add( CVBFO_SourceTile* tileSource );
        
	// 同上，使用options图像图层选项
    bool add( CVBFO_SourceTile* tileSource, const ImageLayerOptions& options );

public: 
        
	// 重载CVBFO_SourceTile函数
    virtual osg::Image* createImage( const CVBF_TileKey& key, ProgressCallback* progress =0 );
    virtual bool isDynamic() const { return _dynamic; }
    Status initialize( const osgDB::Options* dbOptions );

protected:
    CVBF_OptionsDriverSourceTileComposite         _options;
    bool                               _initialized;
    bool                               _dynamic;
    ref_ptr<const osgDB::Options> _dbOptions;
       
    CVBF_OptionsDriverSourceTileComposite::ComponentVector _components;
};


#endif // OSGEARTH_COMPOSITE_TILE_SOURCE_H
