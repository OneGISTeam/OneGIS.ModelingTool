#ifndef OSGEARTHUTIL_HSL_COLOR_FILTER
#define OSGEARTHUTIL_HSL_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // 调整像元的hue/saturation/lightness值
    class OSGEARTHUTIL_EXPORT HSLColorFilter : public ColorFilter
    {
    public:
        HSLColorFilter();
        HSLColorFilter(const CVBF_Config& conf);
        virtual ~HSLColorFilter() { }

        // hue/saturation/lightness的偏移，每个分量为[0..1]
        void setHSLOffset( const osg::Vec3f& hsl );
        osg::Vec3f getHSLOffset() const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName() const;
        virtual void install( osg::StateSet* stateSet ) const;
        virtual CVBF_Config getConfig() const;

    protected:

        unsigned             _instanceId;
        ref_ptr<osg::Uniform> _hsl;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_HSL_COLOR_FILTER
