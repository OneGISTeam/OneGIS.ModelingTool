#ifndef OSGSHADOW_SHADOWVOLUME
#define OSGSHADOW_SHADOWVOLUME 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLight.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>
#include <VBF_Engine/VBF_Shadow/OccluderGeometry>

namespace osgShadow {

// 体积阴影技术，实现基于模板缓存的体积阴影 
class OSGSHADOW_EXPORT ShadowVolume : public ShadowTechnique
{
    public :
        ShadowVolume();

        ShadowVolume(const ShadowVolume& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
            
        META_Object(osgShadow, ShadowVolume);
        

        void setDrawMode(osgShadow::ShadowVolumeGeometry::DrawMode drawMode);
        osgShadow::ShadowVolumeGeometry::DrawMode getDrawMode() const { return _drawMode; }

        void setDynamicShadowVolumes(bool dynamicShadowVolumes);
        bool getDynamicShadowVolumes() const { return _dynamicShadowVolumes; }

        /** initialize the ShadowedScene and local cached data structures.*/
        virtual void init();
        
        /** run the update traversal of the ShadowedScene and update any loca chached data structures.*/
        virtual void update(osg::NodeVisitor& nv);
        
        /** run the cull traversal of the ShadowedScene and set up the rendering for this ShadowTechnique.*/
        virtual void cull(osgUtil::CullVisitor& cv);
        
        /** Clean scene graph from any shadow technique specific nodes, state and drawables.*/
        virtual void cleanSceneGraph();
        

    protected :

        virtual ~ShadowVolume();
        
        osgShadow::ShadowVolumeGeometry::DrawMode       _drawMode;
        bool                                            _dynamicShadowVolumes;

        ref_ptr<osgShadow::OccluderGeometry> _occluder;
        
        OpenThreads::Mutex                              _shadowVolumeMutex;
        ref_ptr<osgShadow::ShadowVolumeGeometry>   _shadowVolume;
        
        osg::Vec4                   _lightpos;
        
        ref_ptr<osg::Light>    _ambientLight;
        ref_ptr<osg::Light>    _diffuseLight;

        ref_ptr<osg::StateSet> _ss1;
        ref_ptr<osg::StateSet> _mainShadowStateSet;
        ref_ptr<osg::StateSet> _shadowVolumeStateSet;
        ref_ptr<osg::StateSet> _shadowedSceneStateSet;


};

}

#endif
