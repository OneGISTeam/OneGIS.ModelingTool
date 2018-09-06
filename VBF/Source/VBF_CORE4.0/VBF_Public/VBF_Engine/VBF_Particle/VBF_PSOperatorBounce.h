#ifndef OSGPARTICLE_BOUNCEOPERATOR
#define OSGPARTICLE_BOUNCEOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperatorDomain.h>

namespace osgParticle
{

// ����������������Ӱ�����ӵ��ٶȣ�ʹ֮�ص����μ�David McAllister������ϵͳAPI (http://www.particlesystems.org)
class OSGPARTICLE_EXPORT BounceOperator : public DomainOperator
{
public:
    BounceOperator()
    : DomainOperator(), _friction(1.0f), _resilience(0.0f), _cutoff(0.0f)
    {}
    
    BounceOperator( const BounceOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    :   DomainOperator(copy, copyop),
        _friction(copy._friction), _resilience(copy._resilience), _cutoff(copy._cutoff)
    {}
    
    META_Object( osgParticle, BounceOperator );
    
    // ����/��ȡĦ����
    void setFriction( float f ) { _friction = f; }
    float getFriction() const { return _friction; }
    
    // ����/��ȡ����
    void setResilience( float r ) { _resilience = r; }
    float getResilience() const { return _resilience; }
    
    // ����/��ȡ���ʽ�ֹ����
    void setCutoff( float v ) { _cutoff = v; }
    float getCutoff() const { return _cutoff; }
    
protected:
    virtual ~BounceOperator() {}
    BounceOperator& operator=( const BounceOperator& ) { return *this; }
    
    virtual void handleTriangle( const Domain& domain, Particle* P, double dt );
    virtual void handleRectangle( const Domain& domain, Particle* P, double dt );
    virtual void handlePlane( const Domain& domain, Particle* P, double dt );
    virtual void handleSphere( const Domain& domain, Particle* P, double dt );
    virtual void handleDisk( const Domain& domain, Particle* P, double dt );
    
    float _friction;
    float _resilience;
    float _cutoff;
};


}

#endif
