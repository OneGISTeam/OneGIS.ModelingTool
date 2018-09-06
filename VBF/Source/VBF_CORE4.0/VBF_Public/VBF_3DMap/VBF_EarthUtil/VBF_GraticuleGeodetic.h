#ifndef OSGEARTHUTIL_GEODETIC_GRATICLE
#define OSGEARTHUTIL_GEODETIC_GRATICLE

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Terrain/MapNodeObserver.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <vector>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;
    using namespace osgEarth::Features;
    using namespace osgEarth::Symbology;

    // ������������������
    class OSGEARTHUTIL_EXPORT GeodeticGraticuleOptions : public CVBF_Options
    {
    public:
        GeodeticGraticuleOptions( const CVBF_Config& conf =CVBF_Config() );
        virtual ~GeodeticGraticuleOptions() { }

    public:
        struct Level // ����ÿ���߶ȵķ�Χ�����
        {
            float    _minRange, _maxRange;
            unsigned _subdivisionFactor;
            CVBF_Optional<Style> _lineStyle;
            CVBF_Optional<Style> _textStyle;
        };

        // Ĭ�ϵ������߷��
        CVBF_Optional<Style>& lineStyle() { return _defaultLineStyle; }
        const CVBF_Optional<Style>& lineStyle() const { return _defaultLineStyle; }

        // Ĭ�ϵ����ַ��
        CVBF_Optional<Style>& textStyle() { return _defaultTextStyle; }
        const CVBF_Optional<Style>& textStyle() const { return _defaultTextStyle; }

        // ��ȡ���߶���Ϣ
        const std::vector<Level>& levels() const { return _levels; }
        void clearLevels();

        // ���һ���µ�LOD��ֻ�ܰ�maxRange�Ľ�����ӣ�����Զ����
        // maxRange��Զ���룬minRange������루����ÿ���������ã����������һ����Ч�����ڽ�����ʱ��ֹ��ʾ��������
        void addLevel( float maxRange, float minRange =0.0f, unsigned subdivisionFactor =2u,
                 const Style& lineStyle = Style(), const Style& textStyle = Style() );

    public:
        CVBF_Config getConfig() const;

    protected:
        CVBF_Optional<Style>    _defaultLineStyle;
        CVBF_Optional<Style>    _defaultTextStyle;
        std::vector<Level> _levels;

        void mergeConfig( const CVBF_Config& conf );
    };


    // ���Ƶ������񣬽���֧�ֵ�������ο��ĵ�ͼ
    // ��һ��֧��ͶӰ����ϵͳ����ӱ�ע
    // ���ܵ�����Ϊ��1�����ô�Բ�߲�ֵ�����Ը�Ϊ�ӵ�Զʱ���ô�Բ�߲�ֵ��
    //             2�����ر���ƣ����Ը�Ϊcompiler.options().ignoreAltitudeSymbol = true;
    class OSGEARTHUTIL_EXPORT GeodeticGraticule : public osg::CVBF_SGNodeGroup, public MapNodeObserver
    {
    public:

        // �����˼���Ĭ�ϵļ��𣬵�ʹ��addLevel()������Ĭ�ϵļ��𽫱�ɾ��
        GeodeticGraticule( CVBFO_SGNodeMap* mapNode );
        GeodeticGraticule( CVBFO_SGNodeMap* mapNode, const GeodeticGraticuleOptions& options);

        virtual ~GeodeticGraticule() { }

        void setOptions( const GeodeticGraticuleOptions& options );
        const GeodeticGraticuleOptions& getOptions() const { return _options.value(); }

    public: // osg::Node
        virtual void traverse(osg::NodeVisitor& nv);

    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );
        virtual CVBFO_SGNodeMap* GetMapNode() { return _mapNode.get(); }


    private:
        ref_ptr<const CVBF_Profile> _profile;
        ref_ptr<const FeatureProfile> _featureProfile;

        unsigned int               _id;
        observer_ptr<CVBFO_SGNodeMap> _mapNode;
        osg::IVBF_SGNodeGroup*        _root;

        CVBF_Optional<GeodeticGraticuleOptions> _options;

    private:
        unsigned int getID() const { return _id; }
        void init();
        void rebuild();
        osg::IVBF_SGNode* buildTile( const CVBF_TileKey& key, CVBF_Map* map ) const;
        osg::IVBF_SGNode* buildChildren( unsigned level, unsigned x, unsigned y ) const;

        friend class GeodeticGraticuleFactory;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_GEODETIC_GRATICLE
