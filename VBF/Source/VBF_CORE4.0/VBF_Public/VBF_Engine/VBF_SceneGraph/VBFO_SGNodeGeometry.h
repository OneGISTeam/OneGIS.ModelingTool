#ifndef VBF_SG_NODE_GEOMETRY_H
#define VBF_SG_NODE_GEOMETRY_H 1


#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometryImpl.h>

namespace osg
{

	class OSG_EXPORT CVBF_SGNodeGeometry : public IVBF_SGNodeGeometryImpl<IVBF_SGNodeGeometry>
	{
	public:
        CVBF_SGNodeGeometry();

        CVBF_SGNodeGeometry(const CVBF_SGNodeGeometry& geode,const CopyOp& copyop=CopyOp::SHALLOW_COPY);


		META_Node(osg, CVBF_SGNodeGeometry);
	};


}


#endif
