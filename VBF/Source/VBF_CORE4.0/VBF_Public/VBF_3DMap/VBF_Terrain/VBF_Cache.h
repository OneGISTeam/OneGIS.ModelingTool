#ifndef OSGEARTH_CACHE_H
#define OSGEARTH_CACHE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CacheBin.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

namespace osgEarth
{    
	// ����ѡ��
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


	// ���棺��һ���������ѹؼ�����Ҫ�ش洢������
    class OSGEARTH_EXPORT Cache : public osg::CVBF_Object
    {
    protected:
        Cache( const CacheOptions& options =CacheOptions() );
        Cache( const Cache& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL );
      
		META_Object( osgEarth, Cache );

        virtual ~Cache();

    public:

		// �����Ƿ���Ч������
        bool isOK() const;

		// ��ȡCacheBin
        CacheBin* getBin( const std::string& name );

		// ��ȡ�򴴽�һ��Ĭ�ϵĻ����䣬����ʵ�ֿ���֧��Ҳ���ܲ�֧�֣�����֮ǰҪ���
        virtual CacheBin* getOrCreateDefaultBin();

		// ����һ���µĻ����䲢����ָ��
        virtual CacheBin* addBin( const std::string& binID );

		// ����һ��������
        virtual void removeBin( CacheBin* bin );

		// ��ȡ�����������
        const CacheOptions& getCacheOptions() const ;

		// �Ѹû��汣�浽osgDB::Options
        void apply( osgDB::Options* options );

		// ��osgDB::Options��ȡ�����ָ��
        static Cache* get( const osgDB::Options* options );

    protected:
        bool                   _ok;
        CacheOptions           _options;
        ThreadSafeCacheBinMap  _bins;
        ref_ptr<CacheBin> _defaultBin;
    };



    // ��������������Ļ���
    class OSGEARTH_EXPORT CacheDriver : public osgDB::ReaderWriter
    {
    public:
        const CacheOptions& getCacheOptions( const osgDB::ReaderWriter::Options* options ) const;
        virtual ~CacheDriver();
        virtual const char* className() const;
    };


    // ����CacheOptions����Cache�Ĺ���
    class OSGEARTH_EXPORT CacheFactory
    {
    public:
        static Cache* create( const CacheOptions& options);
    };
}

#endif // OSGEARTH_CACHE_H
