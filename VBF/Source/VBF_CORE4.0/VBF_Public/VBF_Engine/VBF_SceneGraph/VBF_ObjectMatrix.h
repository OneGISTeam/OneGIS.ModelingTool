#ifndef OSG_OBJECT_MATRIX
#define OSG_OBJECT_MATRIX 1

#include <VBF_Engine/VBF_SceneGraph/Config>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObjectMatrixd.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObjectMatrixf.h>

namespace osg {

#ifdef OSG_USE_FLOAT_MATRIX
    typedef RefMatrixf RefMatrix;
#else
    typedef RefMatrixd RefMatrix;
#endif

} //namespace osg


#endif
