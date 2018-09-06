/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
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

#ifndef OSGPARTICLE_SMOKEEFFECT
#define OSGPARTICLE_SMOKEEFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEffect.h>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitterModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramFluid.h>

namespace osgParticle
{
	// ÑÌÎíÐ§¹û
    class OSGPARTICLE_EXPORT SmokeEffect : public ParticleEffect
    {
    public:    
        explicit SmokeEffect(bool automaticSetup=true);
    
        SmokeEffect(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);      
        SmokeEffect(const SmokeEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Node(osgParticle,SmokeEffect);
        
        virtual void setDefaults();
        virtual void setUpEmitterAndProgram();

        virtual Emitter* getEmitter() { return m_ipEmitter.get(); }
        virtual const Emitter* getEmitter() const { return m_ipEmitter.get(); }

        virtual Program* getProgram() { return m_ipProgram.get(); }
        virtual const Program* getProgram() const { return m_ipProgram.get(); }
    
    protected:

        virtual ~SmokeEffect() {}
        
        ref_ptr<ModularEmitter> m_ipEmitter;
        ref_ptr<FluidProgram>   m_ipProgram;

    };
}

#endif
