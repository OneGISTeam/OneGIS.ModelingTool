#ifndef OSG_OBJECT_MATRIXF
#define OSG_OBJECT_MATRIXF 1
#include <VBF_Common/VBF_Math/VBF_Export.h>

//#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3d>
#include <Types/Vec4d>
#include <Types/VBF_Quat.h>
#include <Types/VBF_Matrixf.h>


namespace osg {


class RefMatrixf : public CVBF_Object, public Matrixf
{
    public:
    
        RefMatrixf():CVBF_Object(false), Matrixf() {}
        RefMatrixf( const Matrixf& other) : CVBF_Object(false), Matrixf(other) {}
        RefMatrixf( const Matrixd& other) : CVBF_Object(false), Matrixf(other) {}
        RefMatrixf( const RefMatrixf& other) : CVBF_Object(other), Matrixf(other) {}
        explicit RefMatrixf( Matrixf::value_type const * const def ):CVBF_Object(false), Matrixf(def) {}
        RefMatrixf( Matrixf::value_type a00, Matrixf::value_type a01, Matrixf::value_type a02, Matrixf::value_type a03,
            Matrixf::value_type a10, Matrixf::value_type a11, Matrixf::value_type a12, Matrixf::value_type a13,
            Matrixf::value_type a20, Matrixf::value_type a21, Matrixf::value_type a22, Matrixf::value_type a23,
            Matrixf::value_type a30, Matrixf::value_type a31, Matrixf::value_type a32, Matrixf::value_type a33):
            CVBF_Object(false), 
            Matrixf(a00, a01, a02, a03,
                   a10, a11, a12, a13,
                   a20, a21, a22, a23,
                   a30, a31, a32, a33) {}

        virtual CVBF_Object* cloneType() const { return new RefMatrixf(); } 
        virtual CVBF_Object* clone(const CopyOp&) const { return new RefMatrixf(*this); }
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const RefMatrixf*>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Matrix"; }
        
        
    protected:
    
        virtual ~RefMatrixf() {}
};


} //namespace osg


#endif
