#ifndef OSGEARTHUTIL_CHROMAKEY_COLOR_FILTER
#define OSGEARTHUTIL_CHROMAKEY_COLOR_FILTER

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // ͸��ɫ������
    class OSGEARTHUTIL_EXPORT ChromaKeyColorFilter : public osgEarth::ColorFilter
    {
    public:
        ChromaKeyColorFilter(void);
        ChromaKeyColorFilter(const CVBF_Config& conf);
        virtual ~ChromaKeyColorFilter(void) { }

        // ����Ϊ͸������ɫ��ÿ������Ϊ[0..1]
        void setColor( const osg::Vec3f& color );
        osg::Vec3f getColor() const;

        // ���ҽӽ�͸����ɫ�����Ծ��룬Ŀǰ���ü򵥵�3D����
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
