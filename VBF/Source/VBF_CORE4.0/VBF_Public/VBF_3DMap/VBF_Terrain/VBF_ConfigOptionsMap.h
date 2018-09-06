#ifndef OSGEARTH_MAP_OPTIONS_H
#define OSGEARTH_MAP_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>


// map ��������
class OSGEARTH_EXPORT CVBF_ConfigOptionsMap : public CVBF_ConfigOptions // no export (header-only)
{
public:
    enum CoordinateSystemType // ����ϵͳ����
    {
        CSTYPE_GEOCENTRIC,       // ��������ϵ
        CSTYPE_GEOCENTRIC_CUBE,	 // ��������������ϵ
        CSTYPE_PROJECTED         // ͶӰ����ϵ
    };		

public:
    CVBF_ConfigOptionsMap( const CVBF_ConfigOptions& options =CVBF_ConfigOptions() ) : CVBF_ConfigOptions ( options ),
            _cachePolicy           ( ),
            _cstype                ( CSTYPE_GEOCENTRIC ),
            _referenceURI          ( "" ),
            _elevationInterpolation( INTERP_BILINEAR ),
            _elevTileSize          ( 8 )
    {
        fromConfig(m_conf);
    }

    virtual ~CVBF_ConfigOptionsMap() { }

	// ͼ��map��������
    CVBF_Optional<std::string>& name() { return m_sName; }
    const CVBF_Optional<std::string>& name() const { return m_sName; }

	// ��ȡ����ϵͳ�����ͣ�Ĭ����CSTYPE_GEOCENTRIC��
    CVBF_Optional<CoordinateSystemType>& coordSysType() { return _cstype; }
    const CVBF_Optional<CoordinateSystemType>& coordSysType() const { return _cstype; }

	// ��ȡmap��һ����ȷ�ı�׼������master profile����ͨ�����Զ�����ģ�����ʱ��Ҫ�ֶ�����
    CVBF_Optional<CVBF_ConfigOptionsProfile>& profile() { return _profileOptions; }
    const CVBF_Optional<CVBF_ConfigOptionsProfile>& profile() const { return _profileOptions; }

  	// ������ͼ�Ļ������á�Ĭ������£���ӵ���ͼ��ͼ�㽫�̳и����ã��������ػ��Զ�������
    CVBF_Optional<CacheOptions>& cache() { return _cacheOptions; }
    const CVBF_Optional<CacheOptions>& cache() const { return _cacheOptions; }

  	// ���ݵ�ÿ��ͼ��Ļ������
    CVBF_Optional<CachePolicy>& cachePolicy() { return _cachePolicy; }
    const CVBF_Optional<CachePolicy>& cachePolicy() const { return _cachePolicy; }

 	// ���ڸ̲߳����Ĳ�ֵ����
    CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void) { return _elevationInterpolation; }
    const CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void) const { return _elevationInterpolation;}

	// �߳���Ƭ�ĳߴ磬����᷵�ظ߳���Ƭ���õ����ߴ磬�������趨һ����Ҫ�ĳߴ�
    CVBF_Optional<unsigned>& elevationTileSize() { return _elevTileSize; }
    const CVBF_Optional<unsigned>& elevationTileSize() const { return _elevTileSize; }

public:
    /**
        * A reference location that drivers can use to load data from relative locations.
        * NOTE: this is a runtime-only property and is NOT serialized in the CVBF_ConfigOptions.
        */
    CVBF_Optional<std::string>& referenceURI() { return _referenceURI; }
    const CVBF_Optional<std::string>& referenceURI() const { return _referenceURI; }
    
public:
    CVBF_Config getConfig() const;

    void mergeConfig( const CVBF_Config& conf ) 
	{ 
		CVBF_ConfigOptions::mergeConfig( conf );
        fromConfig( conf );
    }

private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<std::string>               m_sName;
    CVBF_Optional<CVBF_ConfigOptionsProfile> _profileOptions;
    CVBF_Optional<CacheOptions>              _cacheOptions;
    CVBF_Optional<CachePolicy>               _cachePolicy;
    CVBF_Optional<CoordinateSystemType>      _cstype;
    CVBF_Optional<std::string>               _referenceURI;
    CVBF_Optional<ElevationInterpolation>    _elevationInterpolation;
    CVBF_Optional<unsigned>                  _elevTileSize;
};


#endif // OSGEARTH_MAP_ENGINE_PROPERTIES_H
