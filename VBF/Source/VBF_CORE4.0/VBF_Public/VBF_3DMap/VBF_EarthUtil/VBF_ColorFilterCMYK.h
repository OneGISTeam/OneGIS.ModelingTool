#ifndef OSGEARTHUTIL_CMYK_COLOR_FILTER
#define OSGEARTHUTIL_CMYK_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    // 调整像元的cyan/magenta/yellow/black值
    class OSGEARTHUTIL_EXPORT CMYKColorFilter : public osgEarth::ColorFilter
    {
    public:
        CMYKColorFilter();
        CMYKColorFilter(const CVBF_Config& conf);
        virtual ~CMYKColorFilter() { }

        /**
        * The cyan/magenta/yellow offset, each component is [-1..1] (no change is at 0)
        */
        void setCMYOffset(const osg::Vec3f& cmy);
        osg::Vec3f getCMYOffset(void) const;

        /**
        * The cyan/magenta/yellow/black offset, each component is [-1..1] (no change is at 0)
        */
        void setCMYKOffset(const osg::Vec4f& cmyk);
        osg::Vec4f getCMYKOffset(void) const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned m_instanceId;
        ref_ptr<osg::Uniform> m_cmyk;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_CMYK_COLOR_FILTER
