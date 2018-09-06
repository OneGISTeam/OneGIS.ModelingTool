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
class OSGEARTH_EXPORT CVBF_OptionsMap : public CVBF_Options // no export (header-only)
{
public:
    enum CoordinateSystemType // ����ϵͳ����
    {
        CSTYPE_GEOCENTRIC,       // ��������ϵ
        CSTYPE_GEOCENTRIC_CUBE,	 // ��������������ϵ
        CSTYPE_PROJECTED         // ͶӰ����ϵ
    };		

public:
    CVBF_OptionsMap( const CVBF_Options& options =CVBF_Options() );
    virtual ~CVBF_OptionsMap();

	// ͼ��map��������
    CVBF_Optional<std::string>& name();
    const CVBF_Optional<std::string>& name() const;

	// ��ȡ����ϵͳ�����ͣ�Ĭ����CSTYPE_GEOCENTRIC��
    CVBF_Optional<CoordinateSystemType>& coordSysType();
    const CVBF_Optional<CoordinateSystemType>& coordSysType() const;

	// ��ȡmap��һ����ȷ�ı�׼������master profile����ͨ�����Զ�����ģ�����ʱ��Ҫ�ֶ�����
    CVBF_Optional<CVBF_OptionsProfile>& profile();
    const CVBF_Optional<CVBF_OptionsProfile>& profile() const;

  	// ������ͼ�Ļ������á�Ĭ������£���ӵ���ͼ��ͼ�㽫�̳и����ã��������ػ��Զ�������
    CVBF_Optional<CacheOptions>& cache();
    const CVBF_Optional<CacheOptions>& cache() const;

  	// ���ݵ�ÿ��ͼ��Ļ������
    CVBF_Optional<CachePolicy>& cachePolicy();
    const CVBF_Optional<CachePolicy>& cachePolicy() const;

 	// ���ڸ̲߳����Ĳ�ֵ����
    CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void);
    const CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void) const;

	// �߳���Ƭ�ĳߴ磬����᷵�ظ߳���Ƭ���õ����ߴ磬�������趨һ����Ҫ�ĳߴ�
    CVBF_Optional<unsigned>& elevationTileSize();
    const CVBF_Optional<unsigned>& elevationTileSize() const;

public:

	// ������������ȡ���ݣ����λ�õ����ݣ�ʱ���õĲο�λ�á������Խ�Ϊ����ʱ�ģ����ܴ��л�
    CVBF_Optional<std::string>& referenceURI();
    const CVBF_Optional<std::string>& referenceURI() const;
    
public:
    CVBF_Config getConfig() const;
    void mergeConfig( const CVBF_Config& conf );
private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<std::string>               m_sName;
    CVBF_Optional<CVBF_OptionsProfile>       _profileOptions;
    CVBF_Optional<CacheOptions>              _cacheOptions;
    CVBF_Optional<CachePolicy>               _cachePolicy;
    CVBF_Optional<CoordinateSystemType>      _cstype;
    CVBF_Optional<std::string>               _referenceURI;
    CVBF_Optional<ElevationInterpolation>    _elevationInterpolation;
    CVBF_Optional<unsigned>                  _elevTileSize;
};


#endif // OSGEARTH_MAP_ENGINE_PROPERTIES_H
