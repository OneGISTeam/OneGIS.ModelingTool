#ifndef OSGPARTICLE_ORBITOPERATOR
#define OSGPARTICLE_ORBITOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{

// �����������ǿ���������ƹ�����С��μ�David McAllister������ϵͳAPI (http://www.particlesystems.org)
class OrbitOperator : public Operator
{
public:
    OrbitOperator()
    : Operator(), _magnitude(1.0f), _epsilon(1e-3), _maxRadius(FLT_MAX)
    {}
    
    OrbitOperator( const OrbitOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    :   Operator(copy, copyop), _center(copy._center), _magnitude(copy._magnitude),
        _epsilon(copy._epsilon), _maxRadius(copy._maxRadius)
    {}
    
    META_Object( osgParticle, OrbitOperator );
    
    // ����/��ȡ��������ĵ�
    void setCenter( const osg::Vec3& c ) { _center = c; }
    const osg::Vec3& getCenter() const { return _center; }
    
	// ����/��ȡ���ٶȱȣ�acceleration scale��
    void setMagnitude( float mag ) { _magnitude = mag; }
    float getMagnitude() const { return _magnitude; }
    
    // ���ü��ٶȣ�acceleration epsilon��
    void setEpsilon( float eps ) { _epsilon = eps; }
    float getEpsilon() const { return _epsilon; }
    
    // ����/��ȡ���뾶�����ӵ�������ģ�
    void setMaxRadius( float max ) { _maxRadius = max; }
    float getMaxRadius() const { return _maxRadius; }
    
    // ������Ӧ�ü��ٶȣ���Ҫ�ֹ����ø÷���
    inline void operate( Particle* P, double dt );
    
    // ִ��һЩ��ʼ����������Ҫ�ֹ����ø÷���
    inline void beginOperate( Program* prg );
    
protected:
    virtual ~OrbitOperator() {}
    OrbitOperator& operator=( const OrbitOperator& ) { return *this; }
    
    osg::Vec3 _center;
    osg::Vec3 _xf_center;
    float _magnitude;
    float _epsilon;
    float _maxRadius;
};

// INLINE METHODS

inline void OrbitOperator::operate( Particle* P, double dt )
{
    osg::Vec3 dir = _xf_center - P->getPosition();
    float length = dir.length();
    if ( length<_maxRadius )
    {
        P->addVelocity( dir * ((_magnitude * dt) /
                        (length * (_epsilon+length*length))) );
    }
}

inline void OrbitOperator::beginOperate( Program* prg )
{
    if ( prg->getReferenceFrame()==ModularProgram::RELATIVE_RF )
    {
        _xf_center = prg->transformLocalToWorld(_center);
    }
    else
    {
        _xf_center = _center;
    }
}


}

#endif
