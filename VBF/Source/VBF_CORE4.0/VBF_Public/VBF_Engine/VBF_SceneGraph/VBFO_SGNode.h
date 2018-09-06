#ifndef VBF_SG_NODE_H
#define VBF_SG_NODE_H 1


#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>

namespace osg
{
	class OSG_EXPORT CVBF_SGNode:public IVBF_SGNodeImpl<IVBF_SGNode>
	{
	public:
		CVBF_SGNode()// IE¿ÉÄÜ´íÎó
		{
		}

		CVBF_SGNode(const CVBF_SGNode& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeImpl<IVBF_SGNode>(cs,copyop)
		{
		}

		META_Node(osg, CVBF_SGNode);
/*
		virtual CVBF_Object* cloneType() const { return new Node(); }
		virtual CVBF_Object* clone(const CopyOp& copyop) const { return new Node(*this,copyop); }
		virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const Node*>(obj)!=NULL; }
		virtual const char* libraryName() const { return "osg"; }
		virtual const char* className() const { return "Node"; }
		*/
	};	


	

}


#endif
