#ifndef OSG_CULLFACE
#define OSG_CULLFACE 1

#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

namespace osg {

/** Class to globally enable/disable OpenGL's polygon culling mode.
 */     
class OSG_EXPORT CullFace : public StateAttribute
{
    public :
    
        enum Mode {
            FRONT = GL_FRONT,
            BACK = GL_BACK,
            FRONT_AND_BACK = GL_FRONT_AND_BACK
        };
    // IE可能错误
        CullFace(Mode mode=BACK):
            _mode(mode) {}
// IE可能错误
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        CullFace(const CullFace& cf,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(cf,copyop),
            _mode(cf._mode) {}

        META_StateAttribute(osg, CullFace, CULLFACE);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(CullFace,sa)

            // compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_mode)

            return 0; // passed all the above comparison macros, must be equal.
        }

        virtual bool getModeUsage(StateAttribute::ModeUsage& usage) const
        {
            usage.usesMode(GL_CULL_FACE);
            return true;
        }

        inline void setMode(Mode mode) { _mode = mode; }

        inline Mode getMode() const { return _mode; }
    
        virtual void apply(State& state) const;
        
    protected:
    
        virtual ~CullFace();
        
        Mode _mode;

};

}

#endif
