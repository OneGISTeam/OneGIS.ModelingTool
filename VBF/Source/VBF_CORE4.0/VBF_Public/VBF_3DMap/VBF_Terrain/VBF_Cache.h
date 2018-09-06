#ifndef OSGEARTH_CACHE_H
#define OSGEARTH_CACHE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CacheBin.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

namespace osgEarth
{    
	// 缓存选项
    class OSGEARTH_EXPORT CacheOptions : public CVBF_OptionsDriver
    {
    public:
        CacheOptions( const CVBF_Options& options = CVBF_Options() );
        virtual ~CacheOptions();

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );

    private:
        void fromConfig( const CVBF_Config& conf );
    };



    typedef CVBF_PerObjectRefMap<std::string, CacheBin> ThreadSafeCacheBinMap;


	// 缓存：是一个容器，把关键数据要素存储到本地
    class OSGEARTH_EXPORT Cache : public osg::CVBF_Object
    {
    protected:
        Cache( const CacheOptions& options =CacheOptions() );
        Cache( const Cache& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL );
      
		META_Object( osgEarth, Cache );

        virtual ~Cache();

    public:

		// 缓存是否有效并可用
        bool isOK() const;

		// 获取CacheBin
        CacheBin* getBin( const std::string& name );

		// 获取或创建一个默认的缓存箱，具体实现可能支持也可能不支持，在用之前要检查
        virtual CacheBin* getOrCreateDefaultBin();

		// 创建一个新的缓存箱并返回指针
        virtual CacheBin* addBin( const std::string& binID );

		// 移走一个缓存箱
        virtual void removeBin( CacheBin* bin );

		// 获取缓存的配置项
        const CacheOptions& getCacheOptions() const ;

		// 把该缓存保存到osgDB::Options
        void apply( osgDB::Options* options );

		// 从osgDB::Options获取缓存的指针
        static Cache* get( const osgDB::Options* options );

    protected:
        bool                   _ok;
        CacheOptions           _options;
        ThreadSafeCacheBinMap  _bins;
        ref_ptr<CacheBin> _defaultBin;
    };



    // 缓存驱动器插件的基类
    class OSGEARTH_EXPORT CacheDriver : public osgDB::ReaderWriter
    {
    public:
        const CacheOptions& getCacheOptions( const osgDB::ReaderWriter::Options* options ) const;
        virtual ~CacheDriver();
        virtual const char* className() const;
    };


    // 根据CacheOptions创建Cache的工厂
    class OSGEARTH_EXPORT CacheFactory
    {
    public:
        static Cache* create( const CacheOptions& options);
    };
}

#endif // OSGEARTH_CACHE_H
