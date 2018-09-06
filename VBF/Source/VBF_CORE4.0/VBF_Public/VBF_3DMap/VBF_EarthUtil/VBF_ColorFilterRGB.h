#ifndef OSGEARTHUTIL_RGB_COLOR_FILTER
#define OSGEARTHUTIL_RGB_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    class OSGEARTHUTIL_EXPORT RGBColorFilter : public osgEarth::ColorFilter
    {
    public:
        RGBColorFilter();
        RGBColorFilter(const CVBF_Config& conf);
        virtual ~RGBColorFilter() { }

        void setRGBOffset(const osg::Vec3f& rgb);
        osg::Vec3f getRGBOffset(void) const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned m_instanceId;
        ref_ptr<osg::Uniform> m_rgb;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_RGB_COLOR_FILTER
