#ifndef VBF_EARTHFEATURES_CROP_FILTER_H
#define VBF_EARTHFEATURES_CROP_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    // 把空间数据裁剪到一个范围内
    class OSGEARTHFEATURES_EXPORT CropFilter : public FeatureFilter
    {
    public:
        enum Method 
        {
            METHOD_CENTROID,    // 如果几何中心在范围内则选择该Feature
            METHOD_CROPPING     // 把Feature的几何数据裁剪到指定的范围
        };

    public:
        CropFilter( Method method =METHOD_CENTROID );
        virtual ~CropFilter() { }

        CVBF_Optional<Method>& method() { return _method; }
        const CVBF_Optional<Method>& method() const { return _method; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );

    protected:
        CVBF_Optional<Method> _method;
    };

} } // namespace osgEarth::Features

#endif // VBF_EARTHFEATURES_CROP_FILTER_H
