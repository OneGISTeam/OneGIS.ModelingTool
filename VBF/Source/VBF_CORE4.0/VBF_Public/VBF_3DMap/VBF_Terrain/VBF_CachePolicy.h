#ifndef OSGEARTH_CACHE_POLICY_H
#define OSGEARTH_CACHE_POLICY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SGDB/Options>

namespace osgEarth
{
	// 缓存策略
    class OSGEARTH_EXPORT CachePolicy
    {
    public:
        enum Usage
        {
            USAGE_READ_WRITE   = 0,  // 可读可写（如果存在的话）
            USAGE_CACHE_ONLY   = 1,  // 把缓存作为唯一的数据源
            USAGE_READ_ONLY    = 2,  // 只读缓存
            USAGE_NO_CACHE     = 3   // 没缓存（既不读也不写）
        };


        static CachePolicy DEFAULT;     // 默认的缓存（READ_WRITE）
        static CachePolicy NO_CACHE;    // 不用缓存策略
        static CachePolicy CACHE_ONLY;  // 只用缓存数据的策略

    public:
        CachePolicy(); // 构造一个无效的缓存策略
        CachePolicy( const Usage& usage );
        CachePolicy( const Usage& usage, double maxAgeSeconds );
        CachePolicy( const CVBF_Config& conf );
        virtual ~CachePolicy() { }

		// 从osgDB::Options中读入缓存策略
        static bool fromOptions( const osgDB::Options* dbOptions, CVBF_Optional<CachePolicy>& out_policy );

		// 把缓存策略写入osgDB::Options
        void apply( osgDB::Options* options );


		// 获取缓存的用法
        CVBF_Optional<Usage>& usage() { return _usage; }
        const CVBF_Optional<Usage>& usage() const { return _usage; }

		// 获取缓存记录的寿命限制（秒）
        CVBF_Optional<double>& maxAge() { return _maxAge; }
        const CVBF_Optional<double>& maxAge() const { return _maxAge; }

    public: 

        bool isCacheReadable() const {  return *_usage == USAGE_READ_WRITE || *_usage == USAGE_CACHE_ONLY || *_usage == USAGE_READ_ONLY; }
        bool isCacheWriteable() const { return *_usage == USAGE_READ_WRITE; }

        bool operator == ( const CachePolicy& rhs ) const;
        bool operator != ( const CachePolicy& rhs ) const { return ! operator==(rhs); }

        std::string usageString() const;

    public:

        CVBF_Config getConfig() const;
        void fromConfig( const CVBF_Config& conf );

    private:
        CVBF_Optional<Usage>   _usage;
        CVBF_Optional<double>  _maxAge;
    };
}

#endif // OSGEARTH_CACHE_POLICY_H
