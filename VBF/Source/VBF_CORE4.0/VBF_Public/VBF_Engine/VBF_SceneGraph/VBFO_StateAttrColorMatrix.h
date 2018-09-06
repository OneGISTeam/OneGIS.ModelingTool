#ifndef OSG_COLORMATRIX
#define OSG_COLORMATRIX 1

#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

namespace osg {

/** Encapsulates OpenGL color matrix functionality. */
class OSG_EXPORT ColorMatrix : public StateAttribute
{
    public :
    
        ColorMatrix();
// IE¿ÉÄÜ´íÎó
        /** Copy constructor using CopyOp to manage deep vs shallow copy. */
        ColorMatrix(const ColorMatrix& cm,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(cm,copyop),
            _matrix(cm._matrix) {}

        META_StateAttribute(osg, ColorMatrix, COLORMATRIX);
        
        /** Return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        virtual int compare(const StateAttribute& sa) const
        {
            // Check for equal types, then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(ColorMatrix,sa)

            // Compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_matrix)

            return 0; // Passed all the above comparison macros, so must be equal.
        }

        /** Sets the color matrix. */
        inline void setMatrix(const Matrix& matrix) { _matrix = matrix; }

        /** Gets the color matrix. */
        inline Matrix& getMatrix() { return _matrix; }

        /** Gets the const color matrix. */
        inline const Matrix& getMatrix() const { return _matrix; }

        /** Applies as OpenGL texture matrix. */
        virtual void apply(State& state) const;

    protected:

        virtual ~ColorMatrix( void );

        Matrix _matrix;

};

}


#endif
