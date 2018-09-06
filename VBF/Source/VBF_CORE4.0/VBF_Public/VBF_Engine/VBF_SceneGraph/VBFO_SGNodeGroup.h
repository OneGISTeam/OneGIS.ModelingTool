#ifndef VBF_SG_NODE_GROUP_H
#define VBF_SG_NODE_GROUP_H 1


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
namespace osg
{
	class OSG_EXPORT CVBF_SGNodeGroup : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroup>
	{
	public:
        CVBF_SGNodeGroup();

        CVBF_SGNodeGroup(const CVBF_SGNodeGroup& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY);
        virtual ~CVBF_SGNodeGroup();

		META_Node(osg, CVBF_SGNodeGroup);
	};
}
#endif
