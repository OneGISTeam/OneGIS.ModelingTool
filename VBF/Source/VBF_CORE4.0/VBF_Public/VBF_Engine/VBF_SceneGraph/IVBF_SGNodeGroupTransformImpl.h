
#ifndef OSG_TRANSFORM
#define OSG_TRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

#include <Types/VBF_Matrix.h>

#ifndef GL_RESCALE_NORMAL
#define GL_RESCALE_NORMAL       0x803A
#endif

#ifndef GL_NORMALIZE
#define GL_NORMALIZE            0x0BA1
#endif

namespace osg {

/** Transform�ڵ���һ����ڵ㣬���е��ӽڵ�ͨ��һ��4x4 matrix��������ϵ�任��
  * �����ڰѶ����ڳ����з���һ�����ʵ�λ�á�
  *
  * Transform itself does not provide set/get functions, only the interface
  * for defining what the 4x4 transformation is.  Subclasses, such as
  * MatrixTransform and PositionAttitudeTransform support the use of an
  * osg::Matrix or a osg::Vec3/osg::Quat respectively.
  *
  * Note: If the transformation matrix scales the subgraph then the normals
  * of the underlying geometry will need to be renormalized to be unit
  * vectors once more.  This can be done transparently through OpenGL's 
  * use of either GL_NORMALIZE and GL_RESCALE_NORMAL modes. For further
  * background reading see the glNormalize documentation in the OpenGL
  * Reference Guide (the blue book). To enable it in the OSG, you simply
  * need to attach a local osg::StateSet to the osg::Transform, and set
  * the appropriate mode to ON via
  *   stateset->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
*/



template<class T>
class IVBF_SGNodeGroupTransformImpl : public IVBF_SGNodeGroupImpl<T>
{
private:
    typedef osg::IVBF_SGNodeGroupImpl<T> _Base;
    public :

        IVBF_SGNodeGroupTransformImpl();
        IVBF_SGNodeGroupTransformImpl(const IVBF_SGNodeGroupTransformImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

 //       META_Node(osg, Transform);

        virtual IVBF_SGNodeGroupTransform* asTransform() { return this; }
        virtual const IVBF_SGNodeGroupTransform* asTransform() const { return this; }

        
        /** ���ñ任��ReferenceFrame������������ĸ�reference frame����������ھ��������ܡ�
		  * RELATIVE_RF����Բο���ܣ���Ĭ��ֵ��
          * ע��: ��ReferenceFrame����ΪABSOLUTE_RF���ѱ任��CullingActive��־����Ϊfalse
		  ���������ĸ��ڵ�ģ����Ӷ���ֹ�ü���������parents��
		  * Ϊ�˷�ֹ���ʵ���ɸѡ�����Ǳ�Ҫ�ģ������������ͼ�о��Ա任�������Ӱ��ɸѡ��ʱ�䡣
          * ��ˣ�������ڳ����Ķ���ʹ�þ��Ա任������HUD��
          
          * ABSOLUTE_RF_INHERIT_VIEWPOINT��ABSOLUTE_RF���ƣ���������������
          * to ʹ�ø��ڵ���ӵ�λ��in world coordinates
          * as its local viewpoint in the new coordinates frame.  This is useful for
          * Render to texture Cameras that wish to use the main views LOD range computation 
          * (which uses the viewpoint rather than the eye point) rather than use the local
          * eye point defined by the this Transforms' absolute view matrix.
        */
        virtual void setReferenceFrame(IVBF_SGNodeGroupTransform::ReferenceFrame rf);
        
        virtual IVBF_SGNodeGroupTransform::ReferenceFrame getReferenceFrame() const { return _referenceFrame; }



        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==T::RELATIVE_RF)
            {
                return false;
            }
            else // absolute
            {
                matrix.makeIdentity();
                return true;
            }
        }
        
        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==T::RELATIVE_RF)
            {
                return false;
            }
            else // absolute
            {
                matrix.makeIdentity();
                return true;
            }
        }

        /** Overrides Group's computeBound. There is no need to override in subclasses from osg::Transform
          * since this computeBound() uses the underlying matrix (calling computeMatrix if required).
        */
        virtual BoundingSphere computeBound() const;

    protected :
    
        virtual ~IVBF_SGNodeGroupTransformImpl();
               
        IVBF_SGNodeGroupTransform::ReferenceFrame    _referenceFrame;

};



}
#include "IVBF_SGNodeGroupTransformImpl.inl"


#endif
