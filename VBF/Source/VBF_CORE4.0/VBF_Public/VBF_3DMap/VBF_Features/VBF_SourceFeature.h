#ifndef OSGEARTHFEATURES_FEATURE_SOURCE_H
#define OSGEARTHFEATURES_FEATURE_SOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FeatureCursor.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Query.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>

#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <OpenThreads/Mutex>
#include <list>

namespace osgEarth { namespace Features
{   
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

	// ���ڴ���ʸ������Դ����������Դ��������ѡ��
    class OSGEARTHFEATURES_EXPORT CVBF_OptionsDriverSourceFeature : public CVBF_OptionsDriver
    {
    public: // ����

		// ����Դ������
 //IE����       CVBF_Optional<std::string>& name() { return m_sName; }
        const CVBF_Optional<std::string>& name() const { return m_sName; }

		// ������Դ��ȡ���ݵĹ�������filteres���б�
        FeatureFilterList& filters() { return _filters; }
        const FeatureFilterList& filters() const { return _filters; }

		// �Ƿ���д�ķ�ʽ�����ݣ����֧�ֵĻ���
        CVBF_Optional<bool>& openWrite() { return _openWrite; }
        const CVBF_Optional<bool>& openWrite() const { return _openWrite; }

		// ���أ�������ʵ������Դ�е�profile��Ϣ
        CVBF_Optional<CVBF_OptionsProfile>& profile() { return _profile; }
        const CVBF_Optional<CVBF_OptionsProfile>& profile() const { return _profile; }
        void SetName(std::string sName) { m_sName = sName; }


    public:
        CVBF_OptionsDriverSourceFeature( const CVBF_Options& options =CVBF_Options() );
        virtual ~CVBF_OptionsDriverSourceFeature();
        virtual CVBF_Config getConfig() const;
        CVBF_OptionsDriverSourceFeature& operator = ( const CVBF_OptionsDriverSourceFeature& rhs );

    protected:
        virtual void mergeConfig( const CVBF_Config& conf );

    private:
        void fromConfig( const CVBF_Config& conf );

        FeatureFilterList        _filters;
        CVBF_Optional<std::string>    m_sName;
        CVBF_Optional< bool >         _openWrite;
        CVBF_Optional<CVBF_OptionsProfile> _profile;
        CVBF_Optional<CachePolicy>    _cachePolicy;
    };


	// FeatureSource��һ������ʸ�����ݵĿɲ�����󣬲����з����Ϣ����ѡ��
    class OSGEARTHFEATURES_EXPORT FeatureSource : public osg::CVBF_Object, public Revisioned
    {
    public:      

		// �����ṩ�Ķ�дѡ���һ��ʸ������Դ
        FeatureSource( const CVBF_Options& options=CVBF_Options(), const osgDB::Options* dbOptions =0L );

        // ��ȡ������ʸ�����ݵ�Ԫ���ݣ�����Դ�ɹ���ʼ��֮�����Ч��
        const FeatureProfile* getFeatureProfile() const;

        // ��ȡ����Դ��ѡ����
        const CVBF_OptionsDriverSourceFeature& getFeatureSourceOptions() const { return _options; }

        // ����һ���α꣬���ڲ�ѯʱ�������е�features
        virtual FeatureCursor* createFeatureCursor( const Symbology::Query& query =Symbology::Query() ) =0;

		// ������Դ�Ƿ�֧�ֲ����ɾ��ʸ������
        virtual bool isWritable() const { return false; }

		// ɾ������ID�����ݣ��ɹ�����true��ʧ�ܻ�����ԴΪֻ��ʱ����false
        virtual bool deleteFeature(FeatureID fid) { return false; }

		// ��ȡ������Դ�е�ʸ�����ݵ������������ȷ������-1
        virtual int getFeatureCount() const { return -1; }

		// ��ȡ����ID�����ݣ��Ҳ����򷵻�NULL
        virtual Feature* getFeature( FeatureID fid ) { return 0L; }

		// ��ȡ����������Ա�����Ϊ��
        virtual const FeatureSchema& getSchema() const;

		// ����һ������������ɹ�����true�����򷵻�false
        virtual bool insertFeature(Feature* feature) { return false; }

		// ��ȡ����Դ�м���������ͣ��㡢�ߡ��桢���ȣ�
        virtual Geometry::Type getGeometryType() const { return Geometry::TYPE_UNKNOWN; }


    public: // ������	
        void addToBlacklist( FeatureID fid );// ������������һ�������ID��
        void removeFromBlacklist( FeatureID fid );// �Ӻ��������Ƴ�һ�������ID��
        void clearBlacklist();// ��պ�����
        bool isBlacklisted( FeatureID fid ) const; // �жϸ�ID���Ƿ��ں�������

    public: // ���
        // ����Դ�Ƿ���Ƕ��ķ�񻯣��ڵ������ݵ��������з����Ϣ����Ĭ��Ϊfalse      
        virtual bool hasEmbeddedStyles() const { return false; }

    public:
        // ��ȡ���������б���ѯʱ��������
        const FeatureFilterList& getFilters() const;

    public: 

        // META_Object specialization:
        virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
        virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const FeatureSource*>(obj)!=NULL; }
        virtual const char* className() const { return "FeatureSource"; }
        virtual const char* libraryName() const { return "VBF_Features"; }

		// ��ʼ��
        virtual void initialize( const osgDB::Options* dbOptions =0L ) { }

  		// �������profile��dirty��־
        void dirtyFeatureProfile() { _featureProfile = 0;}

    protected:
        virtual ~FeatureSource();

		// ������������һ�������ĵ����������������Ԫ���ݽṹ���÷�������������getFeatureProfile()����       
        virtual const FeatureProfile* createFeatureProfile() =0;

		// ���ʴ����DBѡ��
        const osgDB::Options* dbOptions() const { return _dbOptions.get(); }
        const URIContext& uriContext() const { return _uriContext; } // ���ڽ������·��

        Cache* getCache() const { return _cache.get(); }  // ��ȡ���棨ͨ��dbOptions����ģ�

    private:
        const CVBF_OptionsDriverSourceFeature _options;
        ref_ptr<const FeatureProfile> _featureProfile;
        CVBF_Mutex                   _createMutex;

        ref_ptr<const osgDB::Options> _dbOptions;
        URIContext                    _uriContext;
        observer_ptr<Cache>           _cache;

        CVBF_ReadWriteMutex          _blacklistMutex;
        std::set<FeatureID>                _blacklist;

        friend class CVBF_Map;
        friend class FeatureSourceFactory;
    };

	// ʸ������Դ������
    class OSGEARTHFEATURES_EXPORT FeatureSourceDriver : public osgDB::ReaderWriter
    {
    public:
        virtual const CVBF_OptionsDriverSourceFeature& getFeatureSourceOptions( const osgDB::ReaderWriter::Options* rwopt ) const;
        virtual const char* className() const;
    };


	// ʸ������Դ�๤�����������������������ִ���һ��ʸ������Դ
    class OSGEARTHFEATURES_EXPORT FeatureSourceFactory
    {
	public:
        static FeatureSource* create( const CVBF_OptionsDriverSourceFeature& options );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_SOURCE_H

