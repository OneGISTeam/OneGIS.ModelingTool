#ifndef OSGEARTH_CACHE_BIN_H
#define OSGEARTH_CACHE_BIN_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/IOTypes.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>

namespace osgEarth
{
	// �����䣺CacheBin�ǻ����е�һ�����������������ڲ�ͬ��Ӧ��ģ����һ�����ػ����зֿ����Ե�����
    class CacheBin : public ::CVBF_Referenced
    {
    public:
  
		// binID�����֣�Ψһ��ʶ��
        CacheBin( const std::string& binID ) : _binID(binID) { }
        virtual ~CacheBin() { }

		// ��ȡΨһ��ʶ
        const std::string& getID() const { return _binID; }

		// �ӻ����ж�ȡObject��key�ǹؼ��֣�maxAge����¼��������䣬������ڷ���0
        virtual ReadResult readObject( const std::string& key, double maxAge =DBL_MAX ) =0;

		// �ӻ����ж�ȡImage��
        virtual ReadResult readImage( const std::string& key, double maxAge =DBL_MAX ) =0;

		// �ӻ����ж�ȡString
        virtual ReadResult readString( const std::string& key, double maxAge = DBL_MAX ) =0;

		// �򻺴���д��Object����Image��
        virtual bool write( const std::string& key, const osg::CVBF_Object* object,
                                          const CVBF_Config& metadata =CVBF_Config() ) =0;

		// ���һ��key�Ƿ��ڻ������Ѿ����ڣ�Ĭ�ϵ�ʵ�ֽ�������ͼ��ȡ�ö���
        virtual bool isCached( const std::string& key, double maxAge =DBL_MAX ) =0;

		// �ӻ����ж�ȡ�Զ���metadata
        virtual CVBF_Config readMetadata() { return CVBF_Config(); }

		// �򻺴���д���Զ���metadata
        virtual bool writeMetadata( const CVBF_Config& meta ) { return false; }

		// �������е���Ŀ(entries)
        virtual bool purge() = 0;

		// ��thisָ��浽һ��Options�ṹ
        void apply( osgDB::Options* options ) const
		{
            if ( options ) options->setPluginData( "osgEarth::CacheBin", (void*)this );
        }

		// ��һ��Options�ṹ��ȡָ��
        static CacheBin* get( const osgDB::Options* options ) 
		{
            return options ? const_cast<CacheBin*>(static_cast<const CacheBin*>(options->getPluginData("osgEarth::CacheBin"))) : 0L;
        }

    protected:
        std::string _binID;
    };
}

#endif // OSGEARTH_CACHE_BIN_H
