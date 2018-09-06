#ifndef OSGEARTH_DRIVER_GEOSERVER_DRIVEROPTIONS
#define OSGEARTH_DRIVER_GEOSERVER_DRIVEROPTIONS 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>

// 地图通数据请求选项
namespace osgEarth { namespace Drivers
{
    using namespace osgEarth;

    class GeoServerOptions : public CVBF_OptionsDriverSourceTile // NO EXPORT; header only
    {
    public:
        CVBF_Optional<URI>& url() { return _url; }
        const CVBF_Optional<URI>& url() const { return _url; }

        CVBF_Optional<std::string>& DataSet() { return m_opsDataSet; }
        const CVBF_Optional<std::string>& DataSet() const { return m_opsDataSet; }

    public:
        GeoServerOptions( const CVBF_OptionsDriverSourceTile& opt =CVBF_OptionsDriverSourceTile() ) : CVBF_OptionsDriverSourceTile( opt )
        {
            setDriver( "GeoServer" );
            fromConfig( m_conf );
        }
        GeoServerOptions( const std::string& inUrl ) : CVBF_OptionsDriverSourceTile()
        {
            setDriver( "GeoServer" );
            fromConfig( m_conf );
            url() = inUrl;
        }
        virtual ~GeoServerOptions() { }

    public:
        CVBF_Config getConfig() const
        {

            CVBF_Config conf = CVBF_OptionsDriverSourceTile::getConfig();
            conf.updateIfSet("url", _url);
            conf.updateIfSet("dataset", m_opsDataSet);
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
            conf.getIfSet( "dataset", m_opsDataSet );

        }

        CVBF_Optional<URI>         _url;
        CVBF_Optional<std::string> m_opsDataSet;
    };

} } // namespace osgEarth::Drivers

#endif // OSGEARTH_DRIVER_GeoServer_DRIVEROPTIONS

