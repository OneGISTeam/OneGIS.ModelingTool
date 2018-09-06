//***************************************************************************************
// FileName：VBF_TileSourceOptions.h
// Function：地块数据源选项
// Author:   杜莹
// Date:     2012-11-12
//***************************************************************************************

#ifndef __VBF_TILE_SOURCE_OPTIONS_H__
#define __VBF_TILE_SOURCE_OPTIONS_H__

#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/HeightFieldUtils.h>
		
using namespace osgEarth;

class CVBF_TileSourceVBF30sOptions : public CVBF_OptionsDriverSourceTile // NO EXPORT; header only
{
public:
    CVBF_TileSourceVBF30sOptions(const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() ) :
		CVBF_OptionsDriverSourceTile( options )
		{
            m_opL0.init(-180.0);
            m_opL1.init( 180.0);
            m_opB0.init( -90.0);
            m_opB1.init(  90.0);

            setDriver( "vbf30s" );
			fromConfig(m_conf);
		}

virtual ~CVBF_TileSourceVBF30sOptions() {}

public:

	CVBF_Config getConfig() const
	{
		CVBF_Config conf = CVBF_OptionsDriverSourceTile::getConfig();
        conf.updateIfSet("name", m_opName );
        conf.updateIfSet("visible",  m_opVisible );
        conf.updateIfSet("L0",  m_opL0 );
        conf.updateIfSet("L1",  m_opL1 );
        conf.updateIfSet("B0",  m_opB0 );
        conf.updateIfSet("B1",  m_opB1 );
        return conf;
	}

	void mergeConfig( const CVBF_Config& conf ) 
	{
		CVBF_OptionsDriverSourceTile::mergeConfig( conf );
        fromConfig( conf );

        CVBF_ConfigList children = conf.children( "url" );
        for( CVBF_ConfigList::const_iterator i = children.begin(); i != children.end(); ++i )
        {
            m_conf.add(*i);
        }
    }

	void fromConfig( const CVBF_Config& conf ) 
	{
        conf.getIfSet("name",  m_opName );
        conf.getIfSet("visible",  m_opVisible );
        conf.getIfSet("L0",  m_opL0 );
        conf.getIfSet("L1",  m_opL1 );
        conf.getIfSet("B0",  m_opB0 );
        conf.getIfSet("B1",  m_opB1 );
    }

    const CVBF_Optional<double>& GetL0() const	{ return m_opL0; }
    const CVBF_Optional<double>& GetL1() const	{ return m_opL1; }
    const CVBF_Optional<double>& GetB0() const	{ return m_opB0; }
    const CVBF_Optional<double>& GetB1() const	{ return m_opB1; }

protected:
    CVBF_Optional<std::string>        m_opName;
    CVBF_Optional<std::string>        m_opVisible;

    CVBF_Optional<double>        m_opL0;
    CVBF_Optional<double>        m_opL1;
    CVBF_Optional<double>        m_opB0;
    CVBF_Optional<double>        m_opB1;

};


#endif
