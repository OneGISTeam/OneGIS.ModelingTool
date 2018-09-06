#ifndef OSG_PROJECTION
#define OSG_PROJECTION 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <Types/VBF_Matrix.h>

namespace osg {

class IVBF_SGNodeGroupProjection : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupProjection(){}
	IVBF_SGNodeGroupProjection(const IVBF_SGNodeGroupProjection& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupProjection(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

    // ����/��ȡ�任����
    virtual void setMatrix(const Matrix& mat)=0;
    virtual const Matrix& getMatrix() const=0;

    // ǰ�ˣ���ˣ��任����
    virtual void preMult(const Matrix& mat)=0;
        
    // ��ˣ��ҳˣ��任����
    virtual void postMult(const Matrix& mat)=0;
};
/** Projection nodes set up the frustum/orthographic projection used when rendering the scene.
*/
class OSG_EXPORT Projection : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupProjection>
{
    public :


        Projection();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Projection(const Projection&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        Projection(const Matrix& matix);

        META_Node(osg, Projection);

        // ����/��ȡ�任����
        void setMatrix(const Matrix& mat) { _matrix = mat; }
        inline const Matrix& getMatrix() const { return _matrix; }

        // ǰ�ˣ���ˣ��任����
        void preMult(const Matrix& mat) { _matrix.preMult(mat); }
        
        // ��ˣ��ҳˣ��任����
        void postMult(const Matrix& mat)  { _matrix.postMult(mat); }
    

    protected :
    
        virtual ~Projection();
                       
        Matrix  _matrix;

};

}

#endif
