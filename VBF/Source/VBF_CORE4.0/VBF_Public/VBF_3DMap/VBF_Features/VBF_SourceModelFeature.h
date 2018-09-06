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

		// 生成的边的最大跨度（单位度），仅用于geocentric地图
        CVBF_Optional<double>& maxGranularity() ;
        const CVBF_Optional<double>& maxGranularity() const ;

		// 是否合并多个features的geometry
        CVBF_Optional<bool>& mergeGeometry() ;
        const CVBF_Optional<bool>& mergeGeometry() const ;

 		// 是否开启灯光
        CVBF_Optional<bool>& enableLighting() ;
        const CVBF_Optional<bool>& enableLighting() const ;

		// 显示配置
        CVBF_Optional<FeatureDisplayLayout>& layout() ;
        const CVBF_Optional<FeatureDisplayLayout>& layout() const ;

		// 是否使用聚簇裁剪
        CVBF_Optional<bool>& clusterCulling();
        const CVBF_Optional<bool>& clusterCulling() const;

		// 地物类的名字
        CVBF_Optional<StringExpression>& featureName() ;
        const CVBF_Optional<StringExpression>& featureName() const ;

 		// 是否创建索引（默认为不设）
        CVBF_Optional<FeatureSourceIndexOptions>& featureIndexing();
        const CVBF_Optional<FeatureSourceIndexOptions>& featureIndexing() const ;

		// 是否使用背面裁剪（默认是使用）
        CVBF_Optional<bool>& backfaceCulling() ;
        const CVBF_Optional<bool>& backfaceCulling() const ;

 		// 是否使用Alpha混合（默认是使用）
        CVBF_Optional<bool>& alphaBlending() ;
        const CVBF_Optional<bool>& alphaBlending() const ;

 		// 明确的数据缓存策略（来自于矢量数据源）
        CVBF_Optional<CachePolicy>& cachePolicy() ;
        const CVBF_Optional<CachePolicy>& cachePolicy() const ;

		// 淡入淡出属性
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

	// 创建矢量节点的类工厂（在数据驱动器中使用），根据一系列feature和风格设置创建节点
    class OSGEARTHFEATURES_EXPORT FeatureNodeFactory : public ::CVBF_Referenced
    {
    public:
		// 根据style渲染（或更新）features，放入一个节点中
        virtual bool createOrUpdateNode( FeatureCursor* cursor, const Style& style,
                    const FilterContext& context, ref_ptr<osg::IVBF_SGNode>&  node ) =0;


        // 创建一个组节点，包含与给定的风格对应的所有的几何体。子类可以重载该函数，以实现自定义
        virtual osg::IVBF_SGNodeGroup* getOrCreateStyleGroup( const Style& style, Session* session );
    };


	// 使用GeometryCompiler创建矢量节点的类工厂（feature_geom驱动器）
    class OSGEARTHFEATURES_EXPORT GeomFeatureNodeFactory : public FeatureNodeFactory
    {
    public:
        GeomFeatureNodeFactory( const GeometryCompilerOptions& options = GeometryCompilerOptions() );

        bool createOrUpdateNode(  FeatureCursor* features, const Style& style, const FilterContext& context,
                                  ref_ptr<osg::IVBF_SGNode>&  node );

    public:
        GeometryCompilerOptions _options;
    };


    // 矢量模型数据源
    class OSGEARTHFEATURES_EXPORT FeatureModelSource : public CVBFO_SourceModel
    {
    public:
        FeatureModelSource( const FeatureModelSourceOptions& options =FeatureModelSourceOptions() );

    public: // 重载CVBFO_SourceModel中的函数

        virtual void initialize( const osgDB::Options* dbOptions =0L );
        virtual osg::IVBF_SGNode* createNodeImplementation( const CVBF_Map* map, const osgDB::Options* dbOptions, ProgressCallback* progress );
    
    public:
        // 纯虚函数，创建FeatureNodeFactory
        virtual FeatureNodeFactory* createFeatureNodeFactory()=0;

    public:
        // 设置/获取feature数据源
        void setFeatureSource( FeatureSource* source );
        FeatureSource* getFeatureSource() { return _features.get(); }

        // 获取feature数据源的选项
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

