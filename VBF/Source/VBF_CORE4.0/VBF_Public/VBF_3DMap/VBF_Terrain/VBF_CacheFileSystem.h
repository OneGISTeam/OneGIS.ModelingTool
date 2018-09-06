#ifndef OSGEARTH_DRIVER_CACHE_FILESYSTEM
#define OSGEARTH_DRIVER_CACHE_FILESYSTEM 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>

namespace osgEarth { namespace Drivers
{
    using namespace osgEarth;
    
    // 文件系统缓存配置项（选项）
    class FileSystemCacheOptions : public CacheOptions
    {
    public:
        FileSystemCacheOptions( const CVBF_Options& options =CVBF_Options() )
            : CacheOptions( options )
        {
            setDriver( "filesystem" );
            fromConfig( m_conf ); 
        }

        virtual ~FileSystemCacheOptions() { }

    public:
        // 缓存的根路径
        CVBF_Optional<std::string>& rootPath() { return _path; }
        const CVBF_Optional<std::string>& rootPath() const { return _path; }

    public:
        virtual CVBF_Config getConfig() const
        {
            CVBF_Config conf = CVBF_Options::getConfig();
            conf.addIfSet( "path", _path );
            return conf;
        }
        virtual void mergeConfig( const CVBF_Config& conf )
        {
            CVBF_Options::mergeConfig( conf );            
            fromConfig( conf );
        }

    private:
        void fromConfig( const CVBF_Config& conf )
        {
            conf.getIfSet( "path", _path );
        }

        CVBF_Optional<std::string> _path;
    };

} }

#endif
