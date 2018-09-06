#ifndef OSGEARTH_FEATURES_LABELSOURCE_H
#define OSGEARTH_FEATURES_LABELSOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FilterContext.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolText.h>

namespace osgEarth { namespace Features
{  
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

	// 标注数据源的配置选项
    class OSGEARTHFEATURES_EXPORT CVBF_OptionsDriverSourceLabel : public CVBF_OptionsDriver
    {
    public:
        CVBF_OptionsDriverSourceLabel( const CVBF_Options& options =CVBF_Options() )
            : CVBF_OptionsDriver( options )
        {
            fromConfig(m_conf);
        }
        
        virtual ~CVBF_OptionsDriverSourceLabel() { }

    public:
        virtual CVBF_Config getConfig() const;

    protected:
        virtual void mergeConfig( const CVBF_Config& conf );
        
    private:
        void fromConfig( const CVBF_Config& conf );
    };

    //--------------------------------------------------------------------


	// 生成文字标注节点的插件
    class OSGEARTHFEATURES_EXPORT LabelSource : public osg::CVBF_Object, public Revisioned
    {
    public:        
        LabelSource( const CVBF_OptionsDriverSourceLabel& options =CVBF_OptionsDriverSourceLabel() )
        {
        }

        virtual osg::IVBF_SGNode* createNode( const FeatureList& input, const Style& style, const FilterContext& context ) =0;

		// 根据文本及风格创建一个节点
        virtual osg::IVBF_SGNode* createNode( const std::string&  text, const Style& style ) =0;

    public:
        
        // META_Object specialization:
        virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
        virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const LabelSource*>(obj)!=NULL; }
        virtual const char* className() const { return "LabelSource"; }
        virtual const char* libraryName() const { return "osgEarth::Features"; }

    protected:
        virtual ~LabelSource() { }
    };

    //--------------------------------------------------------------------

    class OSGEARTHFEATURES_EXPORT LabelSourceDriver : public osgDB::ReaderWriter
    {
    protected:
        const CVBF_OptionsDriverSourceLabel& getLabelSourceOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
        virtual const char* className() const;
    };

    //--------------------------------------------------------------------

    class OSGEARTHFEATURES_EXPORT LabelSourceFactory
    {   
	public:
        static LabelSource* create( const CVBF_OptionsDriverSourceLabel& options =CVBF_OptionsDriverSourceLabel() );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTH_FEATURES_LABELSOURCE_H
