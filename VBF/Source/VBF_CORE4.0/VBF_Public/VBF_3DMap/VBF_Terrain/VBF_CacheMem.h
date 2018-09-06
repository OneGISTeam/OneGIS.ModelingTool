#ifndef OSGEARTH_MEMCACHE_H
#define OSGEARTH_MEMCACHE_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>

namespace osgEarth
{
	// 内存中的缓存：缓存中的每个缓存箱（bin）都有自己保证线程安全的加锁机制（locking mechanism）
    //             每个缓存箱都维持一个限定大小的LRU列表
    class OSGEARTH_EXPORT MemCache : public Cache
    {
    public:
        MemCache( unsigned maxBinSize =16 );
        META_Object( osgEarth, MemCache );

        virtual ~MemCache() { }

    public:
		// 添加缓存箱
        virtual CacheBin* addBin( const std::string& binID );
        virtual CacheBin* getOrCreateDefaultBin();
    
    private:
        MemCache( const MemCache& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ): Cache(rhs,op)
        {
        }

        unsigned _maxBinSize; // 缓存箱的大小（限定值）
    };

} // namespace osgEarth

#endif // OSGEARTH_MEMCACHE_H
