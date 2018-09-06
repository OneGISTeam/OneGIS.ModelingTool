#ifndef OSGPARTICLE_CONSTANTRATECOUNTER
#define OSGPARTICLE_CONSTANTRATECOUNTER 1

#include <VBF_Engine/VBF_Particle/VBF_PSCounter.h>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>

namespace osgParticle
{

    class ConstantRateCounter: public Counter
    {
    public:
        ConstantRateCounter(): Counter(),
            m_numParticlesToCreateMin(0),
            m_numParticlesToCreatePerSecond(0),
            m_dRemainder(0)
        {
        }

        ConstantRateCounter(const ConstantRateCounter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY):
             Counter(copy, copyop), 
             m_numParticlesToCreateMin(copy.m_numParticlesToCreateMin),
             m_numParticlesToCreatePerSecond(copy.m_numParticlesToCreatePerSecond),
             m_dRemainder(copy.m_dRemainder)
        {
        }
            
        
        META_Object(osgParticle, ConstantRateCounter);
        
        // ����/��ȡÿ֡�������ӵ���С��
        void setMinNumberOfParticlesToCreate(int minNumToCreate) { m_numParticlesToCreateMin = minNumToCreate; }
        int getMinNumberOfParticlesToCreate() const { return m_numParticlesToCreateMin; }
    
        // ����ÿ�봴����������
        void setNumberOfParticlesPerSecondToCreate(double numPerSecond) { m_numParticlesToCreatePerSecond = numPerSecond; }
        double getNumberOfParticlesPerSecondToCreate() const { return m_numParticlesToCreatePerSecond; }

        // ��֡������������
        virtual int numParticlesToCreate(double dt) const
        {
            double v = (dt*m_numParticlesToCreatePerSecond);
            int i = (int)(v);

            m_dRemainder += (v-(double)i);

            if (m_dRemainder>1.0)
            {
                ++i;
                m_dRemainder -= 1.0;
            }
            return osg::maximum(m_numParticlesToCreateMin, i);
        }
        
    protected:
        virtual ~ConstantRateCounter() {}
        
        int m_numParticlesToCreateMin; //�������ӵ���С����
        double m_numParticlesToCreatePerSecond; // ÿ����Ҫ������������
        mutable double m_dRemainder; // ��һ֡������
    };
    
}


#endif
