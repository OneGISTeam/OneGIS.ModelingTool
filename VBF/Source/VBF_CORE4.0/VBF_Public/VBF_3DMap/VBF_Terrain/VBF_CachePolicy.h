#ifndef OSGEARTH_CACHE_POLICY_H
#define OSGEARTH_CACHE_POLICY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SGDB/Options>

namespace osgEarth
{
	// �������
    class OSGEARTH_EXPORT CachePolicy
    {
    public:
        enum Usage
        {
            USAGE_READ_WRITE   = 0,  // �ɶ���д��������ڵĻ���
            USAGE_CACHE_ONLY   = 1,  // �ѻ�����ΪΨһ������Դ
            USAGE_READ_ONLY    = 2,  // ֻ������
            USAGE_NO_CACHE     = 3   // û���棨�Ȳ���Ҳ��д��
        };


        static CachePolicy DEFAULT;     // Ĭ�ϵĻ��棨READ_WRITE��
        static CachePolicy NO_CACHE;    // ���û������
        static CachePolicy CACHE_ONLY;  // ֻ�û������ݵĲ���

    public:
        CachePolicy(); // ����һ����Ч�Ļ������
        CachePolicy( const Usage& usage );
        CachePolicy( const Usage& usage, double maxAgeSeconds );
        CachePolicy( const CVBF_Config& conf );
        virtual ~CachePolicy() { }

		// ��osgDB::Options�ж��뻺�����
        static bool fromOptions( const osgDB::Options* dbOptions, CVBF_Optional<CachePolicy>& out_policy );

		// �ѻ������д��osgDB::Options
        void apply( osgDB::Options* options );


		// ��ȡ������÷�
        CVBF_Optional<Usage>& usage() { return _usage; }
        const CVBF_Optional<Usage>& usage() const { return _usage; }

		// ��ȡ�����¼���������ƣ��룩
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
