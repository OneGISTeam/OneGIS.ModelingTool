#ifndef OSGPARTICLE_DAMPINGOPERATOR
#define OSGPARTICLE_DAMPINGOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{

// 阻尼操作器：对粒子速率应用一个阻尼常量。参见David McAllister的粒子系统API (http://www.particlesystems.org)
class DampingOperator : public Operator
{
public:
    DampingOperator() : Operator(), _cutoffLow(0.0f), _cutoffHigh(FLT_MAX)
    { _damping.set(1.0f, 1.0f, 1.0f); }
    
    DampingOperator( const DampingOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    :   Operator(copy, copyop), _damping(copy._damping),
        _cutoffLow(copy._cutoffLow), _cutoffHigh(copy._cutoffHigh)
    {}
    
    META_Object( osgParticle, DampingOperator );
    
    // 设置/获取阻尼因子
    void setDamping( float x, float y, float z ) { _damping.set(x, y, z); }
    void setDamping( const osg::Vec3& damping ) { _damping = damping; }
    void setDamping( float x ) { _damping.set(x, x, x); }
    void getDamping( float& x, float& y, float& z ) const { x = _damping.x(); y = _damping.y(); z = _damping.z(); }    
    const osg::Vec3& getDamping() const { return _damping; }
    
    // 设置/获取速率截止因子（velocity cutoff factors）
    void setCutoff( float low, float high ) { _cutoffLow = low; _cutoffHigh = high; }
    void setCutoffLow( float low ) { _cutoffLow = low; }
    void setCutoffHigh( float low ) { _cutoffHigh = low; }
    void getCutoff( float& low, float& high ) const { low = _cutoffLow; high = _cutoffHigh; }
    float getCutoffLow() const { return _cutoffLow; }
    float getCutoffHigh() const { return _cutoffHigh; }
    
    // 对粒子应用加速度，不要手工调用该方法
    inline void operate( Particle* P, double dt );
    
protected:
    virtual ~DampingOperator() {}
    DampingOperator& operator=( const DampingOperator& ) { return *this; }
    
    osg::Vec3 _damping;
    float _cutoffLow;
    float _cutoffHigh;
};

// INLINE METHODS

inline void DampingOperator::operate( Particle* P, double dt )
{
    const osg::Vec3& vel = P->getVelocity();
    float length2 = vel.length2();
    if ( length2>=_cutoffLow && length2<=_cutoffHigh )
    {
        osg::Vec3 newvel( vel.x() * (1.0f - (1.0f - _damping.x()) * dt),
                          vel.y() * (1.0f - (1.0f - _damping.y()) * dt),
                          vel.z() * (1.0f - (1.0f - _damping.z()) * dt) );
        P->setVelocity( newvel );
    }
}


}

#endif
