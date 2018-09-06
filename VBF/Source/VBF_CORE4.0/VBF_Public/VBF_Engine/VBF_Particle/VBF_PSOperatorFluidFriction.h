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

	// ���������������������ģ�������Ħ����ͨ���ò���������ʹ���Ӱ��������ܶȺ�ճ��������һ���ƶ�
	// �������������Կ������ô�ˮ�Ϳ����Ĳ������û����Ե���setOverrideRadius�����Ƿ�ʹ�����ӵ�����뾶������ֵ��������
    class OSGPARTICLE_EXPORT FluidFrictionOperator: public Operator 
	{
    public:
        
        FluidFrictionOperator();
        FluidFrictionOperator(const FluidFrictionOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Object(osgParticle, FluidFrictionOperator);
               
		// ����/��ȡ������ܶ�
        inline void setFluidDensity(float d);
        inline float getFluidDensity() const;
        
        // ����/��ȡ�����ճ��
        inline void setFluidViscosity(float v);
        inline float getFluidViscosity() const;
        
        // ����/��ȡ��
        inline void setWind(const osg::Vec3& wind) { _wind = wind; }
        inline const osg::Vec3& getWind() const { return _wind; }
               
        // ����/��ȡ�뾶ֵ(����������ӵİ뾶���� 0 )
        inline void setOverrideRadius(float r);
        inline float getOverrideRadius() const;        
        
        // ���ÿ����Ĳ���(20�C temperature).
        inline void setFluidToAir();
        
        // ���ô�ˮ�Ĳ���(20�C temperature).
        inline void setFluidToWater();
        
        // ������Ӧ��Ħ��������Ҫ�ֹ����ø÷���
        void operate(Particle* P, double dt);
        
        // ִ��һЩ��ʼ����������Ҫ�ֹ����ø÷���
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
