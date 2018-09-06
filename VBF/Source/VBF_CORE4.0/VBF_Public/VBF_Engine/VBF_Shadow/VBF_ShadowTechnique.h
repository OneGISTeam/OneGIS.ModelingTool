#ifndef OSGSHADOW_SHADOWEDTECHNIQUE
#define OSGSHADOW_SHADOWEDTECHNIQUE 1

#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_SGUtil/CullVisitor>

#include <VBF_Engine/VBF_Shadow/Export>

namespace osgShadow {

class ShadowedScene;

// ShadowTechnique  ShadowTexture	
//                  ShadowVolume
//					ViewDependentShadowTechnique	DebugShadowMap	StandardShadowMap	MinimalShadowMap	MinimalCullBoundsShadowMap
//																											MinimalDrawBoundsShadowMap
//					ParallelSplitShadowMap
//                  ShadowMap						SoftShadowMap	

// ʵ�ָ�����Ӱ�Ļ��࣬������3�����࣬�ֱ�ΪShadowMap��ShadowTexture��ShadowVolume
class OSGSHADOW_EXPORT ShadowTechnique : public osg::CVBF_Object
{
    public :
        ShadowTechnique();
        ShadowTechnique(const ShadowTechnique& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
            
        META_Object(osgShadow, ShadowTechnique);

        ShadowedScene* getShadowedScene() { return _shadowedScene; }
		const ShadowedScene* getShadowedScene() const { return _shadowedScene; }
        
        /** initialize the ShadowedScene and local cached data structures.*/
        virtual void init();
        
        /** run the update traversal of the ShadowedScene and update any local cached data structures.*/
        virtual void update(osg::NodeVisitor& nv);
        
        /** run the cull traversal of the ShadowedScene and set up the rendering for this ShadowTechnique.*/
        virtual void cull(osgUtil::CullVisitor& cv);
        
        // �������ͼ���κ�ʹ������Ӱ�����Ľڵ㡢״̬�Ϳɻ��ƶ���
        virtual void cleanSceneGraph();

		// ��������
        virtual void traverse(osg::NodeVisitor& nv);
        
		// Dirty�Ա㻺��������󱻸���
        virtual void dirty() { m_bDirty = true; }

    protected :

        class OSGSHADOW_EXPORT CameraCullCallback : public osg::NodeCallback
        {
            public:

                CameraCullCallback(ShadowTechnique* st);

                virtual void operator()(osg::IVBF_SGNode*, osg::NodeVisitor* nv);

            protected:

                ShadowTechnique* _shadowTechnique;
        };

        osg::Vec3 computeOrthogonalVector(const osg::Vec3& direction) const;

        virtual ~ShadowTechnique();
        
        friend class ShadowedScene;
        
        ShadowedScene*  _shadowedScene;
        bool            m_bDirty;
};

}

#endif
