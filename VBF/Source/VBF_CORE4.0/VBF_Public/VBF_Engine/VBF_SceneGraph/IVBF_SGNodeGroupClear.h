#ifndef IVBF_SG_NODE_GROUP_CLEAR_H
#define IVBF_SG_NODE_GROUP_CLEAR_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

class IVBF_SGNodeGroupClear : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupClear(){}
	IVBF_SGNodeGroupClear(const IVBF_SGNodeGroupClear& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupClear(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	/** Enable/disable clearing via glClear. */
	virtual void setRequiresClear(bool requiresClear)=0;
	virtual bool getRequiresClear() const =0;

	/** Sets the clear color. */
	virtual void setClearColor(const Vec4& color)=0;
	virtual const Vec4& getClearColor() const=0;

	/** Set the clear mask used in glClear(..).
	* Defaults to GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT. */
	virtual void setClearMask(GLbitfield mask)=0;
	virtual GLbitfield getClearMask() const =0;
};


OSG_EXPORT IVBF_SGNodeGroupClear* VBF_CreateSGNodeGroupClear() ;
OSG_EXPORT IVBF_SGNodeGroupClear* VBF_CreateSGNodeGroupClear(const IVBF_SGNodeGroupClear& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
