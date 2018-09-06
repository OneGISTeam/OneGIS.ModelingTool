#ifndef OSGPARTICLE_COUNTER
#define OSGPARTICLE_COUNTER 1

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{
	// 计数器：控制每一帧产生的粒子数
    class Counter: public osg::CVBF_Object 
	{
    public:
        inline Counter();
        inline Counter(const Counter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Counter"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Counter* >(obj) != 0; }

		// 本帧产生的粒子的数量
        virtual int numParticlesToCreate(double dt) const = 0;

    protected:
        ~Counter() {}
        Counter &operator=(const Counter &) { return *this; }
    };
    
    
    inline Counter::Counter() : osg::CVBF_Object()
    {
    }
    
    inline Counter::Counter(const Counter& copy, const osg::CopyOp& copyop) : osg::CVBF_Object(copy, copyop)
    {
    }

}

#endif
