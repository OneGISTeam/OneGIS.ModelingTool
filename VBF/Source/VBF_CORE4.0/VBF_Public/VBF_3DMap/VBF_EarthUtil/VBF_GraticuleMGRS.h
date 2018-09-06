#ifndef OSGEARTHUTIL_MGRS_GRATICLE
#define OSGEARTHUTIL_MGRS_GRATICLE

#include <VBF_3DMap/VBF_EarthUtil/VBF_GraticuleUTM.h>

// ���ƾ�����������ϵͳ
namespace osgEarth { namespace Util
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    class OSGEARTHUTIL_EXPORT MGRSGraticuleOptions : public UTMGraticuleOptions
    {
    public:
        MGRSGraticuleOptions( const CVBF_Config& conf =CVBF_Config() );
        virtual ~MGRSGraticuleOptions() { }

        // �ߺ����ֵ���ʽ
        CVBF_Optional<Style>& secondaryStyle() { return _secondaryStyle; }
        const CVBF_Optional<Style>& secondaryStyle() const { return _secondaryStyle; }
    public:
        CVBF_Config getConfig() const;
    protected:
        void mergeConfig( const CVBF_Config& conf );
        CVBF_Optional<Style> _secondaryStyle;
    };


    // ���ƾ�����������ϵͳ������֧�ֵ�������ο��ĵ�ͼ
    // ��һ��֧��ͶӰ����ϵͳ����ӱ�ע
    class OSGEARTHUTIL_EXPORT MGRSGraticule : public UTMGraticule
    {
    public:

        // �����˼���Ĭ�ϵļ��𣬵�ʹ��addLevel()������Ĭ�ϵļ��𽫱�ɾ��
        MGRSGraticule( CVBFO_SGNodeMap* mapNode );
        MGRSGraticule( CVBFO_SGNodeMap* mapNode, const MGRSGraticuleOptions& options);

        virtual ~MGRSGraticule() { }

        void setOptions( const MGRSGraticuleOptions& options );
        const MGRSGraticuleOptions& getOptions() const { return _options.value(); }

    public:
        osg::IVBF_SGNode* buildSQIDTiles( const std::string& gzd );

    protected:
        CVBF_Optional<MGRSGraticuleOptions> _options;
        ref_ptr<osg::Uniform>     _minDepthOffset;

    protected:
        virtual osg::IVBF_SGNodeGroup* buildGZDChildren( osg::IVBF_SGNodeGroup* node, const std::string& gzd );
        
        CVBF_GeoExtent getExtent( const std::string& gzd, const std::string& sqid );

        friend class MGRSGraticuleFactory;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_UTM_GRATICLE
