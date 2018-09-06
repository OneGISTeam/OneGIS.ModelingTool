#ifndef OSGPARTICLE_PLACER
#define OSGPARTICLE_PLACER 1

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle
{

    class Particle;

	// 放置器：设置粒子的初始位置，是所有放置器的基类。
    class Placer: public osg::CVBF_Object 
	{
    public:
        Placer(){}
        Placer(const Placer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY): osg::CVBF_Object(copy, copyop) {}

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Placer"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Placer *>(obj) != 0; }

        virtual void place(Particle* P) const = 0; // 放置一个粒子，必须被子类实现
        virtual float volume() const { return 1.0f; } // 放置器的容量
        virtual osg::Vec3 getControlPosition() const = 0;// Return the control position of particles that placer will generate

    protected:
        ~Placer() {}
        Placer& operator=(const Placer& ) { return *this; }
    };
}

#endif
