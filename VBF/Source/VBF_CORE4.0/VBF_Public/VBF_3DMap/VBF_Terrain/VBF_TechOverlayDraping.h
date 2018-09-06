#ifndef OSGEARTH_OVERLAY_DRAPING_TECHNIQUE
#define OSGEARTH_OVERLAY_DRAPING_TECHNIQUE

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDecoratorTerrainOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

class CVBFO_SGNodeTerrainEngine;



// 覆盖技术，贴地表。把一个覆盖（叠加）场景投影到被覆盖的模型（如，贴地表效果）
// 地形覆盖节点节点自动安装在地图节点下，用于显示“贴地表”属性为true的矢量数据

class OSGEARTH_EXPORT CVBF_TechOverlayDraping : public CVBF_TechOverlay
{
public:
    CVBF_TechOverlayDraping();

	// 明确指定覆盖纹理占用的纹理单元，当把该对象加入CVBFO_SGNodeMap时，会自动分配一个空闲的纹理单元，所以通常情况下不需调用该函数
    void setTextureUnit( int unit );
    int getTextureUnit() const { return *_textureUnit; }

	// 覆盖纹理的大小，默认为4096或显卡的最大支持尺寸
    void setTextureSize( int texSize );
    int getTextureSize() const { return *_textureSize; }

	// 对投影后的纹理是否启用MipMap，启用可以提高视觉效果，但占用更多的显存，并影响性能（覆盖物为动态时）。在某些GPU上性能显著降低（如，Intel GMA）
    void setMipMapping( bool value );
    bool getMipMapping() const { return _mipmapping; }

	// 对RTT相机是否启用混合（blending），默认为true。当多边形非常大时，受分格化影响可能会关掉混合
    void setOverlayBlending( bool value );
    bool getOverlayBlending() const { return _rttBlending; }

	// 设置/获取是否把 RTT相机关联到模板缓存（stencil buffer），默认为true，一些老显卡支持的不好
    void setAttachStencil( bool value );
    bool getAttachStencil() const;


public: // CVBF_TechOverlay

    virtual bool hasData( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params) const;

    void reestablish( CVBFO_SGNodeTerrainEngine* engine );

    void preCullTerrain( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void cullOverlayGroup( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void onInstall( CVBFO_SGNodeTerrainEngine* engine );
    void onUninstall( CVBFO_SGNodeTerrainEngine* engine );


protected:
    virtual ~CVBF_TechOverlayDraping() { }

private:
    CVBF_Optional<int>                 m_opExplicitTextureUnit;
    CVBF_Optional<int>                 _textureUnit;
    CVBF_Optional<int>                 _textureSize;
    bool                          _useShaders;
    bool                          _mipmapping;
    bool                          _rttBlending;
    bool                          _attachStencil;

    struct TechData : public ::CVBF_Referenced
    {
        ref_ptr<osg::Uniform>    _texGenUniform;
        ref_ptr<osg::TexGen>     _texGen;
    };

private:
        
    void setUpCamera(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params);
};



#endif //OSGEARTH_OVERLAY_DRAPING_TECHNIQUE
