#ifndef OSGPARTICLE_ANGULARACCELOPERATOR
#define OSGPARTICLE_ANGULARACCELOPERATOR 1

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle
{

 	// 角加速度操作器
    class AngularAccelOperator: public Operator 
	{
    public:
        inline AngularAccelOperator();
        inline AngularAccelOperator(const AngularAccelOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, AngularAccelOperator);

        /// Get the angular acceleration vector.
        inline const osg::Vec3& getAngularAcceleration() const;
        
        /// Set the angular acceleration vector.
        inline void setAngularAcceleration(const osg::Vec3& v);
        
        /// Apply the angular acceleration to a particle. Do not call this method manually.
        inline void operate(Particle* P, double dt);
        
        /// Perform some initializations. Do not call this method manually.
        inline void beginOperate(Program *prg);

    protected:
        virtual ~AngularAccelOperator() {}
        AngularAccelOperator& operator=(const AngularAccelOperator& ) { return *this; }        

    private:
        osg::Vec3 _angul_araccel;
        osg::Vec3 _xf_angul_araccel;
    };

    // INLINE FUNCTIONS
    
    inline AngularAccelOperator::AngularAccelOperator()
    : Operator(), _angul_araccel(0, 0, 0)
    {
    }
    
    inline AngularAccelOperator::AngularAccelOperator(const AngularAccelOperator& copy, const osg::CopyOp& copyop)
    : Operator(copy, copyop), _angul_araccel(copy._angul_araccel)
    {
    }

    inline const osg::Vec3& AngularAccelOperator::getAngularAcceleration() const
    {
        return _angul_araccel;
    }

    inline void AngularAccelOperator::setAngularAcceleration(const osg::Vec3& v)
    {
        _angul_araccel = v;
    }

    inline void AngularAccelOperator::operate(Particle* P, double dt)
    {
        P->addAngularVelocity(_xf_angul_araccel * dt);
    }
    
    inline void AngularAccelOperator::beginOperate(Program *prg)
    {
        if (prg->getReferenceFrame() == ModularProgram::RELATIVE_RF) {
            _xf_angul_araccel = prg->rotateLocalToWorld(_angul_araccel);
        } else {
            _xf_angul_araccel = _angul_araccel;
        }
    }

}


#endif
