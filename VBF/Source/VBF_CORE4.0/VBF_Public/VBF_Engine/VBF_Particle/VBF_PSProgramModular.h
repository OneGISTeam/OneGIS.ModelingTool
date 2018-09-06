#ifndef OSGPARTICLE_MODULARPROGRAM
#define OSGPARTICLE_MODULARPROGRAM 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_PSProgram.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osgParticle
{

	// ��׼��������ڵ������ӵ����������У��û�����ʹ�ñ������ʵ���������ӵ�λ�ã���Ҫ��Operator�������ʹ��
    class OSGPARTICLE_EXPORT ModularProgram: public Program 
	{
    public:
        ModularProgram();
        ModularProgram(const ModularProgram& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,ModularProgram);
        
		// ��ȡ������������
        inline int numOperators() const;
             
		// ���/��ȡ/�Ƴ�������
        inline void addOperator(Operator* o);
        inline Operator* getOperator(int i);
        inline const Operator* getOperator(int i) const;
        inline void removeOperator(int i);        
            
    protected:
        virtual ~ModularProgram() {}
        ModularProgram& operator=(const ModularProgram&) { return *this; }
        
		// ���غ�����������ϵͳִ��program
        void execute(double dt);
        
    private:
        typedef std::vector<ref_ptr<Operator> > Operator_vector;

        Operator_vector _operators;
    };
    
    // INLINE FUNCTIONS
    
    inline int ModularProgram::numOperators() const
    {
        return static_cast<int>(_operators.size());
    }

    inline void ModularProgram::addOperator(Operator* o)
    {
        _operators.push_back(o);
    }

    inline Operator* ModularProgram::getOperator(int i)
    {
        return _operators[i].get();
    }

    inline const Operator* ModularProgram::getOperator(int i) const
    {
        return _operators[i].get();
    }

    inline void ModularProgram::removeOperator(int i)
    {
        _operators.erase(_operators.begin()+i);
    }
    

}

#endif
