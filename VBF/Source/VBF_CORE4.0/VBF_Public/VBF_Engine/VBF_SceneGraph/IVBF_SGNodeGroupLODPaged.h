#ifndef IVBF_SG_NODE_GROUP_LOD_PAGED_H
#define IVBF_SG_NODE_GROUP_LOD_PAGED_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLOD.h>

namespace osg {


class IVBF_SGNodeGroupLODPaged : public IVBF_SGNodeGroupLOD
{
public:
	IVBF_SGNodeGroupLODPaged(){}
	IVBF_SGNodeGroupLODPaged(const IVBF_SGNodeGroupLODPaged& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupLOD(cs,copyop) {}
	explicit IVBF_SGNodeGroupLODPaged(bool threadSafeRefUnref):IVBF_SGNodeGroupLOD(threadSafeRefUnref){}

	// 添加/移除子节点
    virtual bool addChild(IVBF_SGNode *child)=0;
    virtual bool addChild(IVBF_SGNode *child, float min, float max)=0;
    virtual bool addChild(IVBF_SGNode *child, float min, float max,const std::string& filename, float priorityOffset=0.0f, float priorityScale=1.0f)=0;
	virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove=1)=0;

    // 设置数据库选项，装载子节点时用到
    virtual void setDatabaseOptions(CVBF_Referenced* options)=0;
    virtual CVBF_Referenced* getDatabaseOptions()=0;
    virtual const CVBF_Referenced* getDatabaseOptions() const=0;

	// 设置数据库路径。子节点的文件名（filenames）在此路径下
	virtual void setDatabasePath(const std::string& path)=0;
	virtual const std::string& getDatabasePath() const=0;


	// 设置/获取子节点的文件名
	virtual void setFileName(unsigned int childNo, const std::string& filename)=0;
	virtual const std::string& getFileName(unsigned int childNo) const=0;
	virtual unsigned int getNumFileNames() const=0;

	// 设置/获取子节点的优先级
	virtual void setPriorityOffset(unsigned int childNo, float priorityOffset)=0;
	virtual float getPriorityOffset(unsigned int childNo) const=0;
	virtual unsigned int getNumPriorityOffsets() const=0;

	virtual void setPriorityScale(unsigned int childNo, float priorityScale)=0;
	virtual float getPriorityScale(unsigned int childNo) const =0;
	virtual unsigned int getNumPriorityScales() const=0;


	virtual void setTimeStamp(unsigned int childNo, double timeStamp) =0;
	virtual double getTimeStamp(unsigned int childNo) const=0;
	virtual unsigned int getNumTimeStamps() const =0;

	virtual void setFrameNumber(unsigned int childNo, unsigned int frameNumber)=0;
	virtual unsigned getFrameNumber(unsigned int childNo) const=0;
	virtual unsigned int getNumFrameNumbers() const=0;


	/** Return the DatabaseRequest object used by the DatabasePager to keep track of file load requests 
	* being carried on behalf of the DatabasePager.
	* Note, in normal OSG usage you should not set this value yourself, as this will be managed by 
	* the osgDB::DatabasePager.*/
	virtual ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo)=0;
	virtual const ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) const=0;


	/** Set the frame number of the last time that this PageLOD node was traversed.
	* Note, this frame number is automatically set by the traverse() method for all traversals (update, cull etc.). 
	*/
	virtual void setFrameNumberOfLastTraversal(unsigned int frameNumber)=0;
	virtual unsigned int getFrameNumberOfLastTraversal() const=0;


	/** Set the number of children that the PagedLOD must keep around, even if they are older than their expiry time.*/
	virtual void setNumChildrenThatCannotBeExpired(unsigned int num) =0;
	virtual unsigned int getNumChildrenThatCannotBeExpired() const =0;

	/** Set wether you want to disable the paging in of external nodes.*/
	virtual void setDisableExternalChildrenPaging(bool flag)=0;
	virtual bool getDisableExternalChildrenPaging() const =0;



	/** Remove the children from the PagedLOD which haven't been visited since specified expiry time and expiry frame number.
	* The removed children are added to the removeChildren list passed into the method,
	* this allows the children to be deleted later at the caller's discretion.
	* Return true if children are removed, false otherwise. */
	virtual bool removeExpiredChildren(double expiryTime, unsigned int expiryFrame, NodeList& removedChildren)=0;


};

OSG_EXPORT IVBF_SGNodeGroupLODPaged* VBF_CreateSGNodeGroupLODPaged() ;
OSG_EXPORT IVBF_SGNodeGroupLODPaged* VBF_CreateSGNodeGroupLODPaged(const IVBF_SGNodeGroupLODPaged& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}


#endif
