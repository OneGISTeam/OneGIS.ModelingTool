#ifndef OSGEARTHFEATURES_BUILD_TEXT_FILTER_H
#define OSGEARTHFEATURES_BUILD_TEXT_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features 
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


	// 从矢量数据（feature）构建注记（label）
    class OSGEARTHFEATURES_EXPORT BuildTextFilter : public FeaturesToNodeFilter
    {
    public:
        BuildTextFilter( const Style& style =Style() );
        virtual ~BuildTextFilter() { }

		// 设置/获取Style
        const Style& getStyle() { return _style; }
        void setStyle(const Style& s) { _style = s; }

 		// 传入数据列表，并进行处理
        osg::IVBF_SGNode* push( FeatureList& input, FilterContext& context );

    protected:
        ref_ptr<osg::IVBF_SGNodeGeometry> _geode;
        Style                    _style;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H
