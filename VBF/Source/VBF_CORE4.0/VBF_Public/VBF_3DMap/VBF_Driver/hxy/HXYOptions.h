#ifndef OSGEARTH_DRIVER_HXY_DRIVEROPTIONS
#define OSGEARTH_DRIVER_HXY_DRIVEROPTIONS 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>

// 地图通数据请求选项
namespace osgEarth { namespace Drivers
{
    using namespace osgEarth;

    class HXYOptions : public CVBF_OptionsDriverSourceTile // NO EXPORT; header only
    {
    public:
        CVBF_Optional<URI>& url() { return _url; }
        const CVBF_Optional<URI>& url() const { return _url; }

        CVBF_Optional<std::string>& dataset() { return _dataset; }
        const CVBF_Optional<std::string>& dataset() const { return _dataset; }

    public:
        HXYOptions( const CVBF_OptionsDriverSourceTile& opt =CVBF_OptionsDriverSourceTile() ) : CVBF_OptionsDriverSourceTile( opt )
        {
            setDriver( "HXY" );
            fromConfig( m_conf );
        }
        HXYOptions( const std::string& inUrl ) : CVBF_OptionsDriverSourceTile()
        {
            setDriver( "HXY" );
            fromConfig( m_conf );
            url() = inUrl;
        }
        virtual ~HXYOptions() { }

    public:
        CVBF_Config getConfig() const
        {
            CVBF_Config conf = CVBF_OptionsDriverSourceTile::getConfig();
            conf.updateIfSet("url", _url);
            conf.updateIfSet("dataset", _dataset);
            return conf;
        }

    protected:
        void mergeConfig( const CVBF_Config& conf )
        {
            CVBF_OptionsDriverSourceTile::mergeConfig( conf );            
            fromConfig( conf );
        }

    private:
        void fromConfig( const CVBF_Config& conf )
        {
            conf.getIfSet( "url", _url );
            conf.getIfSet( "dataset", _dataset );
        }

        CVBF_Optional<URI>         _url;
        CVBF_Optional<std::string> _dataset;
    };

} } // namespace osgEarth::Drivers

#endif // OSGEARTH_DRIVER_YAHOO_DRIVEROPTIONS

