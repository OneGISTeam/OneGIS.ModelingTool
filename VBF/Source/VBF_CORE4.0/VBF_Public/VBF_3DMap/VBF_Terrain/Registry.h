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
        static Registry* instance(bool erase = false); // ��ȡEarthע������singleton��

		// 1����ȡProfile	

        const CVBF_Profile* getNamedProfile( const std::string& name ) const;// �������ƻ�ȡProfile��Ԥ�ȶ�������֣�		
        const CVBF_Profile* getGlobalGeodeticProfile() const;// ��ȡȫ�ֵ��ڽ���أ���γ�ȣ�Profile		
        const CVBF_Profile* getGlobalMercatorProfile() const;// ��ȡȫ�ֵ��ڽ�MercatorProfile��mercator/WGS84 datum��	
        const CVBF_Profile* getSphericalMercatorProfile() const;// ��ȡȫ�ֵ��ڽ�����MercatorProfile(mercator/sphere)		
        const CVBF_Profile* getCubeProfile() const;// ��ȡȫ�ֵ��ڽ�CubeProfile

		// 2����ȡ�����û���
 		
        Cache* getCache() const;		// ��ȡϵͳĬ�ϵ�cache
        void setCache( Cache* cache );	// ����ϵͳĬ�ϵ�cache

 		// ���ȵĻ�����ԣ�������ã��򸲸��������������ã�
        const CVBF_Optional<CachePolicy>& overrideCachePolicy() const { return _overrideCachePolicy; }
        void setOverrideCachePolicy( const CachePolicy& policy );

		// Ĭ�ϵĻ�����ԣ�����û�����û�����Ե�ʱ��
        const CVBF_Optional<CachePolicy>& defaultCachePolicy() const { return _defaultCachePolicy; }
        void setDefaultCachePolicy( const CachePolicy& policy );

		// ��ȡ������ԣ��ȼ�����ȵĻ�����ԣ�Ȼ����DB::Options�в��ң�Ȼ����Ĭ�ϵĻ�����ԣ���û���򷵻�false��
        bool getCachePolicy( CVBF_Optional<CachePolicy>& cp, const osgDB::Options* options =0L ) const;


		// 3���ļ�������
		
        bool isBlacklisted(const std::string &filename);// �������ļ��Ƿ��ں������У�		
        void blacklist(const std::string &filename);// �Ѹ������ļ����������	
        unsigned int getNumBlacklistedFilenames();// ��ȡ���������ļ�������
        void clearBlacklist();// ����ļ�������



		// ��ȡGDAL���л��Ļ�������Ӧ������������ģ���GDAL�����̰߳�ȫ��
        OpenThreads::ReentrantMutex& getGDALMutex();

        // Ĭ�ϵ�ϵͳ����
        void setDefaultFont( osgText::Font* font );
        osgText::Font* getDefaultFont();

		// ����/��ȡƽ̨��ͼ��Ӳ������
        const CVBF_Capabilities& getCapabilities() const;
        void setCapabilities( CVBF_Capabilities* caps );
        static const CVBF_Capabilities& capabilities() { return instance()->getCapabilities(); }

		// ����/��ȡ��ɫ������������չ��
        const ShaderFactory* getShaderFactory() const;
        void setShaderFactory( ShaderFactory* lib );
        static const ShaderFactory* shaderFactory() { return instance()->getShaderFactory(); }

		// ��ȡ/����״̬�����棬���ڶ���ڵ�֮�乲��״̬����A registry-wide SSC����OSG 3.1.4+��֧�֣�ϸ�ڼ�Registry.cppע�ͣ�
        StateSetCache* getStateSetCache() const;
        void setStateSetCache( StateSetCache* cache );
        static StateSetCache* stateSetCache() { return instance()->getStateSetCache(); }

		// ��ȡ������������
        TaskServiceManager* getTaskServiceManager() { return _taskServiceManager.get(); }

		// ����һ��ȫ�֣�instance-wide��Ψһ��ʶ
        UID createUID();


		// set/get a global read callback for URI objects.
        void setURIReadCallback( URIReadCallback* callback );
        URIReadCallback* getURIReadCallback() const;

  		// ��ȡĬ�ϵ�osgDB::Options 
        const osgDB::Options* getDefaultOptions() const { return _defaultOptions.get(); }

  		// ����һ��options�ṹ(fixing the archive caching)���򴴽�һ���µ�
        osgDB::Options* cloneOrCreateOptions( const osgDB::Options* options =0L ) const;
        
		// ����/��ȡĬ�ϵĵ������������������֣�ϵͳĬ�ϵ���"mp"��
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
