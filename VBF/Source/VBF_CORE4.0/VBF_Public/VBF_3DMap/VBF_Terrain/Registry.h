#ifndef OSGEARTH_REGISTRY
#define OSGEARTH_REGISTRY 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <OpenThreads/ReentrantMutex>
#include <OpenThreads/ScopedLock>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <VBF_Engine/VBF_Text/Font>
#include <VBF_3DMap/VBF_Terrain/SharedSARepo>

#define GDAL_SCOPED_LOCK \
    OpenThreads::ScopedLock<OpenThreads::ReentrantMutex> _slock( osgEarth::Registry::instance()->getGDALMutex() )\

class CVBF_Capabilities;
class CVBF_Profile;

namespace osgEarth
{    
    class Cache;
    class ShaderFactory;
    class TaskServiceManager;
    class URIReadCallback;
    class ColorFilterRegistry;
    class StateSetCache;

    typedef SharedSARepo<osg::Program> ProgramSharedRepo;

    class OSGEARTH_EXPORT Registry : public ::CVBF_Referenced
    {
    public:
        static Registry* instance(bool erase = false); // 获取Earth注册器（singleton）

		// 1、获取Profile	

        const CVBF_Profile* getNamedProfile( const std::string& name ) const;// 根据名称获取Profile（预先定义的四种）		
        const CVBF_Profile* getGlobalGeodeticProfile() const;// 获取全局的内建大地（经纬度）Profile		
        const CVBF_Profile* getGlobalMercatorProfile() const;// 获取全局的内建MercatorProfile（mercator/WGS84 datum）	
        const CVBF_Profile* getSphericalMercatorProfile() const;// 获取全局的内建球面MercatorProfile(mercator/sphere)		
        const CVBF_Profile* getCubeProfile() const;// 获取全局的内建CubeProfile

		// 2、获取与设置缓存
 		
        Cache* getCache() const;		// 获取系统默认的cache
        void setCache( Cache* cache );	// 设置系统默认的cache

 		// 优先的缓存策略（如果设置，则覆盖所有其他的设置）
        const CVBF_Optional<CachePolicy>& overrideCachePolicy() const { return _overrideCachePolicy; }
        void setOverrideCachePolicy( const CachePolicy& policy );

		// 默认的缓存策略（用于没有设置缓存策略的时候）
        const CVBF_Optional<CachePolicy>& defaultCachePolicy() const { return _defaultCachePolicy; }
        void setDefaultCachePolicy( const CachePolicy& policy );

		// 获取缓存策略（先检测优先的缓存策略，然后在DB::Options中查找，然后检测默认的缓存策略，都没有则返回false）
        bool getCachePolicy( CVBF_Optional<CachePolicy>& cp, const osgDB::Options* options =0L ) const;


		// 3、文件黑名单
		
        bool isBlacklisted(const std::string &filename);// 给定的文件是否在黑名单中？		
        void blacklist(const std::string &filename);// 把给定的文件放入黑名单	
        unsigned int getNumBlacklistedFilenames();// 获取黑名单中文件的数量
        void clearBlacklist();// 清空文件黑名单



		// 获取GDAL串行化的互斥量（应用于整个程序的），GDAL不是线程安全的
        OpenThreads::ReentrantMutex& getGDALMutex();

        // 默认的系统字体
        void setDefaultFont( osgText::Font* font );
        osgText::Font* getDefaultFont();

		// 设置/获取平台的图形硬件能力
        const CVBF_Capabilities& getCapabilities() const;
        void setCapabilities( CVBF_Capabilities* caps );
        static const CVBF_Capabilities& capabilities() { return instance()->getCapabilities(); }

		// 设置/获取着色器工厂（可扩展）
        const ShaderFactory* getShaderFactory() const;
        void setShaderFactory( ShaderFactory* lib );
        static const ShaderFactory* shaderFactory() { return instance()->getShaderFactory(); }

		// 获取/设置状态集缓存，用于多个节点之间共享状态集（A registry-wide SSC仅在OSG 3.1.4+中支持，细节见Registry.cpp注释）
        StateSetCache* getStateSetCache() const;
        void setStateSetCache( StateSetCache* cache );
        static StateSetCache* stateSetCache() { return instance()->getStateSetCache(); }

		// 获取任务服务管理者
        TaskServiceManager* getTaskServiceManager() { return _taskServiceManager.get(); }

		// 生成一个全局（instance-wide）唯一标识
        UID createUID();


		// set/get a global read callback for URI objects.
        void setURIReadCallback( URIReadCallback* callback );
        URIReadCallback* getURIReadCallback() const;

  		// 获取默认的osgDB::Options 
        const osgDB::Options* getDefaultOptions() const { return _defaultOptions.get(); }

  		// 拷贝一个options结构(fixing the archive caching)，或创建一个新的
        osgDB::Options* cloneOrCreateOptions( const osgDB::Options* options =0L ) const;
        
		// 设置/获取默认的地形引擎驱动器的名字（系统默认的是"mp"）
        void setDefaultTerrainEngineDriverName( const std::string& name );
        const std::string& getDefaultTerrainEngineDriverName() const { return _terrainEngineDriver; }

        ProgramSharedRepo* getProgramSharedRepo();
               static ProgramSharedRepo* programSharedRepo() { return instance()->getProgramSharedRepo(); }

       std::string findDataFile(const std::string& fileName, const osgDB::Options* options, EVBF_CASESENSITIVITY caseSensitivity)
       {
           if (options && options->getFindFileCallback()) return options->getFindFileCallback()->findDataFile(fileName, options, caseSensitivity);
           else return findDataFileImplementation(fileName, options, caseSensitivity);
       }
       std::string findDataFileImplementation(const std::string& fileName, const osgDB::Options* options, EVBF_CASESENSITIVITY caseSensitivity);

       /** Set the data file path using a list of paths stored in a FilePath, which is used when search for data files.*/
      void setDataFilePathList(const VBF_FilePathList& filepath) { _dataFilePath = filepath; }

      /** Set the data file path using a single string delimited either with ';' (Windows) or ':' (All other platforms), which is used when search for data files.*/
      void setDataFilePathList(const std::string& paths);

      /** get the data file path which is used when search for data files.*/
      VBF_FilePathList& getDataFilePathList() { return _dataFilePath; }

      /** get the const data file path which is used when search for data files.*/
      const VBF_FilePathList& getDataFilePathList() const { return _dataFilePath; }

    protected:
        virtual ~Registry();
        Registry();

        void destruct();

        OpenThreads::ReentrantMutex _gdal_mutex;
        bool _gdal_registered;

        ref_ptr<const CVBF_Profile> _global_geodetic_profile;
        ref_ptr<const CVBF_Profile> _spherical_mercator_profile;
        ref_ptr<const CVBF_Profile> _cube_profile;

        CVBF_ReadWriteMutex _regMutex;  
        int _numGdalMutexGets;
        
        typedef std::map< std::string, std::string> MimeTypeExtensionMap;
        // maps mime-types to extensions.
        MimeTypeExtensionMap _mimeTypeExtMap;

        ref_ptr<Cache> _cache;
        CVBF_Optional<CachePolicy> _defaultCachePolicy;
        CVBF_Optional<CachePolicy> _overrideCachePolicy;

        typedef std::set<std::string> StringSet;
        StringSet _blacklistedFilenames;
        CVBF_ReadWriteMutex _blacklistMutex;

        ref_ptr<ShaderFactory> _shaderLib;

        ref_ptr<TaskServiceManager> _taskServiceManager;

        // unique ID generator:
        int                      _uidGen;
        mutable CVBF_Mutex _uidGenMutex;

        // system capabilities:
        ref_ptr< CVBF_Capabilities > _caps;
        mutable CVBF_Mutex     _capsMutex;
        void initCapabilities();

        ref_ptr<osgDB::Options> _defaultOptions;

        ref_ptr<URIReadCallback> _uriReadCallback;

        ref_ptr<osgText::Font> _defaultFont;

        ref_ptr<StateSetCache> _stateSetCache;

        std::string _terrainEngineDriver;

        ProgramSharedRepo _programRepo;

        VBF_FilePathList                            _dataFilePath;
    };
}



#endif //OSGEARTH_REGISTRY
