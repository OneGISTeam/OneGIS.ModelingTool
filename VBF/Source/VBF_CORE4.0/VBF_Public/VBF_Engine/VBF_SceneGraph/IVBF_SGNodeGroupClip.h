#ifndef IVBF_SG_NODE_GROUP_CLIP_H
#define IVBF_SG_NODE_GROUP_CLIP_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrClipPlane.h>

namespace osg {

class IVBF_SGNodeGroupClip : public IVBF_SGNodeGroup
{
public:
	typedef std::vector<ref_ptr<ClipPlane> > ClipPlaneList;

	IVBF_SGNodeGroupClip(){}
	IVBF_SGNodeGroupClip(const IVBF_SGNodeGroupClip& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupClip(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	enum ReferenceFrame
	{
		RELATIVE_RF,
		ABSOLUTE_RF
	};

	
	virtual void setReferenceFrame(ReferenceFrame rf)=0;

	virtual ReferenceFrame getReferenceFrame() const=0;


	/** Creates six clip planes corresponding to the given BoundingBox. */
	virtual void createClipBox(const BoundingBox& bb,unsigned int clipPlaneNumberBase=0)=0;

	/** Adds the clipplane. Returns true on success, and false if the plane
	* has already been added, or if clipplane is NULL. */
	virtual bool addClipPlane(ClipPlane* clipplane)=0;

	/** Removes the clipplane. Returns true on success, false if clipplane
	* isn't in this ClipNode.*/
	virtual bool removeClipPlane(ClipPlane* clipplane)=0;
	virtual bool removeClipPlane(unsigned int pos)=0;

	/** Returns the number of ClipPlanes. */
	virtual unsigned int getNumClipPlanes() const =0;


	/** Get ClipPlane at the given index position. */
	virtual ClipPlane* getClipPlane(unsigned int pos) =0;
	virtual const ClipPlane* getClipPlane(unsigned int pos) const =0;

	/** Set the ClipPlaneList. */
	virtual void setClipPlaneList(const ClipPlaneList& cpl) =0;
	virtual ClipPlaneList& getClipPlaneList() =0;
	virtual const ClipPlaneList& getClipPlaneList() const=0;

};

OSG_EXPORT IVBF_SGNodeGroupClip* VBF_CreateSGNodeGroupClip() ;
OSG_EXPORT IVBF_SGNodeGroupClip* VBF_CreateSGNodeGroupClip(const IVBF_SGNodeGroupClip& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
