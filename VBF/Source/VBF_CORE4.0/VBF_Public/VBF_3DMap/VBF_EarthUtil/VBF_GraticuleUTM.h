#ifndef OSGEARTHUTIL_UTM_GRATICLE
#define OSGEARTHUTIL_UTM_GRATICLE

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

    /**
     * Configuration options for the geodetic graticule.
     */
    class OSGEARTHUTIL_EXPORT UTMGraticuleOptions : public CVBF_Options
    {
    public:
        UTMGraticuleOptions( const CVBF_Config& conf =CVBF_Config() );

        /** dtor */
        virtual ~UTMGraticuleOptions() { }


    public:

        /** Default style for grid lines and text */
        CVBF_Optional<Style>& primaryStyle() { return _primaryStyle; }
        const CVBF_Optional<Style>& primaryStyle() const { return _primaryStyle; }

        /** Text scale factor (default = 1) */
        CVBF_Optional<float>& textScale() { return _textScale; }
        const CVBF_Optional<float>& textScale() const { return _textScale; }

    public:
        CVBF_Config getConfig() const;

    protected:
        CVBF_Optional<Style>    _primaryStyle;
        CVBF_Optional<float>    _textScale;

        void mergeConfig( const CVBF_Config& conf );
    };


    /**
     * Implements a UTM map graticule. 
     * 
     * NOTE: So far, this only works for geocentric maps.
     * TODO: Add projected support; add text label support
     */
    class OSGEARTHUTIL_EXPORT UTMGraticule : public osg::CVBF_SGNodeGroup, public MapNodeObserver
    {
    public:

        /**
         * Constructs a new graticule for use with the specified map. The graticule
         * is created with several default levels. If you call addLevel(), the 
         * default levels are deleted.
         *
         * @param map
         *      CVBF_Map with which you will use this graticule
         * @param options
         *      Optional "options" that configure the graticule. Defaults will be used
         *      if you don't specify this.
         */
        UTMGraticule( CVBFO_SGNodeMap* mapNode );
        UTMGraticule( CVBFO_SGNodeMap* mapNode, const UTMGraticuleOptions& options);

        /** dtor */
        virtual ~UTMGraticule() { }

        /** 
         * Applies a new set of options. The graticule will be rebuilt if necessary.
         */
        void setOptions( const UTMGraticuleOptions& options );

        /**
         * Gets the options with which the graticule was built.
         */
        const UTMGraticuleOptions& getOptions() const { return _options.value(); }

        
    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

        virtual CVBFO_SGNodeMap* GetMapNode() { return _mapNode.get(); }


    protected:
        ref_ptr<const CVBF_Profile>        _profile;
        ref_ptr<const FeatureProfile> _featureProfile;

        unsigned int               _id;
        observer_ptr<CVBFO_SGNodeMap> _mapNode;
        osg::IVBF_SGNodeGroup*                _root;

        CVBF_Optional<UTMGraticuleOptions> _options;

        typedef std::map<std::string, CVBF_GeoExtent> SectorTable;
        SectorTable _gzd;

        osg::StateAttribute* _depthAttribute;

    protected:
        unsigned int getID() const { return _id; }
        void init();
        void rebuild();
        osg::IVBF_SGNode* buildGZDTile( const std::string& name, const CVBF_GeoExtent& extent );
        //osg::IVBF_SGNode* buildPolarGZDTiles();

        virtual osg::IVBF_SGNodeGroup* buildGZDChildren( osg::IVBF_SGNodeGroup* node, const std::string& gzd ) {
            return node; }

    public:
        static CVBF_Mutex s_graticuleMutex;
        typedef std::map<unsigned, ref_ptr<UTMGraticule> > UTMGraticuleRegistry;
        static UTMGraticuleRegistry s_graticuleRegistry;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_UTM_GRATICLE
