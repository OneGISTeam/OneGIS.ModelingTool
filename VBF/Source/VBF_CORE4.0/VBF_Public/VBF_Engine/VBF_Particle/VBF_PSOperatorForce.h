#ifndef OSGPARTICLE_FORCEOPERATOR
#define OSGPARTICLE_FORCEOPERATOR 1

#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle
{
	// 作用力操作：对粒子使用恒定的作用力。如果粒子的质量用公斤（kg）表示，长度用米表示，则力用牛顿（Newtons）表示
    class ForceOperator: public Operator 
	{
    public:
        inline ForceOperator();
        inline ForceOperator(const ForceOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Object(osgParticle, ForceOperator);
        
        // 设置/获取作用力
        inline const osg::Vec3& getForce() const;
        inline void setForce(const osg::Vec3& f);
        
        // 对粒子应用作用力，不要手工调用该方法
        inline void operate(Particle* P, double dt);
        
        // 执行一些初始化工作，不要手工调用该方法
        inline void beginOperate(Program *prg);
        
    protected:
        virtual ~ForceOperator() {};
        ForceOperator& operator=(const ForceOperator&) { return *this; }        
        
    private:
        osg::Vec3 _force;
        osg::Vec3 _xf_force;
    };
    
    // INLINE FUNCTIONS
    
    inline ForceOperator::ForceOperator()
    : Operator(), _force(0, 0, 0)
    {        
    }
    
    inline ForceOperator::ForceOperator(const ForceOperator& copy, const osg::CopyOp& copyop)
    : Operator(copy, copyop), _force(copy._force)
    {
    }
    
    inline const osg::Vec3& ForceOperator::getForce() const
    {
        return _force;
    }
    
    inline void ForceOperator::setForce(const osg::Vec3& v)
    {
        _force = v;
    }
    
    inline void ForceOperator::operate(Particle* P, double dt)
    {
        P->addVelocity(_xf_force * (P->getMassInv() * dt));
    }
    
    inline void ForceOperator::beginOperate(Program *prg)
    {
        if (prg->getReferenceFrame() == ModularProgram::RELATIVE_RF) {
            _xf_force = prg->rotateLocalToWorld(_force);
        } else {
            _xf_force = _force;
        }
    }
}

#endif
