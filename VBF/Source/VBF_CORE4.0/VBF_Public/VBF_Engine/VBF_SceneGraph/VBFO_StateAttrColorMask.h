#ifndef OSG_COLORMASK
#define OSG_COLORMASK 1

#include <VBF_Engine/VBF_SceneGraph/Export>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

namespace osg {

/** Encapsulates OpenGL glColorMaskFunc/Op/Mask functions.
*/     
class OSG_EXPORT ColorMask : public StateAttribute
{
    public :
    
    
        ColorMask();
// IE¿ÉÄÜ´íÎó
        ColorMask(bool red,bool green,bool blue,bool alpha):
            _red(red),
            _green(green),
            _blue(blue),
            _alpha(alpha) {}
            

        /** Copy constructor using CopyOp to manage deep vs shallow copy. */
        ColorMask(const ColorMask& cm,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(cm,copyop),
            _red(cm._red),
            _green(cm._green),
            _blue(cm._blue),
            _alpha(cm._alpha) {}
        
        META_StateAttribute(osg, ColorMask, COLORMASK);
        
        /** Return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        virtual int compare(const StateAttribute& sa) const
        {
            // Check for equal types, then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(ColorMask,sa)

            // Compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_red)
            COMPARE_StateAttribute_Parameter(_green)
            COMPARE_StateAttribute_Parameter(_blue)
            COMPARE_StateAttribute_Parameter(_alpha)

            return 0; // Passed all the above comparison macros, so must be equal.
        }

        inline void setMask(bool red,bool green,bool blue,bool alpha)
        {
            _red = red;
            _green = green;
            _blue = blue;
            _alpha = alpha;
            
        }
        
        inline void setRedMask(bool mask) { _red=mask; }
        inline bool getRedMask() const { return _red; }

        inline void setGreenMask(bool mask) { _green=mask; }
        inline bool getGreenMask() const { return _green; }

        inline void setBlueMask(bool mask) { _blue=mask; }
        inline bool getBlueMask() const { return _blue; }
        
        inline void setAlphaMask(bool mask) { _alpha=mask; }
        inline bool getAlphaMask() const { return _alpha; }

        virtual void apply(State& state) const;

    protected:
    
        virtual ~ColorMask();

        bool                _red;
        bool                _green;
        bool                _blue;
        bool                _alpha;

};

}

#endif
