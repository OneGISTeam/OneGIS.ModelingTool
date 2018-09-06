/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2008-2012 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef OSGEARTH_PHONG_LIGHTING_EFFECT_H
#define OSGEARTH_PHONG_LIGHTING_EFFECT_H

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

namespace osgEarth { namespace Util 
{
    /**
     * Shader effect that performs simple Phong lighting.
     */
    class OSGEARTHUTIL_EXPORT PhongLightingEffect : public CVBF_Referenced
    {
    public:
        /** constructs a new effect */
        PhongLightingEffect();

        /** contructs a new effect and attaches it to a stateset. */
        PhongLightingEffect(osg::StateSet* stateset);

        /** is it supported by the h/w? */
        bool supported() const { return _supported; }

        /** whether to create its own lighting mode uniform (default = true).
          * Set this to false if you are creating the lighting uniform elsewhere.
          * The lighting uniform is returned by ShaderFactory::createUniformForGLMode(GL_LIGHTING). */
        void setCreateLightingUniform(bool value);

    public:
        /** attach this effect to a stateset. */
        void attach(osg::StateSet* stateset);

        /** detach this effect from any attached statesets. */
        void detach();
        /** detach this effect from a stateset. */
        void detach(osg::StateSet* stateset);

    protected:
        virtual ~PhongLightingEffect();

        typedef std::list< observer_ptr<osg::StateSet> > StateSetList;

        bool _supported;
        StateSetList _statesets;
        bool _createLightingUniform;
        ref_ptr<osg::Uniform> _lightingUniform;

        void init();
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_PHONG_LIGHTING_EFFECT_H
