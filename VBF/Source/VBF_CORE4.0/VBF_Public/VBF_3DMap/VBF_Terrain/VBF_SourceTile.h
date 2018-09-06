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


// 瓦片数据源驱动器的配置项
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


// 瓦片的黑名单列表（不需要读取）
class OSGEARTH_EXPORT TileBlacklist : public virtual CVBF_Referenced
{
public:
    TileBlacklist();
    virtual ~TileBlacklist() { }

    void add(const osgTerrain::TileID &tile);    // 加入一个瓦片
    void remove(const osgTerrain::TileID& tile); // 移除一个瓦片
    void clear(); // 清空

    bool contains(const osgTerrain::TileID &tile) const; // 是否包含该瓦片
    unsigned int size() const;	// 瓦片数量

    static TileBlacklist* read(std::istream &in);			// 从流中读取黑名单
    static TileBlacklist* read(const std::string &filename);// 从文件读取黑名单

    void write(std::ostream &output) const;			// 向流中写入黑名单
    void write(const std::string &filename) const;	// 向文件写入黑名单

private:
    typedef std::set< osgTerrain::TileID > BlacklistedTiles;
    BlacklistedTiles	_tiles;	// 黑名单数据
    CVBF_ReadWriteMutex _mutex;	// 线程保护
};

// 瓦片数据源，可以创建影像和高程瓦片。数据驱动器插件负责创建并返回数据源，地图（CVBF_Map）使用该数据源创建瓦片
class OSGEARTH_EXPORT CVBFO_SourceTile : public virtual osg::CVBF_Object
{
public:
    struct Status // 数据源初始化的状态
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
	
    const Status& getStatus() const { return _status; } // 获取该瓦片源的状态

    virtual int getPixelsPerTile() const;// 获取每个瓦片的像素数

	// 获取该数据源的数据范围列表
    const DataExtentList& getDataExtents() const { return _dataExtents; }
    DataExtentList& getDataExtents() { return _dataExtents; }

	// 根据键值创建影像，键（CVBF_TileKey）的profile必须与该数据源匹配
    virtual osg::Image* createImage( const CVBF_TileKey& key, ImageOperation* op=0L, ProgressCallback* progress=0L );

	// 根据键值创建高程图，键（CVBF_TileKey）的profile必须与该数据源匹配
    virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, HeightFieldOperation* op=0L, ProgressCallback* progress=0L );

public:

	// 数据源是否正确初始化，并有有效的profile
    virtual bool isOK() const;
    bool isValid() const { return isOK(); }

    virtual const CVBF_Profile* getProfile() const;// 获取数据源的Profile	
    void setProfile( const CVBF_Profile* profile );// 被子类或Factory调用，用于初始化数据源的profile

	// 获取无数据的高程值
    virtual float getNoDataValue() { return _options.noDataValue().value(); } 
    virtual float getNoDataMinValue() { return _options.noDataMinValue().value(); } 
    virtual float getNoDataMaxValue() { return _options.noDataMaxValue().value(); }        

	// 获取首选的扩展名
    virtual std::string getExtension() const {return "png";}

	// 获取黑名单
    TileBlacklist* getBlacklist();
    const TileBlacklist* getBlacklist() const;

	// 对给定的键（key），该数据源是否有数据
    virtual bool hasData(const CVBF_TileKey& key) const;

 	// 该数据源是否有指定LOD级别的数据
    virtual bool hasDataAtLOD( unsigned lod ) const;

	// 该数据源是否有指定区域的数据
    virtual bool hasDataInExtent( const CVBF_GeoExtent& extent ) const;

	// 该数据源提供的数据是否是动态的（创建后还可能被更改）
    virtual bool isDynamic() const { return false; }

 	// 提示该数据源适合使用什么样的缓存策略。
    virtual CachePolicy getCachePolicyHint() const { return CachePolicy::DEFAULT; }

	// 启动该数据源
    const Status& startup( const osgDB::Options* dbOptions );

	// 获取创建该数据源时的选项
    const CVBF_OptionsDriverSourceTile& getOptions() const { return _options; }

public:
	// osg::CVBF_Object的接口
    virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
    virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
    virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const CVBFO_SourceTile*>(obj)!=NULL; }
    virtual const char* className() const { return "CVBFO_SourceTile"; }
    virtual const char* libraryName() const { return "osgEarth"; }

protected:

    virtual ~CVBFO_SourceTile();

    /** * The osgEarth engine calls this function to initialize a CVBFO_SourceTile using an
        * active osgDB::Options*/
	// 初始化数据源，由startup调用
    virtual Status initialize( const osgDB::Options* dbOptions );

	// 根据键值创建影像，纯虚函数，返回值是指针由调用者管理
    virtual osg::Image* createImage( const CVBF_TileKey& key, ProgressCallback* progress ) = 0;
	
	// 根据键值创建高程图，纯虚函数，返回值是指针由调用者管理
    virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, ProgressCallback* progress );


	// 被子类调用，用于设置数据源的状态
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
    Status         _status; // 状态
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

// 数据源驱动器
class OSGEARTH_EXPORT TileSourceDriver : public osgDB::ReaderWriter
{
protected:
    const CVBF_OptionsDriverSourceTile& getTileSourceOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
    virtual const char* className() const;
};


// 数据源工厂：创建瓦片数据源并把它们连在一起构建数据源管线，用于数据访问和处理
class OSGEARTH_EXPORT TileSourceFactory
{
public:
    static CVBFO_SourceTile* create( const CVBF_OptionsDriverSourceTile& options );
};


#endif // OSGEARTH_TILE_SOURCE_H
