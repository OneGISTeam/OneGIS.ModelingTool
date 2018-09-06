#ifndef OSGEARTHUTIL_GAMMA_COLOR_FILTER
#define OSGEARTHUTIL_GAMMA_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>


namespace osgEarth { namespace Util
{
    // 调整像元的Gamma值
    class OSGEARTHUTIL_EXPORT GammaColorFilter : public osgEarth::ColorFilter
    {
    public:
        GammaColorFilter();
        GammaColorFilter(const CVBF_Config& conf);
        virtual ~GammaColorFilter() { }

         // 用于矫正的gamma值
        void setGamma(float gamma);
        void setGamma(const osg::Vec3f& gamma);

        osg::Vec3f getGamma(void) const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned m_instanceId;
        ref_ptr<osg::Uniform> m_gamma;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_GAMMA_COLOR_FILTER
