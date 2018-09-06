#ifndef OSGPARTICLE_ORBITOPERATOR
#define OSGPARTICLE_ORBITOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{

// 轨道操作器：强迫粒子在绕轨道运行。参见David McAllister的粒子系统API (http://www.particlesystems.org)
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
    
    // 设置/获取轨道的中心点
    void setCenter( const osg::Vec3& c ) { _center = c; }
    const osg::Vec3& getCenter() const { return _center; }
    
	// 设置/获取加速度比（acceleration scale）
    void setMagnitude( float mag ) { _magnitude = mag; }
    float getMagnitude() const { return _magnitude; }
    
    // 设置加速度（acceleration epsilon）
    void setEpsilon( float eps ) { _epsilon = eps; }
    float getEpsilon() const { return _epsilon; }
    
    // 设置/获取最大半径（粒子到轨道中心）
    void setMaxRadius( float max ) { _maxRadius = max; }
    float getMaxRadius() const { return _maxRadius; }
    
    // 对粒子应用加速度，不要手工调用该方法
    inline void operate( Particle* P, double dt );
    
    // 执行一些初始化工作，不要手工调用该方法
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
