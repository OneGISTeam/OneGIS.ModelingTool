#ifndef OSG_DEPTH
#define OSG_DEPTH 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

namespace osg {

/** Encapsulate OpenGL glDepthFunc/Mask/Range functions.
*/     
class OSG_EXPORT Depth : public StateAttribute
{
    public :
    
    
        enum Function
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


        Depth(Function func=LESS,double zNear=0.0, double zFar=1.0,bool writeMask=true);
     // IE¿ÉÄÜ´íÎó   
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Depth(const Depth& dp,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(dp,copyop),
            _func(dp._func),
            _zNear(dp._zNear),
            _zFar(dp._zFar),
            _depthWriteMask(dp._depthWriteMask) {}
        
        
        META_StateAttribute(osg, Depth, DEPTH);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(Depth,sa)

            // compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_func)
            COMPARE_StateAttribute_Parameter(_depthWriteMask)
            COMPARE_StateAttribute_Parameter(_zNear)
            COMPARE_StateAttribute_Parameter(_zFar)

            return 0; // passed all the above comparison macros, must be equal.
        }

        virtual bool getModeUsage(StateAttribute::ModeUsage& usage) const
        {
            usage.usesMode(GL_DEPTH_TEST);
            return true;
        }

        inline void setFunction(Function func) { _func = func; }        
        inline Function getFunction() const { return _func; }
               

        inline void setRange(double zNear, double zFar)
        {
            _zNear = zNear;
            _zFar = zFar;
        }

        inline void setZNear(double zNear) { _zNear=zNear; }
        inline double getZNear() const { return _zNear; }
    
        inline void setZFar(double zFar) { _zFar=zFar; }
        inline double getZFar() const { return _zFar; }

        inline void setWriteMask(bool mask) { _depthWriteMask = mask; }        
        inline bool getWriteMask() const { return _depthWriteMask; }


        virtual void apply(State& state) const;

    protected:
    
        virtual ~Depth();

        Function            _func;
        
        double              _zNear;
        double              _zFar;

        bool                _depthWriteMask;
};

}

#endif
