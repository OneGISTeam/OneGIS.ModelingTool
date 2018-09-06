#ifndef OSGEARTH_MAP_OPTIONS_H
#define OSGEARTH_MAP_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>


// map 的配置项
class OSGEARTH_EXPORT CVBF_OptionsMap : public CVBF_Options // no export (header-only)
{
public:
    enum CoordinateSystemType // 坐标系统类型
    {
        CSTYPE_GEOCENTRIC,       // 地心坐标系
        CSTYPE_GEOCENTRIC_CUBE,	 // 地心立方体坐标系
        CSTYPE_PROJECTED         // 投影坐标系
    };		

public:
    CVBF_OptionsMap( const CVBF_Options& options =CVBF_Options() );
    virtual ~CVBF_OptionsMap();

	// 图（map）的名字
    CVBF_Optional<std::string>& name();
    const CVBF_Optional<std::string>& name() const;

	// 获取坐标系统的类型（默认是CSTYPE_GEOCENTRIC）
    CVBF_Optional<CoordinateSystemType>& coordSysType();
    const CVBF_Optional<CoordinateSystemType>& coordSysType() const;

	// 获取map的一个明确的标准轮廓（master profile），通常是自动计算的，但有时需要手动设置
    CVBF_Optional<CVBF_OptionsProfile>& profile();
    const CVBF_Optional<CVBF_OptionsProfile>& profile() const;

  	// 整个地图的缓存设置。默认情况下，添加到地图的图层将继承该设置，除非重载或自定义设置
    CVBF_Optional<CacheOptions>& cache();
    const CVBF_Optional<CacheOptions>& cache() const;

  	// 传递到每个图层的缓存策略
    CVBF_Optional<CachePolicy>& cachePolicy();
    const CVBF_Optional<CachePolicy>& cachePolicy() const;

 	// 用于高程采样的差值方法
    CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void);
    const CVBF_Optional<ElevationInterpolation>& elevationInterpolation(void) const;

	// 高程瓦片的尺寸，引擎会返回高程瓦片可用的最大尺寸，本函数设定一个想要的尺寸
    CVBF_Optional<unsigned>& elevationTileSize();
    const CVBF_Optional<unsigned>& elevationTileSize() const;

public:

	// 数据驱动器读取数据（相对位置的数据）时所用的参考位置。该属性仅为运行时的，不能串行化
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
