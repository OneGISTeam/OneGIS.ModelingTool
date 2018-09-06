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

    // 地理坐标网的配置项
    class OSGEARTHUTIL_EXPORT GeodeticGraticuleOptions : public CVBF_Options
    {
    public:
        GeodeticGraticuleOptions( const CVBF_Config& conf =CVBF_Config() );
        virtual ~GeodeticGraticuleOptions() { }

    public:
        struct Level // 定义每个尺度的范围、风格
        {
            float    _minRange, _maxRange;
            unsigned _subdivisionFactor;
            CVBF_Optional<Style> _lineStyle;
            CVBF_Optional<Style> _textStyle;
        };

        // 默认的网格线风格
        CVBF_Optional<Style>& lineStyle() { return _defaultLineStyle; }
        const CVBF_Optional<Style>& lineStyle() const { return _defaultLineStyle; }

        // 默认的文字风格
        CVBF_Optional<Style>& textStyle() { return _defaultTextStyle; }
        const CVBF_Optional<Style>& textStyle() const { return _defaultTextStyle; }

        // 获取各尺度信息
        const std::vector<Level>& levels() const { return _levels; }
        void clearLevels();

        // 添加一个新的LOD，只能按maxRange的降序添加，即由远及近
        // maxRange最远距离，minRange最近距离（尽管每级都可设置，但仅最近的一级有效，用于近距离时禁止显示坐标网格）
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


    // 绘制地理网格，仅能支持地理坐标参考的地图
    // 下一步支持投影坐标系统，添加标注
    // 性能低是因为：1、采用大圆线差值（可以改为视点远时采用大圆线差值）
    //             2、贴地表绘制，可以改为compiler.options().ignoreAltitudeSymbol = true;
    class OSGEARTHUTIL_EXPORT GeodeticGraticule : public osg::CVBF_SGNodeGroup, public MapNodeObserver
    {
    public:

        // 创建了几个默认的级别，当使用addLevel()函数后默认的级别将被删除
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
