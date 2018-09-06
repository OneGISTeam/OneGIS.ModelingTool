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

	// 标准编程器：在单个粒子的生命周期中，用户可以使用编程器的实例控制粒子的位置，需要与Operator对象组合使用
    class OSGPARTICLE_EXPORT ModularProgram: public Program 
	{
    public:
        ModularProgram();
        ModularProgram(const ModularProgram& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,ModularProgram);
        
		// 获取操作器的数量
        inline int numOperators() const;
             
		// 添加/获取/移除操作器
        inline void addOperator(Operator* o);
        inline Operator* getOperator(int i);
        inline const Operator* getOperator(int i) const;
        inline void removeOperator(int i);        
            
    protected:
        virtual ~ModularProgram() {}
        ModularProgram& operator=(const ModularProgram&) { return *this; }
        
		// 重载函数，对粒子系统执行program
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
