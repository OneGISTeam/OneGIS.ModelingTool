#ifndef OSGEARTHFEATURES_FEATURE_SOURCE_H
#define OSGEARTHFEATURES_FEATURE_SOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FeatureCursor.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Query.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>

#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <OpenThreads/Mutex>
#include <list>

namespace osgEarth { namespace Features
{   
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

	// 用于创建矢量数据源（地物数据源）的配置选项
    class OSGEARTHFEATURES_EXPORT CVBF_OptionsDriverSourceFeature : public CVBF_OptionsDriver
    {
    public: // 属性

		// 数据源的名字
 //IE死机       CVBF_Optional<std::string>& name() { return m_sName; }
        const CVBF_Optional<std::string>& name() const { return m_sName; }

		// 从数据源读取数据的过滤器（filteres）列表
        FeatureFilterList& filters() { return _filters; }
        const FeatureFilterList& filters() const { return _filters; }

		// 是否以写的方式打开数据（如果支持的话）
        CVBF_Optional<bool>& openWrite() { return _openWrite; }
        const CVBF_Optional<bool>& openWrite() const { return _openWrite; }

		// 重载，包含在实际数据源中的profile信息
        CVBF_Optional<CVBF_OptionsProfile>& profile() { return _profile; }
        const CVBF_Optional<CVBF_OptionsProfile>& profile() const { return _profile; }
        void SetName(std::string sName) { m_sName = sName; }


    public:
        CVBF_OptionsDriverSourceFeature( const CVBF_Options& options =CVBF_Options() );
        virtual ~CVBF_OptionsDriverSourceFeature();
        virtual CVBF_Config getConfig() const;
        CVBF_OptionsDriverSourceFeature& operator = ( const CVBF_OptionsDriverSourceFeature& rhs );

    protected:
        virtual void mergeConfig( const CVBF_Config& conf );

    private:
        void fromConfig( const CVBF_Config& conf );

        FeatureFilterList        _filters;
        CVBF_Optional<std::string>    m_sName;
        CVBF_Optional< bool >         _openWrite;
        CVBF_Optional<CVBF_OptionsProfile> _profile;
        CVBF_Optional<CachePolicy>    _cachePolicy;
    };


	// FeatureSource是一个生成矢量数据的可插入对象，并含有风格化信息（可选）
    class OSGEARTHFEATURES_EXPORT FeatureSource : public osg::CVBF_Object, public Revisioned
    {
    public:      

		// 根据提供的读写选项构建一个矢量数据源
        FeatureSource( const CVBF_Options& options=CVBF_Options(), const osgDB::Options* dbOptions =0L );

        // 获取描述该矢量数据的元数据（数据源成功初始化之后才有效）
        const FeatureProfile* getFeatureProfile() const;

        // 获取数据源的选择项
        const CVBF_OptionsDriverSourceFeature& getFeatureSourceOptions() const { return _options; }

        // 创建一个游标，用于查询时遍历所有的features
        virtual FeatureCursor* createFeatureCursor( const Symbology::Query& query =Symbology::Query() ) =0;

		// 该数据源是否支持插入和删除矢量数据
        virtual bool isWritable() const { return false; }

		// 删除给定ID的数据，成功返回true，失败或数据源为只读时返回false
        virtual bool deleteFeature(FeatureID fid) { return false; }

		// 获取该数据源中的矢量数据的数量，如果不确定返回-1
        virtual int getFeatureCount() const { return -1; }

		// 获取给定ID的数据，找不到则返回NULL
        virtual Feature* getFeature( FeatureID fid ) { return 0L; }

		// 获取地物类的属性表，可能为空
        virtual const FeatureSchema& getSchema() const;

		// 插入一个地物，如果插入成功返回true，否则返回false
        virtual bool insertFeature(Feature* feature) { return false; }

		// 获取数据源中几何体的类型（点、线、面、环等）
        virtual Geometry::Type getGeometryType() const { return Geometry::TYPE_UNKNOWN; }


    public: // 黑名单	
        void addToBlacklist( FeatureID fid );// 向黑名单中添加一个地物的ID号
        void removeFromBlacklist( FeatureID fid );// 从黑名单中移除一个地物的ID号
        void clearBlacklist();// 清空黑名单
        bool isBlacklisted( FeatureID fid ) const; // 判断该ID号是否在黑名单中

    public: // 风格化
        // 数据源是否有嵌入的风格化（在地物数据的属性中有风格化信息），默认为false      
        virtual bool hasEmbeddedStyles() const { return false; }

    public:
        // 获取过滤器的列表，查询时过滤数据
        const FeatureFilterList& getFilters() const;

    public: 

        // META_Object specialization:
        virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
        virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const FeatureSource*>(obj)!=NULL; }
        virtual const char* className() const { return "FeatureSource"; }
        virtual const char* libraryName() const { return "VBF_Features"; }

		// 初始化
        virtual void initialize( const osgDB::Options* dbOptions =0L ) { }

  		// 给地物的profile置dirty标志
        void dirtyFeatureProfile() { _featureProfile = 0;}

    protected:
        virtual ~FeatureSource();

		// 创建并返回在一个命名的地物类中描述地物的元数据结构，该方法被公共函数getFeatureProfile()调用       
        virtual const FeatureProfile* createFeatureProfile() =0;

		// 访问传入的DB选项
        const osgDB::Options* dbOptions() const { return _dbOptions.get(); }
        const URIContext& uriContext() const { return _uriContext; } // 用于解析相对路径

        Cache* getCache() const { return _cache.get(); }  // 获取缓存（通过dbOptions传入的）

    private:
        const CVBF_OptionsDriverSourceFeature _options;
        ref_ptr<const FeatureProfile> _featureProfile;
        CVBF_Mutex                   _createMutex;

        ref_ptr<const osgDB::Options> _dbOptions;
        URIContext                    _uriContext;
        observer_ptr<Cache>           _cache;

        CVBF_ReadWriteMutex          _blacklistMutex;
        std::set<FeatureID>                _blacklist;

        friend class CVBF_Map;
        friend class FeatureSourceFactory;
    };

	// 矢量数据源驱动器
    class OSGEARTHFEATURES_EXPORT FeatureSourceDriver : public osgDB::ReaderWriter
    {
    public:
        virtual const CVBF_OptionsDriverSourceFeature& getFeatureSourceOptions( const osgDB::ReaderWriter::Options* rwopt ) const;
        virtual const char* className() const;
    };


	// 矢量数据源类工厂，创建根据驱动器的名字创建一个矢量数据源
    class OSGEARTHFEATURES_EXPORT FeatureSourceFactory
    {
	public:
        static FeatureSource* create( const CVBF_OptionsDriverSourceFeature& options );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_SOURCE_H

