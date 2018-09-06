#ifndef OSGEARTH_TERRAIN_OPTIONS_H
#define OSGEARTH_TERRAIN_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture.h>


// �����ࡣ���õ����������ͼ���ݵ�ѡ��
class OSGEARTH_EXPORT CVBF_LoadingPolicy
{
public:
    enum Mode // ��Ƭװ��ģʽ
    {
        MODE_SERIAL,   // ����װ��Load tiles one LOD at a tile
        MODE_PARALLEL, // ����װ��/** Load tiles one LOD at a tile, in parallel */

        MODE_SEQUENTIAL,// ʹ����������̳߳ؼ�����Ƭ��ǿ����˳�����ʾ��ƬLODs
        // ʹ����������̳߳ؼ�����Ƭ�������ȼ�����߼���LOD�Ŀɼ�ͼ��(�߳���������sequential)
        MODE_PREEMPTIVE,

        MODE_STANDARD = MODE_SERIAL // ʹ�ñ�׼�ķ�ҳ���ݿ����
    };

public:
    CVBF_LoadingPolicy( const CVBF_Config& conf =CVBF_Config() );
    virtual ~CVBF_LoadingPolicy() { }

public: // Configrable
    virtual CVBF_Config getConfig() const;
    virtual void        fromConfig( const CVBF_Config& conf );

public:

    // ����/��ȡ��Ƭװ��ģʽ
    const CVBF_Optional<Mode>& mode() const { return _mode; }
          CVBF_Optional<Mode>& mode() { return _mode; }

    // ÿ��CPU�����ڼ������ݵ��߳���
    const CVBF_Optional<float>& numLoadingThreadsPerCore() const { return _numLoadingThreadsPerCore; }
          CVBF_Optional<float>& numLoadingThreadsPerCore() { return _numLoadingThreadsPerCore; }

    // ���ڼ������ݵ��߳�����STANDARDģʽʱ����ֵӰ���ҳ���ݿ���߳�����
    //                     SEQUENTIAL��PREEMPTIVEģʽʱ����ֵ����Ϊ�����̳߳ص��߳���
    const CVBF_Optional<int>& numLoadingThreads() const { return _numLoadingThreads; }
          CVBF_Optional<int>& numLoadingThreads() { return _numLoadingThreads; }

    // ���ڲ���������Ƭ�ĺ�̨�߳�����������SEQUENTIAL��PREEMPTIVEģʽ
    const CVBF_Optional<int>& numCompileThreads() const { return _numCompileThreads; }
          CVBF_Optional<int>& numCompileThreads() { return _numCompileThreads; }

    // ÿ��CPU�����ڲ���������Ƭ�ĺ�̨�߳�����������SEQUENTIAL��PREEMPTIVEģʽ
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


// �����������������õĻ���
class OSGEARTH_EXPORT CVBF_OptionsTerrain : public CVBF_OptionsDriver
{
public:
    CVBF_OptionsTerrain( const CVBF_Options& options =CVBF_Options() );
    virtual ~CVBF_OptionsTerrain() { }
       
	// ����/��ȡ�߶ȳ��ı������ӣ�Ĭ����1.0
    const CVBF_Optional<float>& verticalScale() const { return _verticalScale; }
          CVBF_Optional<float>& verticalScale() { return _verticalScale; }

	// ����/��ȡ�߶ȳ��������ȣ�Ĭ����1.0����������ʹ�ø�ֵ�Ը߶ȳ����в���
    const CVBF_Optional<float>& heightFieldSampleRatio() const { return _heightFieldSampleRatio; }
          CVBF_Optional<float>& heightFieldSampleRatio() { return _heightFieldSampleRatio; }

	// LOD�л���һ�������С��Χ������С��ΧС����ѣ�LOD���ӣ��������Χ����ϲ���LOD��С��
	// ��Сֵ�趨Ϊ����Ƭ�뾶�����ӣ�minTileRangeFactor����Ĭ��ֵΪ6.0����ʾ���ӵ�����Ƭ�ľ���С����Ƭ�뾶��6.0ʱ������Ƭ
    const CVBF_Optional<float>& minTileRangeFactor() const { return _minTileRangeFactor; }
          CVBF_Optional<float>& minTileRangeFactor() { return _minTileRangeFactor; }

	// �����ģ�������Ƭ�Ĳ���
    const CVBF_Optional<CVBF_LoadingPolicy>& loadingPolicy() const { return _loadingPolicy; }
          CVBF_Optional<CVBF_LoadingPolicy>& loadingPolicy() { return _loadingPolicy; }

	// Ӱ��ͼ����ɫ˥����fading attenuation������
    const CVBF_Optional<float>& attentuationDistance() const { return _attenuationDistance; }
          CVBF_Optional<float>& attenuationDistance() { return _attenuationDistance; }

	// ͼ����Ĺ���ʱ�䣬��λ��
	const CVBF_Optional<float>& lodTransitionTime() const { return _lodTransitionTimeSeconds; }
		  CVBF_Optional<float>& lodTransitionTime() { return _lodTransitionTimeSeconds; }

	// �Ƿ�Ե�����Ƭ���þ۴زü���cluster culling����Ĭ��Ϊtrue
    const CVBF_Optional<bool>& clusterCulling() const { return _clusterCulling; }
		  CVBF_Optional<bool>& clusterCulling() { return _clusterCulling; }

	// ������ȥ�����Ƶ�Quadtree�������档����ʱӰ��ͼ��ϳɼ���
    enum CompositingTechnique
    {
        COMPOSITING_AUTO,
        COMPOSITING_TEXTURE_ARRAY,
        COMPOSITING_MULTITEXTURE_GPU,
        COMPOSITING_MULTITEXTURE_FFP,
        COMPOSITING_MULTIPASS,
        COMPOSITING_USER
    };

	// ������ȥ�����Ƶ�Quadtree�������档����ϳɼ���
    const CVBF_Optional<CompositingTechnique>& compositingTechnique() const { return _compositingTech; }
		  CVBF_Optional<CompositingTechnique>& compositingTechnique() { return _compositingTech; }

	// ��Ƭ���ѵ����LOD����������ã�����ѵ�û������Ϊֹ��Ĭ�ϵ���Ϊ������������˸�ֵ����ʹ�и߷ֱ��ʷ�����Ҳ��ֹͣ����
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

	// ����ʾ����С��LOD��Ĭ��Ϊ0�����ø�ֵ���������Ƭ��һ�����ߵ�LOD��ʼ����ֵ��Ҫ����̫�󣬷�������ڴ��쳣����
    const CVBF_Optional<unsigned>& firstLOD() const { return _firstLOD; }
		  CVBF_Optional<unsigned>& firstLOD() { return _firstLOD; }

	// ��ͼ�ڵ��Ƿ����ù���
    const CVBF_Optional<bool>& enableLighting() const { return _enableLighting; }  
		  CVBF_Optional<bool>& enableLighting() { return _enableLighting; }    

	// �Ƿ�����MipMap����
    const CVBF_Optional<bool>& enableMipmapping() const { return _enableMipmapping; }
		  CVBF_Optional<bool>& enableMipmapping() { return _enableMipmapping; }

	// ��Сʱ���������ģʽ
    const CVBF_Optional<osg::Texture::FilterMode>& minFilter() const { return _minFilter;}
		  CVBF_Optional<osg::Texture::FilterMode>& minFilter() { return _minFilter;}

	// �Ŵ�ʱ���������ģʽ
    const CVBF_Optional<osg::Texture::FilterMode>& magFilter() const { return _magFilter;}
		  CVBF_Optional<osg::Texture::FilterMode>& magFilter() { return _magFilter;}
            
	// �Ƿ����û��
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
