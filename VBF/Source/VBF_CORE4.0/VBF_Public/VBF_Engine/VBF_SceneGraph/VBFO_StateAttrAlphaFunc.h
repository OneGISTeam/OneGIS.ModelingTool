#ifndef OSG_ALPHAFUNC
#define OSG_ALPHAFUNC 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

#ifndef GL_ALPHA_TEST
    #define GL_ALPHA_TEST 0x0BC0
#endif

namespace osg {
  
// glAlphaFunc的封装
class OSG_EXPORT AlphaFunc : public StateAttribute
{
    public :
    
        enum ComparisonFunction 
		{
            NEVER = GL_NEVER,
            LESS = GL_LESS,
            EQUAL = GL_EQUAL,
            LEQUAL = GL_LEQUAL,
            GREATER = GL_GREATER,
            NOTEQUAL = GL_NOTEQUAL,
            GEQUAL = GL_GEQUAL,
            ALWAYS = GL_ALWAYS
        };


        AlphaFunc();
        // IE可能错误
        AlphaFunc(ComparisonFunction func,float ref):
            _comparisonFunc(func),
            _referenceValue(ref) 
		{
		}
// IE可能错误
        /** Copy constructor using CopyOp to manage deep vs shallow copy. */
        AlphaFunc(const AlphaFunc& af,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(af,copyop),
            _comparisonFunc(af._comparisonFunc),
            _referenceValue(af._referenceValue) 
		{
		}
        
        META_StateAttribute(osg, AlphaFunc,ALPHAFUNC);
        
        /** Return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        virtual int compare(const StateAttribute& sa) const
        {
            // Check for equal types, then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(AlphaFunc,sa)

            // Compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_comparisonFunc)
            COMPARE_StateAttribute_Parameter(_referenceValue)

            return 0; // Passed all the above comparison macros, so must be equal.
        }

        virtual bool getModeUsage(StateAttribute::ModeUsage& usage) const
        {
            usage.usesMode(GL_ALPHA_TEST);
            return true;
        }

        inline void setFunction(ComparisonFunction func,float ref)
        {
            _comparisonFunc = func;
            _referenceValue = ref;
        }
        
        inline void setFunction(ComparisonFunction func) { _comparisonFunc=func; }
        inline ComparisonFunction getFunction() const { return _comparisonFunc; }
        
        inline void setReferenceValue(float value) { _referenceValue=value; }
        inline float getReferenceValue() const { return _referenceValue; }
        
        virtual void apply(State& state) const;

    protected:
    
        virtual ~AlphaFunc();

        ComparisonFunction _comparisonFunc;
        float _referenceValue;

};

}

#endif
