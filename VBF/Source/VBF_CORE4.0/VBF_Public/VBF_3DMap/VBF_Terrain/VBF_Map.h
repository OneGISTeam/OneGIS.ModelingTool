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


// ��������ͼ�����Ⱦѡ�ÿ��ͼ�����ʵ�ʵ����ݡ�CVBF_Map��CVBFO_SGNodeMap��Ⱦ����Ҫ����ģ�͡�

// ͨ��earth�ļ�����ͼ��ʱ������ָ�����Ӱ������Դ�Ͷ���߳�����Դ������Դ��˳�������Ⱦ˳��
// ��earth�ļ��д�����ǰ������Ⱦʱ������ײ���Ⱦ����������иߵ;��Ȳ�ͬ��Ӱ�����ݻ��߸߳����ݣ�
// �ڴ���earth�ļ�ʱҪ���־��ȵ����ݷ����Ϸ�xml�ڵ㣬�߾��ȵķ���������Ľڵ㣻
class OSGEARTH_EXPORT CVBF_Map : public IVBF_Map
{
	friend class CVBF_MapInfo;
public:
    CVBF_Map( const CVBF_OptionsMap& options =CVBF_OptionsMap() );

public:
    // ��ȡ����ͼ������ѡ��
    const CVBF_OptionsMap& GetMapOptions() const { return m_MapOptions; }

    // ��ȡͼ��ʼ������ѡ��
    const CVBF_OptionsMap& getInitialMapOptions() const { return m_MapOptionsInit; }

	// 1����ȡ��ͼ��������Ϣ

	// ��ȡͼ��master profile����ֵ�ڵ���autoCalculateProfile֮��ſ���
    const CVBF_Profile* getProfile() const;

	// ��ȡ�ռ�ο�
    const CVBF_SpatialReference* getSRS() const { return m_ipProfile.valid() ? m_ipProfile->getSRS() : 0L; }


	// 2����ȡ��ͼ��ͼ��

	// 2.1 Imageͼ��  
    int getNumImageLayers() const;// ��ȡӰ��ͼ�������
    Revision getImageLayers( CVBF_LayersImage& out_layers ) const;// ��Ӱ��ͼ������ÿ���������б��÷������̰߳�ȫ�ģ������޶����������ݿ���ʱ����Ч��       	
    IVBF_MapLayer* getImageLayerByName( const std::string& name ) const;// ͨ�����ֻ�ȡӰ��ͼ��
    IVBF_MapLayer* getImageLayerByUID( UID layerUID ) const;// ͨ��ID��ȡӰ��ͼ��
    IVBF_MapLayer* getImageLayerAt( int index ) const;// ͨ��������ȡӰ��ͼ��

	// 2.2 �߳�ͼ��
	int getNumElevationLayers() const;// ��ȡ�߳�ͼ�������  
	Revision getElevationLayers( CVBF_LayerTerrainElevations& out_layers ) const;// �Ѹ߳�ͼ������ÿ���������б��÷������̰߳�ȫ�� 
    IVBF_MapLayer* getElevationLayerByName( const std::string& name ) const;// ͨ�����ֻ�ȡ�߳�ͼ��
    IVBF_MapLayer* getElevationLayerByUID( UID layerUID ) const;// ͨ��ID��ȡ�߳�ͼ��
    IVBF_MapLayer* getElevationLayerAt( int index ) const;// ͨ��������ȡ�߳�ͼ��

	// 2.3 ģ��ͼ�㣨������ʸ��ͼ�㣩
	int getNumModelLayers() const;// ͨ��������ȡģ��ͼ��
	Revision getModelLayers( CVBF_LayersModel& out_layers ) const;// ��ģ��ͼ������ÿ���������б��÷������̰߳�ȫ��
    IVBF_MapLayer* getModelLayerByName( const std::string& name ) const;// ͨ�����ֻ�ȡģ��ͼ��
    IVBF_MapLayer* getModelLayerByUID( UID layerUID ) const;// ͨ��ID��ȡģ��ͼ��
    IVBF_MapLayer* getModelLayerAt( int index ) const;// ͨ��������ȡģ��ͼ��


    virtual bool AddModelLayer(const std::string& strFileName);
    virtual void RemoveModelLayer(const std::string& strFileName);
    virtual void AddModelLayers(const CVBF_Config& conf);// �������ļ����ʸ��ͼ�㣨��earthһ�£�
    virtual void AddModelLayer(const CVBF_Config& conf);// �������ļ����ʸ��ͼ�㣨��earthһ�£�
    virtual bool AddImageLayer(const std::string& strFileName);// �������ļ����ͼ��ͼ�㣨��earthһ�£�
    virtual void RemoveImageLayer(const std::string& name);
    virtual void AddImageLayers(const CVBF_Config& conf);// �������ļ����ͼ��ͼ�㣨��earthһ�£�
    virtual void AddImageLayer(const CVBF_Config& conf);// �������ļ����ͼ��ͼ�㣨��earthһ�£�
    virtual bool AddElevationLayer(const std::string& strFileName);// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�
    virtual void RemoveElevationLayer(const std::string& name);
    virtual void AddElevationLayers(const CVBF_Config& conf);// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�
    virtual void AddElevationLayer(const CVBF_Config& conf);// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�


	// 2.4 Maskͼ��   
    int getTerrainMaskLayers( CVBF_LayersMask& out_list ) const;// �ѵ���Maskͼ������ÿ���������б��÷������̰߳�ȫ��


	// 3�����/�Ƴ�ͼ��
   
	// 3.0 ������ͼ���ϵĲ���	
    void addMapCallback( CVBF_MapCallback* callback ) const;// ���Map changed�ص�����Щ�ص���ͼ�㱻��ӡ��Ƴ������˳��ʱ������
    void removeMapCallback( CVBF_MapCallback* callback );	// �Ƴ�Map changed�ص�

    void beginUpdate(); // 1����ʼ/����һ�������������һ����Ӷ��ͼ��ʱ���ã����ͼ������ endUpdate()
    void endUpdate();	// 2����beginUpdate()��endUpdate()֮��, �������κ�callbacks����addMapCallback����ӵģ�
	
    void clear();// �������ͼ��
	
    void setLayersFromMap( const CVBF_Map* map );// ��map��ͼ���滻this��ͼ�㣨���˵�������ͼ�㣩


	// 3.1 Imageͼ��    
    void addImageLayer( CVBF_LayerTerrainImage* pLayer );// ���һ��ͼ��ͼ��
    void insertImageLayer( CVBF_LayerTerrainImage* pLayer, unsigned int index );// ����һ��ͼ��ͼ��
    void removeImageLayer( CVBF_LayerTerrainImage* pLayer );// �Ƴ�һ��ͼ��ͼ��
    void moveImageLayer( CVBF_LayerTerrainImage* pLayer, unsigned int newIndex );// �ƶ�һ��Ӱ��ͼ�㣨��ͼ���Ƶ��б�����һ������λ�ã�

	// 3.2 �߳�ͼ��	
    void addElevationLayer( CVBF_LayerTerrainElevation* pLayer );	// ���һ���߳�ͼ��
    void removeElevationLayer( CVBF_LayerTerrainElevation* pLayer );// �Ƴ�һ���߳�ͼ��	
    void moveElevationLayer( CVBF_LayerTerrainElevation* pLayer, unsigned int newIndex );// �ƶ�һ���߳�ͼ�㣨��ͼ���Ƶ��б�����һ������λ�ã�

	// 3.3 ģ��ͼ��	
    void addModelLayer( CVBF_LayerModel* pLayer );	// ���һ��ģ��ͼ��
    void insertModelLayer( CVBF_LayerModel* pLayer, unsigned int index );// ����һ��ģ��ͼ��
    void removeModelLayer( CVBF_LayerModel* pLayer );// �Ƴ�һ��ģ��ͼ��	
    void moveModelLayer( CVBF_LayerModel* pLayer, unsigned int newIndex );// �ƶ�һ��ģ��ͼ�㣨��ͼ���Ƶ��б�����һ������λ�ã�

	// 3.4 Maskͼ��	
    void addTerrainMaskLayer( CVBF_LayerMask* pLayer );		// ���һ����������ͼ��
    void removeTerrainMaskLayer( CVBF_LayerMask* pLayer );	// �Ƴ�һ����������ͼ��

    CVBF_Config GetConfigFromFile(const std::string& strFileName);

public:
	// ��ȡ�û��ṩ�ģ�user-provided��ѡ��
    const osgDB::ReaderWriter::Options* getGlobalOptions() const;
    void setGlobalOptions( const osgDB::ReaderWriter::Options* options );

	// ����/��ȡ����
    void setName( const std::string& name );
    const std::string& getName() const { return m_sName; }

    // ����TileKey��ȡ�߳�ͼ�������Ҫ�����ͷֱ���
    /** * ˵��: ȱʡ����£����ش�ظߣ�HAE��height above ellipsoid���߳�ͼ����ʹTileKey profile��ƽ����ƽ�棨MSL��mean sea level����ֱ��׼��
        * ������Ϊ�ú��������ڲ���һ���ɻ��Ƶĸ߳�ͼ������ͨ�����ò���convertToHAE=false�ı���һ��Ϊ��
        *
        * ����key��					����߳�ͼ������������LOD
        * ����fallbackIfNecessary��	����������ɸü�ֵ��Ӧ�ĸ߳�ͼ������LOD��ֱ���ܹ�����
        * ����out_hf��				�������ɵĸ߳�ͼ
        * ����out_isFallback��		���ߵ������Ƿ񽵵��˷ֱ���
        * ����convertToHAE��			���صĸ߳�ͼ�Ƿ�ת��Ϊ��ظ�
        * ����samplePolicy��			��������ֵ������
        * ����progress��				(optional) progress callback.
        */
    bool getHeightField( const CVBF_TileKey& key, bool fallbackIfNeessary, 
				ref_ptr<osg::HeightField>& out_hf, bool* out_isFallback =0L, bool bToHAE =true, 
				ElevationSamplePolicy samplePolicy = SAMPLE_FIRST_VALID, ProgressCallback* progress =0L)const;

	// ����/��ȡ���棬NULL��ʾ���û���
    void   setCache( Cache* cache );
    Cache* getCache() const;

	// ��ȡ����ģ�͵��޶����ţ�revision #����ÿ����ӡ��Ƴ����ƶ�ͼ�㣬�޶����Ŷ���ı䡣
    Revision getDataModelRevision() const;

	// �ж�map������ϵͳ�����Ƿ��ǵ�������ϵͳ
    bool isGeocentric() const;

    // ��һ��map frameͬ������ͼ�ĵ�ǰ�汾�����ͬ���������򷵻�true�����򷵻�false
    bool sync( class CVBF_MapFrame& frame ) const;

    // ��ȡ��ͼ���������ݿ�ѡ��
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
    std::string					m_sName;		// ͼ��

    CVBF_OptionsMap       m_MapOptions;	// ��ͼѡ��
    const CVBF_OptionsMap m_MapOptionsInit;// ��ʼ����ʱ�����ѡ���ʼʱ��m_MapOptions��ͬ��������m_MapOptions���ܱ��޸�


    CVBF_LayersImage			m_ImageLayers;		// Ӱ��ͼ��
    CVBF_LayerTerrainElevations	m_ElevationLayers;	// �߳�ͼ��
    CVBF_LayersModel			m_ModelLayers;		// ģ��ͼ��
    CVBF_LayersMask				m_TerrainMaskLayers;// ��������ͼ��

    MapCallbackList				_mapCallbacks;		// �ص�

    ref_ptr<const osgDB::ReaderWriter::Options> _globalOptions;

    CVBF_ReadWriteMutex _mapDataMutex;

    ref_ptr<const CVBF_Profile> m_ipProfile;			// ����
    ref_ptr<const CVBF_Profile> m_ipProfileNoVDatum;	

    ref_ptr<Cache> m_ipCache;		 // ����
    Revision	   _dataModelRevision;

    ref_ptr<osgDB::Options> _dbOptions;

private:
    void calculateProfile();
};


#endif // OSGEARTH_MAP_H
