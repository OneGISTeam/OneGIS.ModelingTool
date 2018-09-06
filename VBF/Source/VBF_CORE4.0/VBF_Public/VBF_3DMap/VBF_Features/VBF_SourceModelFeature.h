#ifndef OSGEARTHFEATURES_FEATURE_MODEL_SOURCE_H
#define OSGEARTHFEATURES_FEATURE_MODEL_SOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_3DMap/VBF_Features/FeatureSourceIndexNode.h>
#include <VBF_3DMap/VBF_Features/FeatureDisplayLayout.h>
#include <VBF_3DMap/VBF_Features/GeometryCompiler.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeFade.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceModel.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <list>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    class OSGEARTHFEATURES_EXPORT FeatureModelSourceOptions : public CVBF_OptionsDriverSourceModel
    {
    public: 
        FeatureModelSourceOptions& operator = ( const FeatureModelSourceOptions& rhs );

        CVBF_Optional<CVBF_OptionsDriverSourceFeature>& featureOptions() ;
        const CVBF_Optional<CVBF_OptionsDriverSourceFeature>& featureOptions() const ;

        ref_ptr<StyleSheet>& styles() ;
        const ref_ptr<StyleSheet>& styles() const ;

		// ���ɵıߵ�����ȣ���λ�ȣ���������geocentric��ͼ
        CVBF_Optional<double>& maxGranularity() ;
        const CVBF_Optional<double>& maxGranularity() const ;

		// �Ƿ�ϲ����features��geometry
        CVBF_Optional<bool>& mergeGeometry() ;
        const CVBF_Optional<bool>& mergeGeometry() const ;

 		// �Ƿ����ƹ�
        CVBF_Optional<bool>& enableLighting() ;
        const CVBF_Optional<bool>& enableLighting() const ;

		// ��ʾ����
        CVBF_Optional<FeatureDisplayLayout>& layout() ;
        const CVBF_Optional<FeatureDisplayLayout>& layout() const ;

		// �Ƿ�ʹ�þ۴زü�
        CVBF_Optional<bool>& clusterCulling();
        const CVBF_Optional<bool>& clusterCulling() const;

		// �����������
        CVBF_Optional<StringExpression>& featureName() ;
        const CVBF_Optional<StringExpression>& featureName() const ;

 		// �Ƿ񴴽�������Ĭ��Ϊ���裩
        CVBF_Optional<FeatureSourceIndexOptions>& featureIndexing();
        const CVBF_Optional<FeatureSourceIndexOptions>& featureIndexing() const ;

		// �Ƿ�ʹ�ñ���ü���Ĭ����ʹ�ã�
        CVBF_Optional<bool>& backfaceCulling() ;
        const CVBF_Optional<bool>& backfaceCulling() const ;

 		// �Ƿ�ʹ��Alpha��ϣ�Ĭ����ʹ�ã�
        CVBF_Optional<bool>& alphaBlending() ;
        const CVBF_Optional<bool>& alphaBlending() const ;

 		// ��ȷ�����ݻ�����ԣ�������ʸ������Դ��
        CVBF_Optional<CachePolicy>& cachePolicy() ;
        const CVBF_Optional<CachePolicy>& cachePolicy() const ;

		// ���뵭������
        CVBF_Optional<CVBF_FadeOptions>& fading();
        const CVBF_Optional<CVBF_FadeOptions>& fading() const ;

    public:
        // A live feature source instance to use. Note, this does not serialize.
        ref_ptr<FeatureSource>& featureSource();
        const ref_ptr<FeatureSource>& featureSource() const;

    public:
        FeatureModelSourceOptions( const CVBF_Options& rhs =CVBF_Options() );

        virtual ~FeatureModelSourceOptions();

        virtual CVBF_Config getConfig() const;

    protected:
        virtual void mergeConfig( const CVBF_Config& conf );

    private:
        void fromConfig( const CVBF_Config& conf );

        CVBF_Optional<CVBF_OptionsDriverSourceFeature>      _featureOptions;
        CVBF_Optional<FeatureDisplayLayout>      _layout;
        CVBF_Optional<StringExpression>          _featureNameExpr;
        CVBF_Optional<bool>                      _lit;
        CVBF_Optional<double>                    _maxGranularity_deg;
        CVBF_Optional<bool>                      _mergeGeometry;
        CVBF_Optional<bool>                      _clusterCulling;
        CVBF_Optional<bool>                      _backfaceCulling;
        CVBF_Optional<bool>                      _alphaBlending;
        CVBF_Optional<CachePolicy>               _cachePolicy;
        CVBF_Optional<CVBF_FadeOptions>               _fading;
        CVBF_Optional<FeatureSourceIndexOptions> _featureIndexing;

        ref_ptr<StyleSheet>            _styles;
        ref_ptr<FeatureSource>         _featureSource;
    };

	// ����ʸ���ڵ���๤������������������ʹ�ã�������һϵ��feature�ͷ�����ô����ڵ�
    class OSGEARTHFEATURES_EXPORT FeatureNodeFactory : public ::CVBF_Referenced
    {
    public:
		// ����style��Ⱦ������£�features������һ���ڵ���
        virtual bool createOrUpdateNode( FeatureCursor* cursor, const Style& style,
                    const FilterContext& context, ref_ptr<osg::IVBF_SGNode>&  node ) =0;


        // ����һ����ڵ㣬����������ķ���Ӧ�����еļ����塣����������ظú�������ʵ���Զ���
        virtual osg::IVBF_SGNodeGroup* getOrCreateStyleGroup( const Style& style, Session* session );
    };


	// ʹ��GeometryCompiler����ʸ���ڵ���๤����feature_geom��������
    class OSGEARTHFEATURES_EXPORT GeomFeatureNodeFactory : public FeatureNodeFactory
    {
    public:
        GeomFeatureNodeFactory( const GeometryCompilerOptions& options = GeometryCompilerOptions() );

        bool createOrUpdateNode(  FeatureCursor* features, const Style& style, const FilterContext& context,
                                  ref_ptr<osg::IVBF_SGNode>&  node );

    public:
        GeometryCompilerOptions _options;
    };


    // ʸ��ģ������Դ
    class OSGEARTHFEATURES_EXPORT FeatureModelSource : public CVBFO_SourceModel
    {
    public:
        FeatureModelSource( const FeatureModelSourceOptions& options =FeatureModelSourceOptions() );

    public: // ����CVBFO_SourceModel�еĺ���

        virtual void initialize( const osgDB::Options* dbOptions =0L );
        virtual osg::IVBF_SGNode* createNodeImplementation( const CVBF_Map* map, const osgDB::Options* dbOptions, ProgressCallback* progress );
    
    public:
        // ���麯��������FeatureNodeFactory
        virtual FeatureNodeFactory* createFeatureNodeFactory()=0;

    public:
        // ����/��ȡfeature����Դ
        void setFeatureSource( FeatureSource* source );
        FeatureSource* getFeatureSource() { return _features.get(); }

        // ��ȡfeature����Դ��ѡ��
        virtual const FeatureModelSourceOptions& getFeatureModelOptions() const { return _options; }

    public: 

        // META_Object specialization:
        virtual osg::CVBF_Object* cloneType() const;
        virtual osg::CVBF_Object* clone(const osg::CopyOp&) const;
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const;
        virtual const char* className() const;
        virtual const char* libraryName() const;

    protected:
        virtual ~FeatureModelSource();

        ref_ptr<FeatureSource>          _features;
        observer_ptr<const CVBF_Map>    _map;
        const FeatureModelSourceOptions _options;
        ref_ptr<FeatureNodeFactory>     _factory;
        ref_ptr<const osgDB::Options>   _dbOptions;

    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_SOURCE_H

