#ifndef OSGEARTHUTIL_CHROMAKEY_COLOR_FILTER
#define OSGEARTHUTIL_CHROMAKEY_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // 透明色过滤器
    class OSGEARTHUTIL_EXPORT ChromaKeyColorFilter : public osgEarth::ColorFilter
    {
    public:
        ChromaKeyColorFilter(void);
        ChromaKeyColorFilter(const CVBF_Config& conf);
        virtual ~ChromaKeyColorFilter(void) { }

        // 设置为透明的颜色，每个分量为[0..1]
        void setColor( const osg::Vec3f& color );
        osg::Vec3f getColor() const;

        // 查找接近透明颜色的线性距离，目前采用简单的3D距离
        void setDistance( float distance );
        float getDistance() const;

    public: // ColorFilter
        virtual std::string getEntryPointFunctionName(void) const;
        virtual void install(osg::StateSet* stateSet) const;
        virtual CVBF_Config getConfig() const;

    protected:
        unsigned int _instanceId;
        ref_ptr<osg::Uniform> _color;
        ref_ptr<osg::Uniform> _distance;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_CHROMAKEY_COLOR_FILTER
