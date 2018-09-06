
#ifndef OSG_MATRIXTRANSFORM
#define OSG_MATRIXTRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>

namespace osg {

/** MatrixTransform - is a subclass of Transform which has an osg::Matrix
  * which represents a 4x4 transformation of its children from local coordinates
  * into the Transform's parent coordinates.
*/
class IVBF_SGNodeGroupTransformMatrix : public IVBF_SGNodeGroupTransform
{
public:
	IVBF_SGNodeGroupTransformMatrix(){}
	IVBF_SGNodeGroupTransformMatrix(const IVBF_SGNodeGroupTransformMatrix& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformMatrix(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}


	// 设置/获取变换矩阵
	virtual void setMatrix(const Matrix& mat) =0;
	virtual const Matrix& getMatrix() const =0;

	virtual void preMult(const Matrix& mat)=0;// 左乘	
	virtual void postMult(const Matrix& mat) =0;// 右乘

};
class OSG_EXPORT MatrixTransform : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformMatrix>
{
    public :


        MatrixTransform();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        MatrixTransform(const MatrixTransform&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        MatrixTransform(const Matrix& matix);

        META_Node(osg, MatrixTransform);

        virtual IVBF_SGNodeGroupTransformMatrix* asMatrixTransform() { return this; }
        virtual const IVBF_SGNodeGroupTransformMatrix* asMatrixTransform() const { return this; }


        // 设置/获取变换矩阵
        void setMatrix(const Matrix& mat) { _matrix = mat; _inverseDirty=true; dirtyBound(); }
        inline const Matrix& getMatrix() const { return _matrix; }

        // 左乘
        void preMult(const Matrix& mat) { _matrix.preMult(mat); _inverseDirty=true; dirtyBound(); }
        
        // 右乘
        void postMult(const Matrix& mat)  { _matrix.postMult(mat); _inverseDirty=true; dirtyBound(); }
    
        /** Get the inverse matrix. */
        inline const Matrix& getInverseMatrix() const
        {
            if (_inverseDirty)
            {
                _inverse.invert(_matrix);
                _inverseDirty = false;
            }
            return _inverse;
        }

        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const;

        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const;


    protected :
    
        virtual ~MatrixTransform();
        
        Matrix                              _matrix;
        mutable Matrix                      _inverse;
        mutable bool                        _inverseDirty;


};

}

#endif
