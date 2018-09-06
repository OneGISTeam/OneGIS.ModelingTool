#ifndef OSGPARTICLE_SINKOPERATOR
#define OSGPARTICLE_SINKOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperatorDomain.h>

namespace osgParticle
{
// ��͸������������ �����λ�û�����inside/outside������������ɱ�����ӡ��μ�David McAllister������ϵͳAPI (http://www.particlesystems.org)
class OSGPARTICLE_EXPORT SinkOperator : public DomainOperator
{
public:
    enum SinkTarget { SINK_POSITION, SINK_VELOCITY, SINK_ANGULAR_VELOCITY };
    enum SinkStrategy { SINK_INSIDE, SINK_OUTSIDE };
    
    SinkOperator()
    : DomainOperator(), _sinkTarget(SINK_POSITION), _sinkStrategy(SINK_INSIDE)
    {}
    
    SinkOperator( const SinkOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    : DomainOperator(copy, copyop), _sinkTarget(copy._sinkTarget), _sinkStrategy(copy._sinkStrategy)
    {}
    
    META_Object( osgParticle, SinkOperator );
    

	// ����/��ȡ��͸��������Ŀ��
    void setSinkTarget( SinkTarget so ) { _sinkTarget = so; }
    SinkTarget getSinkTarget() const { return _sinkTarget; }
    
	// ����/��ȡ��͸������������
    void setSinkStrategy( SinkStrategy ss ) { _sinkStrategy = ss; }
    SinkStrategy getSinkStrategy() const { return _sinkStrategy; }
    
    // ִ��һЩ��ʼ����������Ҫ�ֹ����ø÷���
    void beginOperate( Program* prg );
    
protected:
    virtual ~SinkOperator() {}
    SinkOperator& operator=( const SinkOperator& ) { return *this; }
    
    virtual void handlePoint( const Domain& domain, Particle* P, double dt );
    virtual void handleLineSegment( const Domain& domain, Particle* P, double dt );
    virtual void handleTriangle( const Domain& domain, Particle* P, double dt );
    virtual void handleRectangle( const Domain& domain, Particle* P, double dt );
    virtual void handlePlane( const Domain& domain, Particle* P, double dt );
    virtual void handleSphere( const Domain& domain, Particle* P, double dt );
    virtual void handleBox( const Domain& domain, Particle* P, double dt );
    virtual void handleDisk( const Domain& domain, Particle* P, double dt );
    
    inline const osg::Vec3& getValue( Particle* P );
    inline void kill( Particle* P, bool insideDomain );
    
    SinkTarget _sinkTarget;
    SinkStrategy _sinkStrategy;
};

// INLINE METHODS

inline const osg::Vec3& SinkOperator::getValue( Particle* P )
{
    switch ( _sinkTarget )
    {
    case SINK_VELOCITY: return P->getVelocity();
    case SINK_ANGULAR_VELOCITY: return P->getAngularVelocity();
    case SINK_POSITION: default: return P->getPosition();
    }
}

inline void SinkOperator::kill( Particle* P, bool insideDomain )
{
    if ( !((_sinkStrategy==SINK_INSIDE) ^ insideDomain) )
        P->kill();
}


}

#endif
