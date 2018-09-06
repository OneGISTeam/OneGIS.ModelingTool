/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2011 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

// ∂≈”®Ã·»°◊‘osg3.3.1

#ifndef OSGSHADOW_VIEWDEPENDENTSHADOWMAP
#define OSGSHADOW_VIEWDEPENDENTSHADOWMAP 1


#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLightSource.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrPolygonOffset.h>
#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>


namespace osgShadow {

/** ViewDependentShadowMap provides an base implementation of view dependent shadow mapping techniques.*/
class OSGSHADOW_EXPORT ViewDependentShadowMap : public ShadowTechnique
{
    public :
        ViewDependentShadowMap();

        ViewDependentShadowMap(const ViewDependentShadowMap& vdsm, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgShadow, ViewDependentShadowMap);

        /** initialize the ShadowedScene and local cached data structures.*/
        virtual void init();

        /** run the update traversal of the ShadowedScene and update any loca chached data structures.*/
        virtual void update(osg::NodeVisitor& nv);

        /** run the cull traversal of the ShadowedScene and set up the rendering for this ShadowTechnique.*/
        virtual void cull(osgUtil::CullVisitor& cv);

        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases any associated OpenGL objects for
           * the specified graphics context. Otherwise, releases OpenGL objects
           * for all graphics contexts. */
        virtual void releaseGLObjects(osg::State* = 0) const;

        /** Clean scene graph from any shadow technique specific nodes, state and drawables.*/
        virtual void cleanSceneGraph();


        struct OSGSHADOW_EXPORT Frustum
        {
            Frustum(osgUtil::CullVisitor* cv, double minZNear, double maxZFar);

            osg::Matrixd projectionMatrix;
            osg::Matrixd modelViewMatrix;

            typedef std::vector<osg::Vec3d> Vertices;
            Vertices corners;

            typedef std::vector<unsigned int> Indices;
            typedef std::vector<Indices> Faces;
            Faces faces;

            typedef std::vector<Indices> Edges;
            Edges edges;

            osg::Vec3d eye;
            osg::Vec3d centerNearPlane;
            osg::Vec3d centerFarPlane;
            osg::Vec3d center;
            osg::Vec3d frustumCenterLine;
        };

        // forward declare
        class ViewDependentData;

        struct OSGSHADOW_EXPORT LightData : public CVBF_Referenced
        {
            LightData(ViewDependentData* vdd);

            virtual void setLightData(osg::RefMatrix* lm, const osg::Light* l, const osg::Matrixd& modelViewMatrix);

            ViewDependentData*              _viewDependentData;

            ref_ptr<osg::RefMatrix>        lightMatrix;
            ref_ptr<const osg::Light>      light;

            osg::Vec4d                      lightPos;
            osg::Vec3d                      lightPos3;
            osg::Vec3d                      lightDir;
            bool                            directionalLight;

            typedef std::vector<unsigned int> ActiveTextureUnits;
            ActiveTextureUnits                   textureUnits;
        };

        typedef std::list< ref_ptr<LightData> > LightDataList;

        struct OSGSHADOW_EXPORT ShadowData : public CVBF_Referenced
        {
            ShadowData(ViewDependentData* vdd);

            virtual void releaseGLObjects(osg::State* = 0) const;

            ViewDependentData*                  _viewDependentData;

            unsigned int                        _textureUnit;
            ref_ptr<osg::Texture2D>        _texture;
            ref_ptr<osg::TexGen>           _texgen;
            ref_ptr<osg::Camera>           _camera;
        };

        typedef std::list< ref_ptr<ShadowData> > ShadowDataList;


        class OSGSHADOW_EXPORT ViewDependentData : public CVBF_Referenced
        {
        public:
            ViewDependentData(ViewDependentShadowMap* vdsm);

			ViewDependentShadowMap* getViewDependentShadowMap() { return _viewDependentShadowMap; }
            const ViewDependentShadowMap* getViewDependentShadowMap() const { return _viewDependentShadowMap; }

            LightDataList& getLightDataList() { return _lightDataList; }

            ShadowDataList& getShadowDataList() { return _shadowDataList; }

            osg::StateSet* getStateSet() { return _stateset.get(); }

            virtual void releaseGLObjects(osg::State* = 0) const;

        protected:
            virtual ~ViewDependentData() {}

            ViewDependentShadowMap*     _viewDependentShadowMap;

            ref_ptr<osg::StateSet> _stateset;

            LightDataList               _lightDataList;
            ShadowDataList              _shadowDataList;
        };

        virtual ViewDependentData* createViewDependentData(osgUtil::CullVisitor* cv);

        ViewDependentData* getViewDependentData(osgUtil::CullVisitor* cv);



        virtual void createShaders();

        virtual bool selectActiveLights(osgUtil::CullVisitor* cv, ViewDependentData* vdd) const;

        virtual osg::Polytope computeLightViewFrustumPolytope(Frustum& frustum, LightData& positionedLight);

        virtual bool computeShadowCameraSettings(Frustum& frustum, LightData& positionedLight, osg::Matrixd& projectionMatrix, osg::Matrixd& viewMatrix);

        virtual bool adjustPerspectiveShadowMapCameraSettings(osgUtil::RenderStage* renderStage, Frustum& frustum, LightData& positionedLight, osg::Camera* camera);

        virtual bool assignTexGenSettings(osgUtil::CullVisitor* cv, osg::Camera* camera, unsigned int textureUnit, osg::TexGen* texgen);

        virtual void cullShadowReceivingScene(osgUtil::CullVisitor* cv) const;

        virtual void cullShadowCastingScene(osgUtil::CullVisitor* cv, osg::Camera* camera) const;

        virtual osg::StateSet* selectStateSetForRenderingShadow(ViewDependentData& vdd) const;


protected:
        virtual ~ViewDependentShadowMap();

        typedef std::map< osgUtil::CullVisitor*, ref_ptr<ViewDependentData> >  ViewDependentDataMap;
        mutable OpenThreads::Mutex              _viewDependentDataMapMutex;
        ViewDependentDataMap                    _viewDependentDataMap;

        ref_ptr<osg::StateSet>             _shadowRecievingPlaceholderStateSet;

        ref_ptr<osg::StateSet>             _shadowCastingStateSet;
        ref_ptr<osg::PolygonOffset>        _polygonOffset;
        ref_ptr<osg::Texture2D>            _fallbackBaseTexture;
        ref_ptr<osg::Texture2D>            _fallbackShadowMapTexture;

        typedef std::vector< ref_ptr<osg::Uniform> > Uniforms;
        mutable OpenThreads::Mutex              _accessUnfiromsAndProgramMutex;
        Uniforms                                _uniforms;
        ref_ptr<osg::Program>              _program;
};

}

#endif
