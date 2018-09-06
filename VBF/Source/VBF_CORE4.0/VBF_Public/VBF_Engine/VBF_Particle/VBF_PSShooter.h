#ifndef OSGPARTICLE_SHOOTER
#define OSGPARTICLE_SHOOTER 1

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{

    class Particle;

	// �������Ļ��ࡣ��������ָ�����ӵĳ�ʼ�ٶ�
    class Shooter: public osg::CVBF_Object
    {
    public:
        inline Shooter();
        inline Shooter(const Shooter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Shooter"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Shooter *>(obj) != 0; }

		// ����һ�����ӣ������������ʵ��
        virtual void shoot(Particle* P) const = 0;

    protected:
        virtual ~Shooter() {}
        Shooter &operator=(const Shooter &) { return *this; }
    };
    
    // INLINE FUNCTIONS
    
    inline Shooter::Shooter()
    : osg::CVBF_Object()
    {
    }
    
    inline Shooter::Shooter(const Shooter& copy, const osg::CopyOp& copyop)
    : osg::CVBF_Object(copy, copyop)
    {
    }

}

#endif
