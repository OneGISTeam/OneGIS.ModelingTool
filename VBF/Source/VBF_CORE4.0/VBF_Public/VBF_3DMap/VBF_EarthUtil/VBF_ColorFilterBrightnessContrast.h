#ifndef OSGEARTHUTIL_BRIGHTNESS_CONTRAST_COLOR_FILTER
#define OSGEARTHUTIL_BRIGHTNESS_CONTRAST_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    // 调整像元亮度和对比度
    class OSGEARTHUTIL_EXPORT BrightnessContrastColorFilter : public osgEarth::ColorFilter
    {
    public:
        BrightnessContrastColorFilter();
        BrightnessContrastColorFilter(const CVBF_Config& conf);
        virtual ~BrightnessContrastColorFilter() { }

        /**
        * The brightness and contrast as percentages of the incoming pixel value.
        * (For example, brightness => 1.2 to increase brightness by 20%.)
        *
        * Range is [0..inf], results are clamped to [0..1].
        */
        void setBrightnessContrast(const osg::Vec2f& bc);
        osg::Vec2f getBrightnessContrast(void) const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned                   m_instanceId;
        ref_ptr<osg::Uniform> m_bc;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_BRIGHTNESS_CONTRAST_COLOR_FILTER
