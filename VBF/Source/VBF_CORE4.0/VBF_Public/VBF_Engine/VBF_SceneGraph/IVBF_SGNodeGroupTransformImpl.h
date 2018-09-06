
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

/** Transform节点是一个组节点，所有的子节点通过一个4x4 matrix进行坐标系变换。
  * 常用于把对象在场景中放置一个合适的位置。
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

        
        /** 设置变换的ReferenceFrame，是相对于它的父reference frame，还是相对于绝对坐标框架。
		  * RELATIVE_RF（相对参考框架）是默认值。
          * 注意: 把ReferenceFrame设置为ABSOLUTE_RF将把变换的CullingActive标志设置为false
		  （还有它的父节点的），从而禁止裁剪它和它的parents。
		  * 为了防止不适当的筛选，这是必要的，但是如果场景图中绝对变换很深，可能影响筛选的时间。
          * 因此，建议仅在场景的顶部使用绝对变换，用于HUD。
          
          * ABSOLUTE_RF_INHERIT_VIEWPOINT和ABSOLUTE_RF类似，除了增加了能力
          * to 使用父节点的视点位置in world coordinates
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
