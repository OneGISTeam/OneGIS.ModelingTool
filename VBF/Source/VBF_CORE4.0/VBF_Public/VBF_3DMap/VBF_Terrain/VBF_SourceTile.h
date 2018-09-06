#ifndef OSGEARTH_TILE_SOURCE_H
#define OSGEARTH_TILE_SOURCE_H 1

// Need to undef Status in case it has been defined in Xlib.h. This can happen on Linux
#undef Status

#include <limits.h>

#include <VBF_Engine/VBF_SceneGraph/Version>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CacheMem.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>
#if OSG_MIN_VERSION_REQUIRED(2,9,5)
#include <VBF_Engine/VBF_SGDB/Options>
#endif
#include <VBF_Engine/VBF_SGDB/ReadFile>

#include <OpenThreads/Mutex>

#include <string>


#define TILESOURCE_CONFIG "tileSourceConfig"


// ��Ƭ����Դ��������������
class OSGEARTH_EXPORT CVBF_OptionsDriverSourceTile : public CVBF_OptionsDriver
{
public:

    CVBF_Optional<int>& tileSize() { return _tileSize; }
    const CVBF_Optional<int>& tileSize() const { return _tileSize; }

    CVBF_Optional<float>& noDataValue() { return _noDataValue; }
    const CVBF_Optional<float>& noDataValue() const { return _noDataValue; }

    CVBF_Optional<float>& noDataMinValue() { return _noDataMinValue; }
    const CVBF_Optional<float>& noDataMinValue() const { return _noDataMinValue; }

    CVBF_Optional<float>& noDataMaxValue() { return _noDataMaxValue; }
    const CVBF_Optional<float>& noDataMaxValue() const { return _noDataMaxValue; }

    CVBF_Optional<std::string>& blacklistFilename() { return _blacklistFilename; }
    const CVBF_Optional<std::string>& blacklistFilename() const { return _blacklistFilename; }

    CVBF_Optional<CVBF_OptionsProfile>& profile() { return _profileOptions; }
    const CVBF_Optional<CVBF_OptionsProfile>& profile() const { return _profileOptions; }

    CVBF_Optional<int>& L2CacheSize() { return _L2CacheSize; }
    const CVBF_Optional<int>& L2CacheSize() const { return _L2CacheSize; }

    CVBF_Optional<bool>& bilinearReprojection() { return _bilinearReprojection; }
    const CVBF_Optional<bool>& bilinearReprojection() const { return _bilinearReprojection; }

public:
    CVBF_OptionsDriverSourceTile( const CVBF_Options& options =CVBF_Options() );
    virtual ~CVBF_OptionsDriverSourceTile();
    CVBF_OptionsDriverSourceTile& operator = (const CVBF_OptionsDriverSourceTile& rhs);

public:
    virtual CVBF_Config getConfig() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf );

private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<int>            _tileSize;
    CVBF_Optional<float>          _noDataValue, _noDataMinValue, _noDataMaxValue;
    CVBF_Optional<CVBF_OptionsProfile> _profileOptions;
    CVBF_Optional<std::string>    _blacklistFilename;
    CVBF_Optional<int>            _L2CacheSize;
    CVBF_Optional<bool>           _bilinearReprojection;
};

typedef std::vector<CVBF_OptionsDriverSourceTile> TileSourceOptionsVector;


// ��Ƭ�ĺ������б�����Ҫ��ȡ��
class OSGEARTH_EXPORT TileBlacklist : public virtual CVBF_Referenced
{
public:
    TileBlacklist();
    virtual ~TileBlacklist() { }

    void add(const osgTerrain::TileID &tile);    // ����һ����Ƭ
    void remove(const osgTerrain::TileID& tile); // �Ƴ�һ����Ƭ
    void clear(); // ���

    bool contains(const osgTerrain::TileID &tile) const; // �Ƿ��������Ƭ
    unsigned int size() const;	// ��Ƭ����

    static TileBlacklist* read(std::istream &in);			// �����ж�ȡ������
    static TileBlacklist* read(const std::string &filename);// ���ļ���ȡ������

    void write(std::ostream &output) const;			// ������д�������
    void write(const std::string &filename) const;	// ���ļ�д�������

private:
    typedef std::set< osgTerrain::TileID > BlacklistedTiles;
    BlacklistedTiles	_tiles;	// ����������
    CVBF_ReadWriteMutex _mutex;	// �̱߳���
};

// ��Ƭ����Դ�����Դ���Ӱ��͸߳���Ƭ������������������𴴽�����������Դ����ͼ��CVBF_Map��ʹ�ø�����Դ������Ƭ
class OSGEARTH_EXPORT CVBFO_SourceTile : public virtual osg::CVBF_Object
{
public:
    struct Status // ����Դ��ʼ����״̬
    {
    public:
        Status() { }
        Status(const Status& rhs) : _msg(rhs._msg) { }
        Status(const std::string& msg) : _msg(msg) { }
        bool isOK() const { return _msg.empty(); }
        bool isError() const { return !_msg.empty(); }
        const std::string& message() const { return _msg; }
        bool operator == (const Status& rhs) const { return _msg.compare(rhs._msg)==0; }
        bool operator != (const Status& rhs) const { return _msg.compare(rhs._msg)!=0; }
        static Status Error(const std::string& msg) { return Status(msg); }
    private:
        std::string _msg;
    };

    static Status STATUS_OK;

public:
    struct ImageOperation : public ::CVBF_Referenced 
	{
        virtual void operator()( ref_ptr<osg::Image>& in_out_image ) =0;
    };

    struct HeightFieldOperation : public ::CVBF_Referenced 
	{
        virtual void operator()( ref_ptr<osg::HeightField>& in_out_hf ) =0;
    };

public:
    CVBFO_SourceTile( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );
	
    const Status& getStatus() const { return _status; } // ��ȡ����ƬԴ��״̬

    virtual int getPixelsPerTile() const;// ��ȡÿ����Ƭ��������

	// ��ȡ������Դ�����ݷ�Χ�б�
    const DataExtentList& getDataExtents() const { return _dataExtents; }
    DataExtentList& getDataExtents() { return _dataExtents; }

	// ���ݼ�ֵ����Ӱ�񣬼���CVBF_TileKey����profile�����������Դƥ��
    virtual osg::Image* createImage( const CVBF_TileKey& key, ImageOperation* op=0L, ProgressCallback* progress=0L );

	// ���ݼ�ֵ�����߳�ͼ������CVBF_TileKey����profile�����������Դƥ��
    virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, HeightFieldOperation* op=0L, ProgressCallback* progress=0L );

public:

	// ����Դ�Ƿ���ȷ��ʼ����������Ч��profile
    virtual bool isOK() const;
    bool isValid() const { return isOK(); }

    virtual const CVBF_Profile* getProfile() const;// ��ȡ����Դ��Profile	
    void setProfile( const CVBF_Profile* profile );// �������Factory���ã����ڳ�ʼ������Դ��profile

	// ��ȡ�����ݵĸ߳�ֵ
    virtual float getNoDataValue() { return _options.noDataValue().value(); } 
    virtual float getNoDataMinValue() { return _options.noDataMinValue().value(); } 
    virtual float getNoDataMaxValue() { return _options.noDataMaxValue().value(); }        

	// ��ȡ��ѡ����չ��
    virtual std::string getExtension() const {return "png";}

	// ��ȡ������
    TileBlacklist* getBlacklist();
    const TileBlacklist* getBlacklist() const;

	// �Ը����ļ���key����������Դ�Ƿ�������
    virtual bool hasData(const CVBF_TileKey& key) const;

 	// ������Դ�Ƿ���ָ��LOD���������
    virtual bool hasDataAtLOD( unsigned lod ) const;

	// ������Դ�Ƿ���ָ�����������
    virtual bool hasDataInExtent( const CVBF_GeoExtent& extent ) const;

	// ������Դ�ṩ�������Ƿ��Ƕ�̬�ģ������󻹿��ܱ����ģ�
    virtual bool isDynamic() const { return false; }

 	// ��ʾ������Դ�ʺ�ʹ��ʲô���Ļ�����ԡ�
    virtual CachePolicy getCachePolicyHint() const { return CachePolicy::DEFAULT; }

	// ����������Դ
    const Status& startup( const osgDB::Options* dbOptions );

	// ��ȡ����������Դʱ��ѡ��
    const CVBF_OptionsDriverSourceTile& getOptions() const { return _options; }

public:
	// osg::CVBF_Object�Ľӿ�
    virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
    virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
    virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const CVBFO_SourceTile*>(obj)!=NULL; }
    virtual const char* className() const { return "CVBFO_SourceTile"; }
    virtual const char* libraryName() const { return "osgEarth"; }

protected:

    virtual ~CVBFO_SourceTile();

    /** * The osgEarth engine calls this function to initialize a CVBFO_SourceTile using an
        * active osgDB::Options*/
	// ��ʼ������Դ����startup����
    virtual Status initialize( const osgDB::Options* dbOptions );

	// ���ݼ�ֵ����Ӱ�񣬴��麯��������ֵ��ָ���ɵ����߹���
    virtual osg::Image* createImage( const CVBF_TileKey& key, ProgressCallback* progress ) = 0;
	
	// ���ݼ�ֵ�����߳�ͼ�����麯��������ֵ��ָ���ɵ����߹���
    virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, ProgressCallback* progress );


	// ��������ã�������������Դ��״̬
    void setStatus( Status status );

private:

    ref_ptr<const CVBF_Profile> _profile;
    const CVBF_OptionsDriverSourceTile  _options;

    friend class CVBF_Map;
    friend class MapEngine;
    friend class CVBFO_SourceTileComposite;

    ref_ptr< TileBlacklist > _blacklist;
    std::string _blacklistFilename;

    ref_ptr<MemCache> _memCache;

    DataExtentList _dataExtents;
    Status         _status; // ״̬
};
class CVBF_SourceTileGroup:public CVBFO_SourceTile
{
public:
    CVBF_SourceTileGroup(const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile()):CVBFO_SourceTile(options) { }
    virtual void AddLayer(const CVBF_Options& opt )=0;
    virtual void AddLayer(const CVBF_Config& confURL)=0;
    virtual int  GetLayerNum()=0;
    virtual void SetLayerVisible(int idxLayer,bool bVisible)=0;
    virtual bool GetLayerVisible(int idxLayer)=0;
    virtual std::string GetLayerName(int idxLayer)=0;
    virtual void RemoveLayer(int idxLayer)=0;
    virtual void RemoveLayer(const std::string& sLayerName)=0;
    virtual void RemoveAllLayer()=0;
};

typedef std::vector< ref_ptr<CVBFO_SourceTile> > TileSourceVector;

// ����Դ������
class OSGEARTH_EXPORT TileSourceDriver : public osgDB::ReaderWriter
{
protected:
    const CVBF_OptionsDriverSourceTile& getTileSourceOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
    virtual const char* className() const;
};


// ����Դ������������Ƭ����Դ������������һ�𹹽�����Դ���ߣ��������ݷ��ʺʹ���
class OSGEARTH_EXPORT TileSourceFactory
{
public:
    static CVBFO_SourceTile* create( const CVBF_OptionsDriverSourceTile& options );
};


#endif // OSGEARTH_TILE_SOURCE_H
