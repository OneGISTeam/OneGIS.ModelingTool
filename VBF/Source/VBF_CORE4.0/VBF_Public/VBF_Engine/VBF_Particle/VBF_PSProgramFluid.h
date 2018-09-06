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

#ifndef OSGPARTICLE_FLUIDPROGRAM
#define OSGPARTICLE_FLUIDPROGRAM 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_PSProgram.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osgParticle
{

    // 流体编程器
    class OSGPARTICLE_EXPORT FluidProgram: public Program
    {
    public:
        FluidProgram();
        FluidProgram(const FluidProgram& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,FluidProgram);
        
        // 设置/获取流体的粘度
        inline void setFluidViscosity(float v)
        {
            m_fViscosity = v;
            m_fViscosityCoefficient = 6 * osg::PI * m_fViscosity;
        }

        inline float getFluidViscosity() const { return m_fViscosity; }


        // 设置/获取流体的密度
        inline void setFluidDensity(float d)
        {
            m_fDensity = d;
            m_fDensityCoefficient = 0.2f * osg::PI * m_fDensity;
        }
        inline float getFluidDensity() const { return m_fDensity; }
            
        // 设置/获取风向量
        inline void setWind(const osg::Vec3& wind) { m_vWind = wind; }
        inline const osg::Vec3& getWind() const { return m_vWind; }
        
        // 设置/获取加速度向量
        inline void setAcceleration(const osg::Vec3& v) { m_vAcceleration = v; }
        inline const osg::Vec3& getAcceleration() const { return m_vAcceleration; }

        // 设置加速度向量为重力向量（0, 0, -9.81），该值将被<CODE>scale</CODE> 乘
        inline void setToGravity(float scale = 1.0f) { m_vAcceleration.set(0, 0, -9.81f*scale); }

        // 设置流体参数为空气(20癈 temperature).
        inline void setFluidToAir()
        {
            setToGravity(1.0f);
            setFluidDensity(1.2929f);
            setFluidViscosity(1.8e-5f);
        }
        
        // 设置流体参数为纯水(20癈 temperature).
        inline void setFluidToWater()
        {
            setToGravity(1.0f);
            setFluidDensity(1.0f);
            setFluidViscosity(1.002e-3f);
        }
            
    protected:

        virtual ~FluidProgram() {}
        FluidProgram& operator=(const FluidProgram&) { return *this; }
        
        virtual void execute(double dt);

        osg::Vec3   m_vAcceleration;// 加速度
        float       m_fViscosity;   // 粘度
        float       m_fDensity;     // 密度
        osg::Vec3   m_vWind;        // 风

        float       m_fViscosityCoefficient;    // 粘度系数
        float       m_fDensityCoefficient;      // 密度系数
    };
    

}

#endif
