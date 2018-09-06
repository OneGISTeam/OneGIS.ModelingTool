#ifndef OSGPARTICLE_PROGRAM
#define OSGPARTICLE_PROGRAM 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/ParticleProcessor>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>

namespace osgParticle
{

	// ����������Ӵ����������࣬������ɸѡ�����и�������
    class OSGPARTICLE_EXPORT Program: public ParticleProcessor
    {
    public:
        Program();
        Program(const Program& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "Program"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Program*>(obj) != 0; }
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } }

    protected:
        virtual ~Program() {}
        Program& operator=(const Program&) { return *this; }

        // ���ظ����ʵ�֣��û���Ҫ���øú���
		inline void process(double dt) { execute(dt); }
        
        // ������ϵͳִ��program������������������
        virtual void execute(double dt) = 0;

    };
}

#endif
