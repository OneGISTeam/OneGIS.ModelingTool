#ifndef OSGPARTICLE_EMITTER
#define OSGPARTICLE_EMITTER 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/ParticleProcessor>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>

namespace osgParticle
{

	// 喷发器的基类，一个标准的喷发器（ModularEmitter）包括一个计数器（Counter）、一个放置器（Placer）和一个发射器（Shooter）
    class OSGPARTICLE_EXPORT Emitter: public ParticleProcessor 
	{
    public:
        Emitter();
        Emitter(const Emitter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Emitter"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Emitter*>(obj) != 0; }
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } }
        
        // 设置/获取粒子模板
        inline const Particle& getParticleTemplate() const { return _ptemp; }
        inline void setParticleTemplate(const Particle& p);
 
		// 设置/获取是否使用默认的粒子模板，该标志为true时，设置的粒子模板被忽略，用默认的粒子模板代替
        inline bool getUseDefaultTemplate() const { return _usedeftemp; }
        inline void setUseDefaultTemplate(bool v) { _usedeftemp = v; }

    protected:
        virtual ~Emitter() {}
        Emitter& operator=(const Emitter&) { return *this; }
        
        inline void process(double dt)  { emitParticles(dt); }
        
		// 子类必须重写emitParticles以产生新的粒子
        virtual void emitParticles(double dt) = 0;
        
        bool _usedeftemp;
        Particle _ptemp;
    };

 
    inline void Emitter::setParticleTemplate(const Particle& p)
    {
        _ptemp = p;
        _usedeftemp = false;
    }

}


#endif

