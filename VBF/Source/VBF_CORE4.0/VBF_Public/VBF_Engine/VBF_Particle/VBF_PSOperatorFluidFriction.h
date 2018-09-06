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
//osgParticle - Copyright (C) 2002 Marco Jez

#ifndef OSGPARTICLE_FLUIDFRICTIONOPERATOR
#define OSGPARTICLE_FLUIDFRICTIONOPERATOR 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>

namespace osgParticle
{

    class Particle;    

	// 空气阻力或流体操作器：模拟流体的摩擦。通过该操作器可以使粒子按给定的密度和粘度象流体一样移动
	// 有两个函数可以快速设置纯水和空气的参数。用户可以调用setOverrideRadius决定是否使用粒子的物理半径或其它值来计算力
    class OSGPARTICLE_EXPORT FluidFrictionOperator: public Operator 
	{
    public:
        
        FluidFrictionOperator();
        FluidFrictionOperator(const FluidFrictionOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Object(osgParticle, FluidFrictionOperator);
               
		// 设置/获取流体的密度
        inline void setFluidDensity(float d);
        inline float getFluidDensity() const;
        
        // 设置/获取流体的粘度
        inline void setFluidViscosity(float v);
        inline float getFluidViscosity() const;
        
        // 设置/获取风
        inline void setWind(const osg::Vec3& wind) { _wind = wind; }
        inline const osg::Vec3& getWind() const { return _wind; }
               
        // 设置/获取半径值(如果想用粒子的半径传入 0 )
        inline void setOverrideRadius(float r);
        inline float getOverrideRadius() const;        
        
        // 设置空气的参数(20癈 temperature).
        inline void setFluidToAir();
        
        // 设置纯水的参数(20癈 temperature).
        inline void setFluidToWater();
        
        // 对粒子应用摩擦力，不要手工调用该方法
        void operate(Particle* P, double dt);
        
        // 执行一些初始化工作，不要手工调用该方法
        inline void beginOperate(Program* prg);
        
    protected:
        virtual ~FluidFrictionOperator() {}
        FluidFrictionOperator &operator=(const FluidFrictionOperator &) { return *this; }
        
    private:
        float       _coeff_A;
        float       _coeff_B;
        float       _density;
        float       _viscosity;
        float       _ovr_rad;
        osg::Vec3   _wind;
        Program*    _current_program;
    };
    
    // INLINE FUNCTIONS
    
    inline float FluidFrictionOperator::getFluidDensity() const
    {
        return _density;
    }

    inline float FluidFrictionOperator::getFluidViscosity() const
    {
        return _viscosity;
    }
    
    inline void FluidFrictionOperator::setFluidDensity(float d)
    {
        _density = d;
        _coeff_B = 0.2f * osg::PI * _density;
    }

    inline void FluidFrictionOperator::setFluidViscosity(float v)
    {
        _viscosity = v;
        _coeff_A = 6 * osg::PI * _viscosity;
    }
    
    inline void FluidFrictionOperator::setFluidToAir()
    {
        setFluidViscosity(1.8e-5f);
        setFluidDensity(1.2929f);
    }

    inline void FluidFrictionOperator::setFluidToWater()
    {
        setFluidViscosity(1.002e-3f);
        setFluidDensity(1.0f);
    }
    
    inline float FluidFrictionOperator::getOverrideRadius() const
    {
        return _ovr_rad;
    }
    
    inline void FluidFrictionOperator::setOverrideRadius(float r)
    {
        _ovr_rad = r;
    }
    
    inline void FluidFrictionOperator::beginOperate(Program* prg)
    {
        _current_program = prg;
    }

}


#endif
