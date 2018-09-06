#ifndef OSGEARTH_MEMCACHE_H
#define OSGEARTH_MEMCACHE_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>

namespace osgEarth
{
	// �ڴ��еĻ��棺�����е�ÿ�������䣨bin�������Լ���֤�̰߳�ȫ�ļ������ƣ�locking mechanism��
    //             ÿ�������䶼ά��һ���޶���С��LRU�б�
    class OSGEARTH_EXPORT MemCache : public Cache
    {
    public:
        MemCache( unsigned maxBinSize =16 );
        META_Object( osgEarth, MemCache );

        virtual ~MemCache() { }

    public:
		// ��ӻ�����
        virtual CacheBin* addBin( const std::string& binID );
        virtual CacheBin* getOrCreateDefaultBin();
    
    private:
        MemCache( const MemCache& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ): Cache(rhs,op)
        {
        }

        unsigned _maxBinSize; // ������Ĵ�С���޶�ֵ��
    };

} // namespace osgEarth

#endif // OSGEARTH_MEMCACHE_H
