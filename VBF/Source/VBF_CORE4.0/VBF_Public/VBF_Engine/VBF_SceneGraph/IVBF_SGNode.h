#ifndef IVBF_SG_NODE_H
#define IVBF_SG_NODE_H 1

#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <Types/VBF_BoundingSphere.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>


namespace osgTerrain {
class Terrain;
}
namespace osg 
{
class NodeVisitor;
class IVBF_SGNodeGroup;
class IVBF_SGNodeGroupTransform;
class IVBF_SGNode;
class IVBF_SGNodeGroupSwitch;
class IVBF_SGNodeGeometry;

/** ���ڵ���б�ÿ�����ڵ���һ��Group��*/
typedef std::vector<IVBF_SGNodeGroup*> CVBF_NodeParentList;

/** IVBF_SGNodeImplָ���vector�� ���������Ӹ��ڵ㵽��������·����path�� ��*/
typedef std::vector< IVBF_SGNode* > CVBF_SGNodePath;

/** NodePath��vector, ���͵�Ӧ���������ӽڵ㵽���ܵĸ��ڵ�����е�·����*/
typedef std::vector< CVBF_SGNodePath > NodePathList;

/** Matrix��vector������仯���б�*/
typedef std::vector< Matrix > MatrixList;

class IVBF_SGNode:public CVBF_Object
{

public:
	typedef unsigned int NodeMask;



	typedef std::vector<std::string> DescriptionList; //���������ڵ���ַ����б�


	/** �ص�����������ȱʡ�ļ����Χ��ķ�����*/
	struct ComputeBoundingSphereCallback : public osg::CVBF_Object
	{
		ComputeBoundingSphereCallback() {}

		ComputeBoundingSphereCallback(const ComputeBoundingSphereCallback&,const CopyOp&) {}

		META_Object(osg,ComputeBoundingSphereCallback);

		virtual BoundingSphere computeBound(const osg::IVBF_SGNode&) const { return BoundingSphere(); }
	};

public:
	IVBF_SGNode(){}
	IVBF_SGNode(const IVBF_SGNode& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):CVBF_Object(cs,copyop) {}
	explicit IVBF_SGNode(bool threadSafeRefUnref):CVBF_Object(threadSafeRefUnref){}


	// ����ת���������T���ͣ��򷵻�T*,���򷵻�0����ͬ��dynamic_cast<T*>()��
	virtual IVBF_SGNodeGroup* asGroup() { return 0; }
	virtual const IVBF_SGNodeGroup* asGroup() const { return 0; }

	virtual IVBF_SGNodeGroupTransform* asTransform() { return 0; }
	virtual const IVBF_SGNodeGroupTransform* asTransform() const { return 0; }

	virtual IVBF_SGNodeGroupSwitch* asSwitch() { return 0; }
    virtual const IVBF_SGNodeGroupSwitch* asSwitch() const { return 0; }


	virtual IVBF_SGNodeGeometry* asGeode() { return 0; }
    virtual const IVBF_SGNodeGeometry* asGeode() const { return 0; }

	virtual osgTerrain::Terrain* asTerrain() { return 0; }
    virtual const osgTerrain::Terrain* asTerrain() const { return 0; }



	// 4�������������ص�����

    virtual void accept(NodeVisitor& nv)=0;

    /** ���ϱ��� : ���ø��׵�accept���� with NodeVisitor.*/
    virtual void ascend(NodeVisitor& nv)=0;

    /** ���±��� : ���ú��ӵ�accept���� with NodeVisitor.*/
    virtual void traverse(NodeVisitor& nv)=0;   


	// 5���븸�ӹ�ϵ�йص�����

 
    virtual const CVBF_NodeParentList& getParents() const =0; //��ȡ�ڵ�ĸ��ڵ��б�
    virtual CVBF_NodeParentList getParents()=0; // ��ȡ���ڵ��б�Ŀ�����ʹ�ÿ������Է�ֹ���ڵ��б�����

	virtual IVBF_SGNodeGroup* getParent(unsigned int i)=0;   // ��ȡ��i�����ڵ�
	virtual const IVBF_SGNodeGroup* getParent(unsigned int i) const=0;

    virtual unsigned int getNumParents() const=0; //��ȡ���ڵ�ĸ���

    /** ��ȡ���ڵ�·�����б����ڵ�·�������ж��������ѡ����IVBF_SGNodeImpl* haltTraversalAtNode������ָ���Ľڵ㴦ֹͣ������*/
    virtual NodePathList getParentalNodePaths(osg::IVBF_SGNode* haltTraversalAtNode=0) const=0;

    virtual void addParent(osg::IVBF_SGNodeGroup* node)=0; 
    virtual void removeParent(osg::IVBF_SGNodeGroup* node)=0; 

	// 5.1�������任·���йص�����

    /** ��ȡ�ѽڵ�Ӿֲ�����ϵ�任����������ϵ�ľ����б���ѡ����IVBF_SGNodeImpl* haltTraversalAtNode������ָ���Ľڵ㴦ֹͣ������*/
    virtual MatrixList getWorldMatrices(const osg::IVBF_SGNode* haltTraversalAtNode=0) const=0;

	// 6����ڵ�ص������йص�����

	// 6.1 ���»ص�

	/** ����/��ȡ/���/�Ƴ�Update�ص��������ڱ������µ�ʱ��ص���*/
	virtual void setUpdateCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getUpdateCallback()=0;
	virtual const NodeCallback* getUpdateCallback() const=0;
    virtual void addUpdateCallback(NodeCallback* nc) =0;
	virtual void removeUpdateCallback(NodeCallback* nc) =0;
		
    /** ��ȡ��Ҫ���±������ӽڵ�ĸ�������Щ�ӽڵ������Update Callback�����ӽڵ������Update Callback��*/
    virtual unsigned int getNumChildrenRequiringUpdateTraversal() const=0;
	virtual void setNumChildrenRequiringUpdateTraversal(unsigned int num)=0;


  

	// 6.2 �¼��ص�

	/** ����/��ȡevent�ص��������ڱ���event��ʱ��ص���*/
	virtual void setEventCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getEventCallback() =0;
	virtual const NodeCallback* getEventCallback() const=0;
	virtual void addEventCallback(NodeCallback* nc) =0;
	virtual void removeEventCallback(NodeCallback* nc)=0; 
	
	/** ��ȡ��ҪEvent�������ӽڵ�ĸ�������Щ�ӽڵ������Event Callback�����ӽڵ������Event Callback��*/
	virtual unsigned int getNumChildrenRequiringEventTraversal() const=0; 
    virtual void setNumChildrenRequiringEventTraversal(unsigned int num)=0;

 	// 6.3 �ü��ص�

    /** ����/��ȡCull�ص��������ڱ����ü���ʱ��ص���*/
	virtual void setCullCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getCullCallback()=0;
	virtual const NodeCallback* getCullCallback() const =0;

	/** ���Cull�ص��������ڵ��Cull�ص�����������ʱ������������ʱ����Ƕ�׵��Ѿ����ڵ�Cull�ص������� */
    virtual void addCullCallback(NodeCallback* nc) =0;
		 
 	/** �Ƴ��ڵ��Cull�ص���������ʹ�ú�����Ƕ����Ҳ���ã����Ҳ�����Cull�ص�����Ҳ�����ش��� */
    virtual void removeCullCallback(NodeCallback* nc)=0;
		
    /** Set/get the view frustum/small feature culling of this node to be active or inactive.*/
    virtual void setCullingActive(bool active)=0;
    virtual bool getCullingActive() const =0;

    /** Get the number of Children of this node which have culling disabled.*/
    virtual unsigned int getNumChildrenWithCullingDisabled() const=0;
	virtual void setNumChildrenWithCullingDisabled(unsigned int num)=0;

    /** Return true if this node can be culled by view frustum, occlusion or small feature culling during the cull traversal.
        * Note, returns true only if no children have culling disabled, and the local _cullingActive flag is true.*/
    virtual bool isCullingActive() const =0;

    /** ��ȡ�ǻ���OccluderNode���ӽڵ�ĸ�����*/
    virtual unsigned int getNumChildrenWithOccluderNodes() const =0;
    virtual void setNumChildrenWithOccluderNodes(unsigned int num)=0;
  
    /** �Ƿ�����ڹ��ڵ㡣����ýڵ���OccluderNode��ýڵ����ͼ��OccluderNode����true��*/
    virtual bool containsOccluderNodes() const=0;

        

 

	// 7����ڵ�Mask�йص�����

    /** �����ڵ��һϵ��λ��־��Ĭ��ֵΪ0xffffffff (all bits set)�� ͨ�����ڳ���ͼ�����Ĺ����С�
	* osg::NodeVisitor��һ��TraversalMask��NodeMask��ANDλ�������Ծ����ýڵ��Ƿ񱻴���/������
    * ����, ĳ�ڵ��NodeMaskֵΪ0x02 (����2λΪ1)��osg::Camera ��CullMaskΪ0x4 (��2λΪ0)��
	* �ڱ����ü������У�TraversalMask��ֵ��Camera's CullMask��ã���ˣ��ýڵ㼰���ӽڵ㽫���Թ�������Ϊ�Ѿ��ü����� "culled"������Ⱦ��
    * ��֮, ���osg::Camera��CullMaskΪ0x3 (��2λΪ1)�� ������ýڵ㲢������ӽڵ㡣
	*/

	/** ����/��ȡ�ڵ�Mask*/
	virtual void setNodeMask(NodeMask nm)=0;
	virtual NodeMask getNodeMask() const =0;

	// 8����״̬�����йص�����

	virtual void setStateSet(osg::StateSet* stateset)=0;
	virtual osg::StateSet* getOrCreateStateSet()=0;
	virtual osg::StateSet* getStateSet()=0;
	virtual const osg::StateSet* getStateSet() const=0;


	// 9����ڵ�������Ϣ�йص�����


	/** ���û�ȡ�����ڵ���ַ����б�*/
	virtual void setDescriptions(const DescriptionList& descriptions) = 0;
	virtual DescriptionList& getDescriptions()= 0;
	virtual const DescriptionList& getDescriptions() const= 0;


	/** ��ȡ�����ڵ�ĵ�i���ַ����б�*/
	virtual const std::string& getDescription(unsigned int i) const= 0;
	virtual std::string& getDescription(unsigned int i)= 0;
	/** ��ȡ�����ڵ���ַ����б�ĸ�����*/
	virtual unsigned int getNumDescriptions() const= 0;
	/** ���һ�������ڵ���ַ����б�*/
	virtual void addDescription(const std::string& desc)= 0;

	// 10����ڵ��Χ��/���йص�����


	/** ����/��ȡ��ʼ�İ�Χ�塣*/
	virtual void setInitialBound(const osg::BoundingSphere& bsphere)=0;
	virtual const BoundingSphere& getInitialBound() const =0;

	/** �ѽڵ�İ�Χ����Ϊdirty���Ա����´ε���getBound��������ʱǿ�Ƽ����Χ��*/
    virtual void dirtyBound()=0;

    /** ��ȡ�ڵ�İ�Χ�򣬵���Χ����Ϊdirtyʱ���ȼ����Χ��*/
    virtual const BoundingSphere& getBound() const=0;
    

    /** �����Χ�򣨰����ڵ��geometry��children������ͨ��dirtyBound()�Ѱ�Χ����Ϊdirtyʱ���÷�����getBound()�Զ����á�*/
    virtual BoundingSphere computeBound() const=0;

  

	/** ����/��ȡ�����Χ��Ļص��������ú�������ȱʡ�ļ����Χ��ķ���*/
	virtual void setComputeBoundingSphereCallback(ComputeBoundingSphereCallback* callback)=0;
	virtual ComputeBoundingSphereCallback* getComputeBoundingSphereCallback()=0;
	virtual const ComputeBoundingSphereCallback* getComputeBoundingSphereCallback() const =0;

    //h00017
        virtual bool intersectWithRay(osg::Vec3 start,osg::Vec3 end,osg::Vec3& outPoint)
        {
            return false;
        }
    //h00017
};

OSG_EXPORT IVBF_SGNode* VBF_CreateSGNode() ;

// ����ģ�;ֲ�����ϵ����������ϵ�ı任�����ۻ��ڵ�·���ϵ����оֲ����������
extern OSG_EXPORT Matrix computeLocalToWorld(const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// ����ģ����������ϵ���ֲ�����ϵ�ı任�����ۻ��ڵ�·���ϵ��������絽�ֲ�����
extern OSG_EXPORT Matrix computeWorldToLocal(const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// ����ģ�;ֲ�����ϵ��������ϵ�ı任�����ۻ��ڵ�·���ϵ����оֲ���������󣬲���modelview����
extern OSG_EXPORT Matrix computeLocalToEye(const Matrix& modelview, const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// ����ģ��������ϵ���ֲ�����ϵ�ı任�����ۻ��ڵ�·���ϵ��������絽�ֲ����󣬲���modelview�����
extern OSG_EXPORT Matrix computeEyeToLocal(const Matrix& modelview, const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);


}
#endif
