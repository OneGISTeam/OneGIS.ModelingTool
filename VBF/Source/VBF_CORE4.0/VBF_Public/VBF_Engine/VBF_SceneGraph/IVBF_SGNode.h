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

/** 父节点的列表，每个父节点是一个Group。*/
typedef std::vector<IVBF_SGNodeGroup*> CVBF_NodeParentList;

/** IVBF_SGNodeImpl指针的vector， 用于描述从根节点到子孙后代的路径（path） 。*/
typedef std::vector< IVBF_SGNode* > CVBF_SGNodePath;

/** NodePath的vector, 典型的应用是描述从节点到可能的根节点的所有的路径。*/
typedef std::vector< CVBF_SGNodePath > NodePathList;

/** Matrix的vector，矩阵变化的列表*/
typedef std::vector< Matrix > MatrixList;

class IVBF_SGNode:public CVBF_Object
{

public:
	typedef unsigned int NodeMask;



	typedef std::vector<std::string> DescriptionList; //用于描述节点的字符串列表


	/** 回调函数允许覆盖缺省的计算包围体的方法。*/
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


	// 类型转换，如果是T类型，则返回T*,否则返回0。等同于dynamic_cast<T*>()。
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



	// 4、与遍历操作相关的内容

    virtual void accept(NodeVisitor& nv)=0;

    /** 向上遍历 : 调用父亲的accept方法 with NodeVisitor.*/
    virtual void ascend(NodeVisitor& nv)=0;

    /** 向下遍历 : 调用孩子的accept方法 with NodeVisitor.*/
    virtual void traverse(NodeVisitor& nv)=0;   


	// 5、与父子关系有关的内容

 
    virtual const CVBF_NodeParentList& getParents() const =0; //获取节点的父节点列表
    virtual CVBF_NodeParentList getParents()=0; // 获取父节点列表的拷贝，使用拷贝可以防止父节点列表被更改

	virtual IVBF_SGNodeGroup* getParent(unsigned int i)=0;   // 获取第i个父节点
	virtual const IVBF_SGNodeGroup* getParent(unsigned int i) const=0;

    virtual unsigned int getNumParents() const=0; //获取父节点的个数

    /** 获取父节点路径的列表（父节点路径可能有多个）。可选参数IVBF_SGNodeImpl* haltTraversalAtNode允许在指定的节点处停止遍历。*/
    virtual NodePathList getParentalNodePaths(osg::IVBF_SGNode* haltTraversalAtNode=0) const=0;

    virtual void addParent(osg::IVBF_SGNodeGroup* node)=0; 
    virtual void removeParent(osg::IVBF_SGNodeGroup* node)=0; 

	// 5.1、与矩阵变换路径有关的内容

    /** 获取把节点从局部坐标系变换到世界坐标系的矩阵列表。可选参数IVBF_SGNodeImpl* haltTraversalAtNode允许在指定的节点处停止遍历。*/
    virtual MatrixList getWorldMatrices(const osg::IVBF_SGNode* haltTraversalAtNode=0) const=0;

	// 6、与节点回调函数有关的内容

	// 6.1 更新回调

	/** 设置/获取/添加/移除Update回调函数，在遍历更新的时候回调。*/
	virtual void setUpdateCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getUpdateCallback()=0;
	virtual const NodeCallback* getUpdateCallback() const=0;
    virtual void addUpdateCallback(NodeCallback* nc) =0;
	virtual void removeUpdateCallback(NodeCallback* nc) =0;
		
    /** 获取需要更新遍历的子节点的个数。这些子节点关联了Update Callback或其子节点关联了Update Callback。*/
    virtual unsigned int getNumChildrenRequiringUpdateTraversal() const=0;
	virtual void setNumChildrenRequiringUpdateTraversal(unsigned int num)=0;


  

	// 6.2 事件回调

	/** 设置/获取event回调函数，在遍历event的时候回调。*/
	virtual void setEventCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getEventCallback() =0;
	virtual const NodeCallback* getEventCallback() const=0;
	virtual void addEventCallback(NodeCallback* nc) =0;
	virtual void removeEventCallback(NodeCallback* nc)=0; 
	
	/** 获取需要Event遍历的子节点的个数。这些子节点关联了Event Callback或其子节点关联了Event Callback。*/
	virtual unsigned int getNumChildrenRequiringEventTraversal() const=0; 
    virtual void setNumChildrenRequiringEventTraversal(unsigned int num)=0;

 	// 6.3 裁剪回调

    /** 设置/获取Cull回调函数，在遍历裁剪的时候回调。*/
	virtual void setCullCallback(NodeCallback* nc)=0;
	virtual NodeCallback* getCullCallback()=0;
	virtual const NodeCallback* getCullCallback() const =0;

	/** 添加Cull回调函数，节点的Cull回调函数不存在时设置它，存在时把它嵌套到已经存在的Cull回调函数。 */
    virtual void addCullCallback(NodeCallback* nc) =0;
		 
 	/** 移除节点的Cull回调函数（即使该函数被嵌套了也适用），找不到该Cull回调函数也不返回错误。 */
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

    /** 获取是或含有OccluderNode的子节点的个数。*/
    virtual unsigned int getNumChildrenWithOccluderNodes() const =0;
    virtual void setNumChildrenWithOccluderNodes(unsigned int num)=0;
  
    /** 是否包含遮光板节点。如果该节点是OccluderNode或该节点的子图是OccluderNode返回true。*/
    virtual bool containsOccluderNodes() const=0;

        

 

	// 7、与节点Mask有关的内容

    /** 描述节点的一系列位标志，默认值为0xffffffff (all bits set)。 通常用于场景图遍历的过程中。
	* osg::NodeVisitor做一个TraversalMask和NodeMask的AND位操作，以决定该节点是否被处理/遍历。
    * 例如, 某节点的NodeMask值为0x02 (仅第2位为1)，osg::Camera 的CullMask为0x4 (第2位为0)，
	* 在遍历裁剪过程中，TraversalMask的值从Camera's CullMask获得，因此，该节点及其子节点将被略过并被认为已经裁剪过（ "culled"）不渲染。
    * 反之, 如果osg::Camera的CullMask为0x3 (第2位为1)， 将处理该节点并检查其子节点。
	*/

	/** 设置/获取节点Mask*/
	virtual void setNodeMask(NodeMask nm)=0;
	virtual NodeMask getNodeMask() const =0;

	// 8、与状态集合有关的内容

	virtual void setStateSet(osg::StateSet* stateset)=0;
	virtual osg::StateSet* getOrCreateStateSet()=0;
	virtual osg::StateSet* getStateSet()=0;
	virtual const osg::StateSet* getStateSet() const=0;


	// 9、与节点描述信息有关的内容


	/** 设置获取描述节点的字符串列表。*/
	virtual void setDescriptions(const DescriptionList& descriptions) = 0;
	virtual DescriptionList& getDescriptions()= 0;
	virtual const DescriptionList& getDescriptions() const= 0;


	/** 获取描述节点的第i个字符串列表。*/
	virtual const std::string& getDescription(unsigned int i) const= 0;
	virtual std::string& getDescription(unsigned int i)= 0;
	/** 获取描述节点的字符串列表的个数。*/
	virtual unsigned int getNumDescriptions() const= 0;
	/** 添加一个描述节点的字符串列表。*/
	virtual void addDescription(const std::string& desc)= 0;

	// 10、与节点包围球/盒有关的内容


	/** 设置/获取初始的包围体。*/
	virtual void setInitialBound(const osg::BoundingSphere& bsphere)=0;
	virtual const BoundingSphere& getInitialBound() const =0;

	/** 把节点的包围球标记为dirty，以便在下次调用getBound（）函数时强制计算包围球。*/
    virtual void dirtyBound()=0;

    /** 获取节点的包围球，当包围球标记为dirty时，先计算包围球。*/
    virtual const BoundingSphere& getBound() const=0;
    

    /** 计算包围球（包含节点的geometry或children）。当通过dirtyBound()把包围球标记为dirty时，该方法被getBound()自动调用。*/
    virtual BoundingSphere computeBound() const=0;

  

	/** 设置/获取计算包围体的回调函数，该函数覆盖缺省的计算包围体的方法*/
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

// 计算模型局部坐标系到世界坐标系的变换矩阵（累积节点路径上的所有局部到世界矩阵）
extern OSG_EXPORT Matrix computeLocalToWorld(const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// 计算模型世界坐标系到局部坐标系的变换矩阵（累积节点路径上的所有世界到局部矩阵）
extern OSG_EXPORT Matrix computeWorldToLocal(const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// 计算模型局部坐标系到眼坐标系的变换矩阵（累积节点路径上的所有局部到世界矩阵，并乘modelview矩阵）
extern OSG_EXPORT Matrix computeLocalToEye(const Matrix& modelview, const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);

// 计算模型眼坐标系到局部坐标系的变换矩阵（累积节点路径上的所有世界到局部矩阵，并乘modelview逆矩阵）
extern OSG_EXPORT Matrix computeEyeToLocal(const Matrix& modelview, const osg::CVBF_SGNodePath& nodePath, bool ignoreCameras = true);


}
#endif
