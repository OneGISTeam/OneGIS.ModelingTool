#ifndef OSGPARTICLE_EXPLOSIONOPERATOR
#define OSGPARTICLE_EXPLOSIONOPERATOR

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{


/** An explosion operator exerts force on each particle away from the explosion center.
    Refer to David McAllister's Particle System API (http://www.particlesystems.org)
*/
class ExplosionOperator : public Operator
{
public:
    ExplosionOperator()
    :   Operator(), _radius(1.0f),
        _magnitude(1.0f), _epsilon(1e-3), _sigma(1.0f),
        _inexp(0.0f), _outexp(0.0f)
    {}
    
    ExplosionOperator( const ExplosionOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    :   Operator(copy, copyop), _center(copy._center), _radius(copy._radius),
        _magnitude(copy._magnitude), _epsilon(copy._epsilon), _sigma(copy._sigma),
        _inexp(copy._inexp), _outexp(copy._outexp)
    {}
    
    META_Object( osgParticle, ExplosionOperator );
    
    // 设置爆炸中心
    void setCenter( const osg::Vec3& c ) { _center = c; }
    const osg::Vec3& getCenter() const { return _center; }
    

    // 设置爆炸波作用的半径
    void setRadius( float r ) { _radius = r; }
    float getRadius() const { return _radius; }
    
    /// Set the acceleration scale
    void setMagnitude( float mag ) { _magnitude = mag; }
    
    /// Get the acceleration scale
    float getMagnitude() const { return _magnitude; }
    
    /// Set the acceleration epsilon
    void setEpsilon( float eps ) { _epsilon = eps; }
    
    /// Get the acceleration epsilon
    float getEpsilon() const { return _epsilon; }
    
    /// Set broadness of the strength of the wave
    void setSigma( float s ) { _sigma = s; }
    
    /// Get broadness of the strength of the wave
    float getSigma() const { return _sigma; }
    
    /// Apply the acceleration to a particle. Do not call this method manually.
    inline void operate( Particle* P, double dt );
    
    /// Perform some initializations. Do not call this method manually.
    inline void beginOperate( Program* prg );
    
protected:
    virtual ~ExplosionOperator() {}
    ExplosionOperator& operator=( const ExplosionOperator& ) { return *this; }
    
    osg::Vec3 _center;
    osg::Vec3 _xf_center;
    float _radius;
    float _magnitude;
    float _epsilon;
    float _sigma;
    float _inexp;
    float _outexp;
};

// INLINE METHODS

inline void ExplosionOperator::operate( Particle* P, double dt )
{
    osg::Vec3 dir = P->getPosition() - _xf_center;
    float length = dir.length();
    float distanceFromWave2 = (_radius - length) * (_radius - length);
    float Gd = exp(distanceFromWave2 * _inexp) * _outexp;
    float factor = (_magnitude * dt) / (length * (_epsilon+length*length));
    P->addVelocity( dir * (Gd * factor) );
}

inline void ExplosionOperator::beginOperate( Program* prg )
{
    if ( prg->getReferenceFrame()==ModularProgram::RELATIVE_RF )
    {
        _xf_center = prg->transformLocalToWorld(_center);
    }
    else
    {
        _xf_center = _center;
    }
    
    float oneOverSigma = (_sigma!=0.0f ? (1.0f / _sigma) : 1.0f);
    _inexp = -0.5f * oneOverSigma * oneOverSigma;
    _outexp = oneOverSigma / sqrt(osg::PI * 2.0f);
}


}

#endif
