#ifndef VBF_MATH_MATRIX
#define VBF_MATH_MATRIX 1

#include <VBF_Engine/VBF_SceneGraph/Config>
#include <Types/VBF_Matrixd.h>
#include <Types/VBF_Matrixf.h>

namespace osg {

#ifdef OSG_USE_FLOAT_MATRIX
    typedef Matrixf Matrix;
//    typedef RefMatrixf RefMatrix;
#else
    typedef Matrixd Matrix;
//    typedef RefMatrixd RefMatrix;
#endif

} //namespace osg


#endif
