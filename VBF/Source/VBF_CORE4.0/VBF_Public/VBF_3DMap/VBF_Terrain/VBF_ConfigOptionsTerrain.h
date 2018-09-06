#ifndef OSGEARTH_TERRAIN_OPTIONS_H
#define OSGEARTH_TERRAIN_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture.h>


// 废弃类。配置地形引擎读地图数据的选项
class OSGEARTH_EXPORT CVBF_LoadingPolicy
{
public:
    enum Mode // 瓦片装载模式
    {
        MODE_SERIAL,   // 串行装载Load tiles one LOD at a tile
        MODE_PARALLEL, // 并行装载/** Load tiles one LOD at a tile, in parallel */

        MODE_SEQUENTIAL,// 使用任务服务线程池加载瓦片，强化有顺序的显示瓦片LODs
        // 使用任务服务线程池加载瓦片，但优先加载最高级别LOD的可见图像(高程数据总是sequential)
        MODE_PREEMPTIVE,

        MODE_STANDARD = MODE_SERIAL // 使用标准的分页数据库机制
    };

public:
    CVBF_LoadingPolicy( const CVBF_Config& conf =CVBF_Config() );
    virtual ~CVBF_LoadingPolicy() { }

public: // Configrable
    virtual CVBF_Config getConfig() const;
    virtual void        fromConfig( const CVBF_Config& conf );

public:

    // 设置/获取瓦片装载模式
    const CVBF_Optional<Mode>& mode() const { return _mode; }
          CVBF_Optional<Mode>& mode() { return _mode; }

    // 每个CPU上用于加载数据的线程数
    const CVBF_Optional<float>& numLoadingThreadsPerCore() const { return _numLoadingThreadsPerCore; }
          CVBF_Optional<float>& numLoadingThreadsPerCore() { return _numLoadingThreadsPerCore; }

    // 用于加载数据的线程数，STANDARD模式时，该值影响分页数据库的线程数；
    //                     SEQUENTIAL或PREEMPTIVE模式时，该值设置为任务线程池的线程数
    const CVBF_Optional<int>& numLoadingThreads() const { return _numLoadingThreads; }
          CVBF_Optional<int>& numLoadingThreads() { return _numLoadingThreads; }

    // 用于产生地形瓦片的后台线程数，仅用于SEQUENTIAL和PREEMPTIVE模式
    const CVBF_Optional<int>& numCompileThreads() const { return _numCompileThreads; }
          CVBF_Optional<int>& numCompileThreads() { return _numCompileThreads; }

    // 每个CPU上用于产生地形瓦片的后台线程数，仅用于SEQUENTIAL和PREEMPTIVE模式
    const CVBF_Optional<float>& numCompileThreadsPerCore() const { return _numCompileThreadsPerCore; }
          CVBF_Optional<float>& numCompileThreadsPerCore() { return _numCompileThreadsPerCore; }

protected:
    CVBF_Optional<Mode>		_mode;
    CVBF_Optional<int>		_numLoadingThreads;
    CVBF_Optional<float>	_numLoadingThreadsPerCore;
    CVBF_Optional<int>		_numCompileThreads;
    CVBF_Optional<float>	_numCompileThreadsPerCore;
};

extern OSGEARTH_EXPORT int VBF_ComputeLoadingThreads(const CVBF_LoadingPolicy& policy);


// 地形引擎驱动器配置的基类
class OSGEARTH_EXPORT CVBF_OptionsTerrain : public CVBF_OptionsDriver
{
public:
    CVBF_OptionsTerrain( const CVBF_Options& options =CVBF_Options() );
    virtual ~CVBF_OptionsTerrain() { }
       
	// 设置/获取高度场的比例因子，默认是1.0
    const CVBF_Optional<float>& verticalScale() const { return _verticalScale; }
          CVBF_Optional<float>& verticalScale() { return _verticalScale; }

	// 设置/获取高度场的样本比，默认是1.0。地形引擎使用该值对高度场进行采样
    const CVBF_Optional<float>& heightFieldSampleRatio() const { return _heightFieldSampleRatio; }
          CVBF_Optional<float>& heightFieldSampleRatio() { return _heightFieldSampleRatio; }

	// LOD切换有一个最大最小范围，比最小范围小则分裂（LOD增加），比最大范围大则合并（LOD减小）
	// 最小值设定为：瓦片半径×因子（minTileRangeFactor），默认值为6.0，表示当视点与瓦片的距离小于瓦片半径×6.0时分裂瓦片
    const CVBF_Optional<float>& minTileRangeFactor() const { return _minTileRangeFactor; }
          CVBF_Optional<float>& minTileRangeFactor() { return _minTileRangeFactor; }

	// 废弃的，加载瓦片的策略
    const CVBF_Optional<CVBF_LoadingPolicy>& loadingPolicy() const { return _loadingPolicy; }
          CVBF_Optional<CVBF_LoadingPolicy>& loadingPolicy() { return _loadingPolicy; }

	// 影像图层颜色衰减（fading attenuation）距离
    const CVBF_Optional<float>& attentuationDistance() const { return _attenuationDistance; }
          CVBF_Optional<float>& attenuationDistance() { return _attenuationDistance; }

	// 图像淡入的过渡时间，单位秒
	const CVBF_Optional<float>& lodTransitionTime() const { return _lodTransitionTimeSeconds; }
		  CVBF_Optional<float>& lodTransitionTime() { return _lodTransitionTimeSeconds; }

	// 是否对地形瓦片启用聚簇裁剪（cluster culling），默认为true
    const CVBF_Optional<bool>& clusterCulling() const { return _clusterCulling; }
		  CVBF_Optional<bool>& clusterCulling() { return _clusterCulling; }

	// 废弃，去掉或移到Quadtree地形引擎。运行时影像图层合成技术
    enum CompositingTechnique
    {
        COMPOSITING_AUTO,
        COMPOSITING_TEXTURE_ARRAY,
        COMPOSITING_MULTITEXTURE_GPU,
        COMPOSITING_MULTITEXTURE_FFP,
        COMPOSITING_MULTIPASS,
        COMPOSITING_USER
    };

	// 废弃，去掉或移到Quadtree地形引擎。纹理合成技术
    const CVBF_Optional<CompositingTechnique>& compositingTechnique() const { return _compositingTech; }
		  CVBF_Optional<CompositingTechnique>& compositingTechnique() { return _compositingTech; }

	// 瓦片分裂的最大LOD，如果不设置，则分裂到没有数据为止（默认的行为），如果设置了该值，即使有高分辨率发数据也会停止分裂
    const CVBF_Optional<unsigned>& maxLOD() const { return _maxLOD; }
          CVBF_Optional<unsigned>& maxLOD() { return _maxLOD; }

    /**
        * The minimum level of detail to which the terrain should subdivide (no matter what).
        * If you leave this unset, the terrain will subdivide until the map layers
        * stop providing data (default behavior). If you set a value, the terrain will subdivide
        * to the specified LOD no matter what (and may continue farther if higher-resolution
        * data is available).
        */

    const CVBF_Optional<unsigned>& minLOD() const { return _minLOD; }
		  CVBF_Optional<unsigned>& minLOD() { return _minLOD; }

	// 可显示的最小的LOD，默认为0。设置该值，则地形瓦片从一个更高的LOD开始，该值不要设置太大，否则会有内存异常问题
    const CVBF_Optional<unsigned>& firstLOD() const { return _firstLOD; }
		  CVBF_Optional<unsigned>& firstLOD() { return _firstLOD; }

	// 地图节点是否启用光照
    const CVBF_Optional<bool>& enableLighting() const { return _enableLighting; }  
		  CVBF_Optional<bool>& enableLighting() { return _enableLighting; }    

	// 是否启用MipMap纹理
    const CVBF_Optional<bool>& enableMipmapping() const { return _enableMipmapping; }
		  CVBF_Optional<bool>& enableMipmapping() { return _enableMipmapping; }

	// 缩小时，纹理过滤模式
    const CVBF_Optional<osg::Texture::FilterMode>& minFilter() const { return _minFilter;}
		  CVBF_Optional<osg::Texture::FilterMode>& minFilter() { return _minFilter;}

	// 放大时，纹理过滤模式
    const CVBF_Optional<osg::Texture::FilterMode>& magFilter() const { return _magFilter;}
		  CVBF_Optional<osg::Texture::FilterMode>& magFilter() { return _magFilter;}
            
	// 是否启用混合
    const CVBF_Optional<bool>& enableBlending() const { return _enableBlending; }
          CVBF_Optional<bool>& enableBlending() { return _enableBlending; }

    /**
        * Whether to enable the "fast path" for spherical Mercator image layers
        * Default = true. If enabled, Mercator image tiles will be rendered on a
        * geocentric map with no reprojection. The trade-off is higher texture
        * memory usage and NPOT texture usage.
        */
    const CVBF_Optional<bool>& enableMercatorFastPath() const { return _mercatorFastPath; }
		  CVBF_Optional<bool>& enableMercatorFastPath() { return _mercatorFastPath; }

    /**
        * Traversal mask to use for primary geometry -- geometry that comprises the visible
        * geometry and should participate in intersection, shadowing, etc.
        */

    const CVBF_Optional<unsigned>& primaryTraversalMask() const { return _primaryTraversalMask; }
		  CVBF_Optional<unsigned>& primaryTraversalMask() { return _primaryTraversalMask; }
    /**
        * Traversal mask to use for secondary geometry -- geometry that exists for
        * secondary purpose (e.g. terrain skirts) that should not participate in 
        * intersection, shadowing, etc.
        */
    const CVBF_Optional<unsigned>& secondaryTraversalMask() const { return _secondaryTraversalMask; }
		  CVBF_Optional<unsigned>& secondaryTraversalMask() { return _secondaryTraversalMask; }
   
public:
    virtual CVBF_Config getConfig() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf ) 
	{
        CVBF_OptionsDriver::mergeConfig( conf );
        fromConfig( conf );
    }

private:
    void fromConfig( const CVBF_Config& conf );
                    
    CVBF_Optional<float> _verticalScale;
    CVBF_Optional<float> _heightFieldSampleRatio;
    CVBF_Optional<float> _minTileRangeFactor;        
    CVBF_Optional<bool> _combineLayers;
    CVBF_Optional<CVBF_LoadingPolicy> _loadingPolicy;
    CVBF_Optional<CompositingTechnique> _compositingTech;
    CVBF_Optional<unsigned> _minLOD;
    CVBF_Optional<unsigned> _maxLOD;
    CVBF_Optional<unsigned> _firstLOD;
    CVBF_Optional<bool> _enableLighting;
    CVBF_Optional<float> _attenuationDistance;
    CVBF_Optional<bool> _lodBlending;
    CVBF_Optional<float> _lodTransitionTimeSeconds;
    CVBF_Optional<bool>  _enableMipmapping;
    CVBF_Optional<bool> _clusterCulling;
    CVBF_Optional<bool> _enableBlending;
    CVBF_Optional<bool> _mercatorFastPath;
    CVBF_Optional<osg::Texture::FilterMode> _magFilter;
    CVBF_Optional<osg::Texture::FilterMode> _minFilter;
    CVBF_Optional<osgEarth::ElevationInterpolation> _elevationInterpolation;
    CVBF_Optional<unsigned> _primaryTraversalMask;
    CVBF_Optional<unsigned> _secondaryTraversalMask;
};


#endif // OSGEARTH_MAP_ENGINE_PROPERTIES_H
