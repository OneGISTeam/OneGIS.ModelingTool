#ifndef OSGEARTH_CACHE_BIN_H
#define OSGEARTH_CACHE_BIN_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/IOTypes.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>

namespace osgEarth
{
	// 缓存箱：CacheBin是缓存中的一个命名容器，它用于不同的应用模块在一个本地缓存中分开各自的数据
    class CacheBin : public ::CVBF_Referenced
    {
    public:
  
		// binID：名字（唯一标识）
        CacheBin( const std::string& binID ) : _binID(binID) { }
        virtual ~CacheBin() { }

		// 获取唯一标识
        const std::string& getID() const { return _binID; }

		// 从缓存中读取Object。key是关键字，maxAge，记录的最大年龄，如果过期返回0
        virtual ReadResult readObject( const std::string& key, double maxAge =DBL_MAX ) =0;

		// 从缓存中读取Image。
        virtual ReadResult readImage( const std::string& key, double maxAge =DBL_MAX ) =0;

		// 从缓存中读取String
        virtual ReadResult readString( const std::string& key, double maxAge = DBL_MAX ) =0;

		// 向缓存中写入Object（或Image）
        virtual bool write( const std::string& key, const osg::CVBF_Object* object,
                                          const CVBF_Config& metadata =CVBF_Config() ) =0;

		// 检查一个key是否在缓存中已经存在（默认的实现仅仅是试图读取该对象）
        virtual bool isCached( const std::string& key, double maxAge =DBL_MAX ) =0;

		// 从缓存中读取自定义metadata
        virtual CVBF_Config readMetadata() { return CVBF_Config(); }

		// 向缓存中写入自定义metadata
        virtual bool writeMetadata( const CVBF_Config& meta ) { return false; }

		// 清理所有的条目(entries)
        virtual bool purge() = 0;

		// 把this指针存到一个Options结构
        void apply( osgDB::Options* options ) const
		{
            if ( options ) options->setPluginData( "osgEarth::CacheBin", (void*)this );
        }

		// 从一个Options结构获取指针
        static CacheBin* get( const osgDB::Options* options ) 
		{
            return options ? const_cast<CacheBin*>(static_cast<const CacheBin*>(options->getPluginData("osgEarth::CacheBin"))) : 0L;
        }

    protected:
        std::string _binID;
    };
}

#endif // OSGEARTH_CACHE_BIN_H
