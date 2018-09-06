#ifndef OSGEARTH_OVERLAY_CLAMPING_TECHNIQUE
#define OSGEARTH_OVERLAY_CLAMPING_TECHNIQUE

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDecoratorTerrainOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

#define OSGEARTH_CLAMPING_BIN "osgEarth::ClampingBin"

class CVBFO_SGNodeTerrainEngine;


/**
    * Clamps geometry to the terrain using the GPU.
    *
    * This overlay technique installs a shader that samples the depth
    * of the underlying terrain and then adjusts the vertex position to
    * the height of the terrain. It then applies a depth offset in order
    * to mitigate Z-fighting.
    *
    * Approach
    *
    * This technique works by first setting up a nadir-view RTT camera that
    * captures the depth component of the terrain within the view frustum of
    * the main camera. Then the GPU uses this "depth texture" to move each
    * vertex so it coindices with the terrain.
    *
    * Limitations
    *
    * Since this is an orthographic view, the effective resolution of depth
    * data close to the camera may not be quite sufficient, especially when
    * the camera is pitched up looking out over the horizon. As a reuslt, you
    * may see the verts "jitter" slightly in the Z direciton as you camera moves.
    *
    * Performance takes a hit since we need to RTT the terrain in a pre-render
    * pass.
    */
class OSGEARTH_EXPORT CVBF_TechOverlayClamping : public CVBF_TechOverlay
{
public:
    typedef osg::IVBF_SGNodeGroup* (*TechniqueProvider)(class CVBFO_SGNodeMap*);
    static TechniqueProvider Provider;

public:
    CVBF_TechOverlayClamping();

    /**
        * The size (resolution in both directions) of the depth map texture. By
        * default, this defaults to 4096 or your hardware's maximum supported
        * texture size, whichever is less.
        */
    void setTextureSize( int texSize );
    int getTextureSize() const { return *_textureSize; }


public: // CVBF_TechOverlay

    bool hasData( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params) const;

    void reestablish( CVBFO_SGNodeTerrainEngine* engine );

    void preCullTerrain( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void cullOverlayGroup( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void onInstall( CVBFO_SGNodeTerrainEngine* engine );

    void onUninstall( CVBFO_SGNodeTerrainEngine* engine );


protected:
    virtual ~CVBF_TechOverlayClamping() { }

private:
    int							_textureUnit;
    CVBF_Optional<int>			_textureSize;
    CVBFO_SGNodeTerrainEngine*	_engine;

private:
    void setUpCamera(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params);
};


#endif //OSGEARTH_OVERLAY_CLAMPING_TECHNIQUE
