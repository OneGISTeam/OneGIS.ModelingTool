#ifndef OSGPARTICLE_ACCELOPERATOR
#define OSGPARTICLE_ACCELOPERATOR 1

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle
{
	// 加速度操作器
    class AccelOperator: public Operator 
	{
    public:
        inline AccelOperator();
        inline AccelOperator(const AccelOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, AccelOperator);

        // 设置/获取加速向量
        inline const osg::Vec3& getAcceleration() const;
        inline void setAcceleration(const osg::Vec3& v);
        
        /** Quickly set the acceleration vector to the gravity on earth (0, 0, -9.81).
            The acceleration will be multiplied by the <CODE>scale</CODE> parameter.
        */
        inline void setToGravity(float scale = 1);
        
        /// Apply the acceleration to a particle. Do not call this method manually.
        inline void operate(Particle* P, double dt);
        
        /// Perform some initializations. Do not call this method manually.
        inline void beginOperate(Program *prg);

    protected:
        virtual ~AccelOperator() {}
        AccelOperator &operator=(const AccelOperator &) { return *this; }        

    private:
        osg::Vec3 _accel;
        osg::Vec3 _xf_accel;
    };


    inline AccelOperator::AccelOperator()
    : Operator(), _accel(0, 0, 0)
    {
    }
    
    inline AccelOperator::AccelOperator(const AccelOperator& copy, const osg::CopyOp& copyop)
    : Operator(copy, copyop), _accel(copy._accel)
    {
    }

    inline const osg::Vec3& AccelOperator::getAcceleration() const
    {
        return _accel;
    }

    inline void AccelOperator::setAcceleration(const osg::Vec3& v)
    {
        _accel = v;
    }
    
    inline void AccelOperator::setToGravity(float scale)
    {
        _accel.set(0, 0, -9.80665f * scale);
    }

    inline void AccelOperator::operate(Particle* P, double dt)
    {
        P->addVelocity(_xf_accel * dt);
    }
    
    inline void AccelOperator::beginOperate(Program *prg)
    {
        if (prg->getReferenceFrame() == ModularProgram::RELATIVE_RF) {
            _xf_accel = prg->rotateLocalToWorld(_accel);
        } else {
            _xf_accel = _accel;
        }
    }

}


#endif
