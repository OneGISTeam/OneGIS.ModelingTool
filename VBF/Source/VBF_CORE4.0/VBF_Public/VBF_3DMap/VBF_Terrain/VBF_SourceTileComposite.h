#ifndef OSGEARTH_COMPOSITE_TILE_SOURCE_H
#define OSGEARTH_COMPOSITE_TILE_SOURCE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>


// �������ø�����Ƭ����Դ
class OSGEARTH_EXPORT CVBF_OptionsDriverSourceTileComposite : public CVBF_OptionsDriverSourceTile
{
public:
    CVBF_OptionsDriverSourceTileComposite( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );
    virtual ~CVBF_OptionsDriverSourceTileComposite() { }

    // ���һ��ͼ��ͼ���������Ϣ
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

// ���ϵ���Ƭ����Դ����1��������Ƭ����Դ��ɣ���ͼ��ʹ�ã�
class OSGEARTH_EXPORT CVBFO_SourceTileComposite : public CVBFO_SourceTile
{
public:
    CVBFO_SourceTileComposite( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );
    virtual ~CVBFO_SourceTileComposite() { }

	// ���һ���Ѿ����ڵ���Ƭ����Դ��ֻ���ڳ�ʼ����initialized��ǰ��ӣ��ڼ���Map֮ǰ�������򷵻�false 
    bool add( CVBFO_SourceTile* tileSource );
        
	// ͬ�ϣ�ʹ��optionsͼ��ͼ��ѡ��
    bool add( CVBFO_SourceTile* tileSource, const ImageLayerOptions& options );

public: 
        
	// ����CVBFO_SourceTile����
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
