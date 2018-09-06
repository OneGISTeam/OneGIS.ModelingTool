#ifndef OSGPARTICLE_VARIABLERATE_COUNTER
#define OSGPARTICLE_VARIABLERATE_COUNTER 1

#include <VBF_Engine/VBF_Particle/VBF_PSCounter.h>
#include <VBF_Engine/VBF_Particle/range>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{

    class VariableRateCounter: public Counter
	{
    public:
        inline VariableRateCounter();
        inline VariableRateCounter(const VariableRateCounter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "VariableRateCounter"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const VariableRateCounter *>(obj) != 0; }
        
        inline const rangef& getRateRange() const;
        inline void setRateRange(const rangef& r);
        inline void setRateRange(float minrange, float maxrange);
        
    protected:
        virtual ~VariableRateCounter() {}
        
    private:
        rangef _rate_range;
    };
    
    // INLINE FUNCTIONS
    
    inline VariableRateCounter::VariableRateCounter()
    : Counter(), _rate_range(1, 1)
    {
    }
    
    inline VariableRateCounter::VariableRateCounter(const VariableRateCounter& copy, const osg::CopyOp& copyop)
    : Counter(copy, copyop), _rate_range(copy._rate_range)
    {
    }
    
    inline const rangef &VariableRateCounter::getRateRange() const
    {
        return _rate_range;
    }
    
    inline void VariableRateCounter::setRateRange(const rangef& r)
    {
        _rate_range = r;
    }

    inline void VariableRateCounter::setRateRange(float minrange, float maxrange)
    {
        _rate_range.set(minrange, maxrange);
    }

}


#endif
