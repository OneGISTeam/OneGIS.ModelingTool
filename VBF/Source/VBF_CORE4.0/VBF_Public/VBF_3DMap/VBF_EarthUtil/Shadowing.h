/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2008-2014 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

// ��Ө��ȡ��osgEarth-2.6

#ifndef OSGEARTH_UTIL_SHADOWING_H
#define OSGEARTH_UTIL_SHADOWING_H  1

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2DArray.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLight.h>


namespace osgEarth { namespace Util 
{
    /**
     * Group that casts shadows on its subgraph.
     *
     * NOTE!! This object is not multi-camera aware yet.
     */
    class OSGEARTHUTIL_EXPORT ShadowCaster : public CVBF_SGNodeGroup
    {
    public:
        ShadowCaster();

        /** Whether shadows are supported (requires GLSL) */
        bool supported() const { return _supported; }

        /**
         * The light that will cast shadows.
         * NOTE: Only works for point lights, like the sun.
         */
        void setLight(osg::Light* light) { _light = light; }
        osg::Light* getLight() { return _light.get(); }

        /**
         * Group of geometry that should cast shadows on this node's children.
         * You must add geometry here in order to cast shadows. The geometry
         * you add here will only be used to generate shadows - it must still
         * exist elsewhere in the scene graph for rendering.
         */
        osg::IVBF_SGNodeGroup* getShadowCastingGroup() { return _castingGroup.get(); }

        /**
         * Slice ranges. Each slice (the space beteen each value in the list)
         * represents a single shadow map in the Cascading Shadow Maps 
         * implementation.
         */
        const std::vector<float>& getRanges() { return _ranges; }
        void setRanges(const std::vector<float>& ranges);

        /**
         * The GPU texture image unit that will store the shadow map while
         * rendering the subgraph.
         */
        int getTextureImageUnit() const { return _texImageUnit; }
        void setTextureImageUnit(int unit);

        /**
         * The size (in both dimensions) of the shadow depth texture. Bigger
         * is sharper. Default is 1024. The total texture size used will be
         * size * # of range slices * 3 bytes.
         */
        unsigned getTextureSize() const { return _size; }
        void setTextureSize(unsigned size);

        /**
         * The ambient color of the shadow. This is blended with the fragment
         * color to achieve shadowing. Default is 0x7f7f7fff
         */
        void setShadowColor(const osg::Vec4f& value);
        const osg::Vec4f& getShadowColor() const { return _color; }

        /**
         * The blurring factor to apply to shadow PCF sampling. Using a blurring
         * factor will incur a GPU performance penalty. Default is 0.0.
         * Decent values are [0.0 -> 0.001].
         */
        void setBlurFactor(float value);
        float getBlurFactor() const { return _blurFactor; }

    public: // osg::Node
        virtual void traverse(osg::NodeVisitor& nv);

    protected:
        virtual ~ShadowCaster() { }

        void reinitialize();

        bool                                    _supported;
        ref_ptr<osg::IVBF_SGNodeGroup>          _castingGroup;
        unsigned                                _size;
        float                                   _blurFactor;
        osg::Vec4f                              _color;
        ref_ptr<osg::Light>						_light;
        ref_ptr<osg::Texture2DArray>			_shadowmap;
        ref_ptr<osg::StateSet>					_rttStateSet;
        std::vector<float>                      _ranges;
        std::vector<ref_ptr<osg::Camera> >		_rttCameras;
        osg::Matrix                             _prevProjMatrix;

        int							_texImageUnit;
        ref_ptr<osg::StateSet>		_renderStateSet;
        ref_ptr<osg::Uniform>		_shadowMapTexGenUniform;
        ref_ptr<osg::Uniform>		_shadowBlurUniform;
        ref_ptr<osg::Uniform>		_shadowColorUniform;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_UTIL_SHADOWING_H
