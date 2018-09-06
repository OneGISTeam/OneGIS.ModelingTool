/**************************************************************************************************
* @file NormalMapEffect.h
* @note 地形的NormalMap法线贴图的效果实现
* @author c00005
* @data 2015-9-29
**************************************************************************************************/
#ifndef FE_NORMAL_MAP_EFFECT_H
#define FE_NORMAL_MAP_EFFECT_H

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/IVBF_TerrainEffect.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>

//#include "export.h"

namespace osgEarth { namespace Util
{
    class OSGEARTHUTIL_EXPORT CNormalMapEffect : public IVBF_TerrainEffect
    {
    public:
        CNormalMapEffect();

        CNormalMapEffect(const CVBF_Config& conf, CVBF_Map* map);

        virtual ~CNormalMapEffect();
    public:
        void setNormalMapLayer(CVBF_LayerTerrainImage* layer);

        CVBF_LayerTerrainImage* getNormalMapLayer();

        void setStartLOD(unsigned lod);

        unsigned int getStartLOD() const;

    public:

        void onInstall(CVBFO_SGNodeTerrainEngine* engine);

        void onUninstall(CVBFO_SGNodeTerrainEngine* engine);

    public:
        void mergeConfig(const CVBF_Config& conf);

        virtual CVBF_Config getConfig() const;

    protected:

        void init();

        CVBF_Optional<unsigned>    _startLOD;

        CVBF_Optional<std::string> _layerName;

        observer_ptr<CVBF_LayerTerrainImage> _layer;

        ref_ptr<osg::Uniform>    _samplerUniform;

        ref_ptr<osg::Uniform>    _startLODUniform;
    };

} 
}

#endif // FE_NORMAL_MAP_EFFECT_H
