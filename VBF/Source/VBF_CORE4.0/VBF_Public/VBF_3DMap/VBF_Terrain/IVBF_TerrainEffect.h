#ifndef OSGEARTH_TERRAIN_EFFECT_H
#define OSGEARTH_TERRAIN_EFFECT_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>

class CVBFO_SGNodeTerrainEngine;

namespace osgEarth
{  
    // 地形效果，给TerrainEngineNode使用的效果，可以调用TerrainEngineNode::addEffect()给地形引擎添加效果
    // 一个地形效果可以做任何事情，通常是使用某种方法更改状态集（如，自定义着色器）
    class IVBF_TerrainEffect : public CVBF_Referenced
    {
    public:
        // 当安装该效果时被地形引擎调用
        virtual void onInstall(CVBFO_SGNodeTerrainEngine* engine) { }

        // 当卸载该效果时被地形引擎调用
        virtual void onUninstall(CVBFO_SGNodeTerrainEngine* engine) { }

    public: // 用于串行化
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }

    protected:
        IVBF_TerrainEffect() { }
        virtual ~IVBF_TerrainEffect() { }
    };
}
#endif
