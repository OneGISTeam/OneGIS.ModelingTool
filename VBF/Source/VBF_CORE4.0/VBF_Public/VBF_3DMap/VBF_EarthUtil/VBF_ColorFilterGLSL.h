#ifndef OSGEARTHUTIL_GLSL_COLOR_FILTER
#define OSGEARTHUTIL_GLSL_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    // 允许用户植入GLSL代码进行像元的颜色调整
    class OSGEARTHUTIL_EXPORT GLSLColorFilter : public osgEarth::ColorFilter
    {
    public:
        GLSLColorFilter();
        GLSLColorFilter(const CVBF_Config& conf);
        virtual ~GLSLColorFilter() { }

        void setCode(const std::string& code) { _code = code; }
        const std::string& getCode() const { return _code; }

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned m_instanceId;
        void init();
        std::string _code;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_GLSL_COLOR_FILTER
