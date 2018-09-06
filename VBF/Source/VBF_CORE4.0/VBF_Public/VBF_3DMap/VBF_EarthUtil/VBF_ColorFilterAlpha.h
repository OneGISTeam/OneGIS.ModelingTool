#ifndef OSGEARTHUTIL_ALPHA_COLOR_FILTER
#define OSGEARTHUTIL_ALPHA_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    class OSGEARTHUTIL_EXPORT AlphaColorFilter : public osgEarth::ColorFilter
    {
    public:
        AlphaColorFilter();
        AlphaColorFilter(const CVBF_Config& conf);
        virtual ~AlphaColorFilter() { }

        void setAlpha(float alpha);
        float getAlpha(void) const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned m_instanceId;
        ref_ptr<osg::Uniform> m_alpha;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_ALPHA_COLOR_FILTER
