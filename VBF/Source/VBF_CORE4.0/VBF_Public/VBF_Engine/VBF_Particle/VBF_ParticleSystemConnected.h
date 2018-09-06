#ifndef OSGPARTICLE_CONNECTEDPARTICLESYSTEM
#define OSGPARTICLE_CONNECTEDPARTICLESYSTEM 1

#include <VBF_Engine/VBF_Particle/VBF_ParticleSystem.h>

namespace osgParticle
{

    // һ�����������ϵͳ�����������ӳ�һ��˿��һ�����絼��β��
    class OSGPARTICLE_EXPORT ConnectedParticleSystem: public osgParticle::ParticleSystem
    {
    public:
    
        ConnectedParticleSystem();
        ConnectedParticleSystem(const ConnectedParticleSystem& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, ConnectedParticleSystem);
        
        // ʹ���ض���ģ�崴��һ��������(��ģ��Ϊnull).
        virtual Particle* createParticle(const Particle* ptemplate);
        
        // ���õ�i������
        virtual void reuseParticle(int i);
        
        // �������ӣ��������߾�������߻��ı���������
        virtual void drawImplementation(osg::RenderInfo& renderInfo) const;
        
        // ��ȡ�ߣ����������Ͽ�ʼ���Ƶ���ǰ�������
        const osgParticle::Particle* getStartParticle() const
        {
            return (m_idxStartParticle != Particle::INVALID_INDEX) ? &m_vParticles[m_idxStartParticle] : 0;
        }
        osgParticle::Particle* getStartParticle()
        {
            return (m_idxStartParticle != Particle::INVALID_INDEX) ? &m_vParticles[m_idxStartParticle] : 0;
        }
        
        // ����/��ȡ����ʱ������֮ǰ���������������������
        void setMaxNumberOfParticlesToSkip(unsigned int maxNumberofParticlesToSkip){m_nMaxNumberOfParticlesToSkip = maxNumberofParticlesToSkip;}
        unsigned int getMaxNumberOfParticlesToSkip(){ return m_nMaxNumberOfParticlesToSkip;}
        
    protected:
        virtual ~ConnectedParticleSystem();

        ConnectedParticleSystem& operator=(const ConnectedParticleSystem&) { return *this; }
        
        int m_idxLastParticleCreated;   // ���ɵ����һ�����ӵ�λ��
        int m_idxStartParticle;         // ���Ƶĵ�һ�����ӵ�λ��
        unsigned int m_nMaxNumberOfParticlesToSkip;
        unsigned int m_nCountParticle; // �����ӽ��м�����Ŀ���Ǽ�����������

       
      };

}

#endif
