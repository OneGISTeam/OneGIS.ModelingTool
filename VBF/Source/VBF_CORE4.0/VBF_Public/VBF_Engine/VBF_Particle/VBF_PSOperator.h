#ifndef OSGPARTICLE_OPERATOR
#define OSGPARTICLE_OPERATOR 1

#include <VBF_Engine/VBF_Particle/VBF_PSProgram.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/VBF_Matrix.h>

namespace osgParticle
{

    
    class Particle;

 	// 操作器： 提供了控制粒子在生命周期中的运动特性的方法。用户可以改变现有的Operator类实例的参数或定义自己的Operator类。
    class Operator: public osg::CVBF_Object 
	{        
    public:
        inline Operator();
        inline Operator(const Operator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Operator"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Operator* >(obj) != 0; }


		// 设置/获取该操作器是否可用
        inline bool isEnabled() const;
        inline void setEnabled(bool v);
        
        /** Do something on all emitted particles.
            This method is called by <CODE>ModularProgram</CODE> objects to perform some operations
            on the particles. By default, it will call the <CODE>operate()</CODE> method for each particle.
            You must override it in descendant classes.
        */
        virtual void operateParticles(ParticleSystem* ps, double dt)
        {
            int n = ps->numParticles();
            for (int i=0; i<n; ++i)
            {
                Particle* P = ps->getParticle(i);
                if (P->isAlive() && isEnabled()) operate(P, dt);
            }
        }
        
        /**    Do something on a particle. 
            You must override it in descendant classes. Common operations
            consist of modifying the particle's velocity vector. The <CODE>dt</CODE> parameter is
            the time elapsed from last operation.            
        */
        virtual void operate(Particle* P, double dt) = 0;
        
        /** Do something before processing particles via the <CODE>operate()</CODE> method.
            Overriding this method could be necessary to query the calling <CODE>Program</CODE> object
            for the current reference frame. If the reference frame is RELATIVE_RF, then your
            class should prepare itself to do all operations in local coordinates.
        */
        virtual void beginOperate(Program *) {}
        
        /// Do something after all particles have been processed.
        virtual void endOperate() {}

    protected:
        virtual ~Operator() {}
        Operator &operator=(const Operator &) { return *this; }
        
    private:
        bool _enabled;        
    };
    
    // INLINE FUNCTIONS
    
    inline Operator::Operator()
    : osg::CVBF_Object(), _enabled(true)
    {
    }
    
    inline Operator::Operator(const Operator& copy, const osg::CopyOp& copyop)
    : osg::CVBF_Object(copy, copyop), _enabled(copy._enabled)
    {
    }
    
    inline bool Operator::isEnabled() const    
    {
        return _enabled;
    }
    
    inline void Operator::setEnabled(bool v)
    {
        _enabled = v;
    }


}

#endif
