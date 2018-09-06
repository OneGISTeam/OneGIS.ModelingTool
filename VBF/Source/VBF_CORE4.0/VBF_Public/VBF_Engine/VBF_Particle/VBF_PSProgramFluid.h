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

    // ��������
    class OSGPARTICLE_EXPORT FluidProgram: public Program
    {
    public:
        FluidProgram();
        FluidProgram(const FluidProgram& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,FluidProgram);
        
        // ����/��ȡ�����ճ��
        inline void setFluidViscosity(float v)
        {
            m_fViscosity = v;
            m_fViscosityCoefficient = 6 * osg::PI * m_fViscosity;
        }

        inline float getFluidViscosity() const { return m_fViscosity; }


        // ����/��ȡ������ܶ�
        inline void setFluidDensity(float d)
        {
            m_fDensity = d;
            m_fDensityCoefficient = 0.2f * osg::PI * m_fDensity;
        }
        inline float getFluidDensity() const { return m_fDensity; }
            
        // ����/��ȡ������
        inline void setWind(const osg::Vec3& wind) { m_vWind = wind; }
        inline const osg::Vec3& getWind() const { return m_vWind; }
        
        // ����/��ȡ���ٶ�����
        inline void setAcceleration(const osg::Vec3& v) { m_vAcceleration = v; }
        inline const osg::Vec3& getAcceleration() const { return m_vAcceleration; }

        // ���ü��ٶ�����Ϊ����������0, 0, -9.81������ֵ����<CODE>scale</CODE> ��
        inline void setToGravity(float scale = 1.0f) { m_vAcceleration.set(0, 0, -9.81f*scale); }

        // �����������Ϊ����(20�C temperature).
        inline void setFluidToAir()
        {
            setToGravity(1.0f);
            setFluidDensity(1.2929f);
            setFluidViscosity(1.8e-5f);
        }
        
        // �����������Ϊ��ˮ(20�C temperature).
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

        osg::Vec3   m_vAcceleration;// ���ٶ�
        float       m_fViscosity;   // ճ��
        float       m_fDensity;     // �ܶ�
        osg::Vec3   m_vWind;        // ��

        float       m_fViscosityCoefficient;    // ճ��ϵ��
        float       m_fDensityCoefficient;      // �ܶ�ϵ��
    };
    

}

#endif
