#ifndef VBF_SG_NODE_GROUP_LOD_H
#define VBF_SG_NODE_GROUP_LOD_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>

namespace osg
{
	class OSG_EXPORT CVBF_SGNodeGroupLOD : public IVBF_SGNodeGroupLODImpl<IVBF_SGNodeGroupLOD>
	{
	public:
        CVBF_SGNodeGroupLOD();
        CVBF_SGNodeGroupLOD(const CVBF_SGNodeGroupLOD& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(osg, CVBF_SGNodeGroupLOD);
	};
}
#endif
