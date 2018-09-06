#ifndef OSGPARTICLE_CONNECTEDPARTICLESYSTEM
#define OSGPARTICLE_CONNECTEDPARTICLESYSTEM 1

#include <VBF_Engine/VBF_Particle/VBF_ParticleSystem.h>

namespace osgParticle
{

    // 一类特殊的粒子系统，把粒子连接成一个丝带一样，如导弹尾迹
    class OSGPARTICLE_EXPORT ConnectedParticleSystem: public osgParticle::ParticleSystem
    {
    public:
    
        ConnectedParticleSystem();
        ConnectedParticleSystem(const ConnectedParticleSystem& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, ConnectedParticleSystem);
        
        // 使用特定的模板创建一个新粒子(或模板为null).
        virtual Particle* createParticle(const Particle* ptemplate);
        
        // 重用第i个粒子
        virtual void reuseParticle(int i);
        
        // 绘制粒子（根据视线距离采用线或四边形条带）
        virtual void drawImplementation(osg::RenderInfo& renderInfo) const;
        
        // 获取线（或条带）上开始绘制的最前面的粒子
        const osgParticle::Particle* getStartParticle() const
        {
            return (m_idxStartParticle != Particle::INVALID_INDEX) ? &m_vParticles[m_idxStartParticle] : 0;
        }
        osgParticle::Particle* getStartParticle()
        {
            return (m_idxStartParticle != Particle::INVALID_INDEX) ? &m_vParticles[m_idxStartParticle] : 0;
        }
        
        // 设置/获取过滤时（绘制之前）可跳过的粒子最大数量
        void setMaxNumberOfParticlesToSkip(unsigned int maxNumberofParticlesToSkip){m_nMaxNumberOfParticlesToSkip = maxNumberofParticlesToSkip;}
        unsigned int getMaxNumberOfParticlesToSkip(){ return m_nMaxNumberOfParticlesToSkip;}
        
    protected:
        virtual ~ConnectedParticleSystem();

        ConnectedParticleSystem& operator=(const ConnectedParticleSystem&) { return *this; }
        
        int m_idxLastParticleCreated;   // 生成的最后一个粒子的位置
        int m_idxStartParticle;         // 绘制的第一个粒子的位置
        unsigned int m_nMaxNumberOfParticlesToSkip;
        unsigned int m_nCountParticle; // 对粒子进行计数，目的是计算纹理坐标

       
      };

}

#endif
