#pragma once

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include "VBF_FadeSwitch.h"

namespace osg {
	class VBF_GLAUX_EXPORT FadeLOD : public FadeSwitch
	{
	public :
		FadeLOD();
		FadeLOD(const FadeLOD&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(osg, FadeLOD);

		typedef osg::BoundingSphere::vec_type vec_type;
		typedef osg::BoundingSphere::value_type value_type;

		virtual FadeSwitch* asFadeLOD() { return this; }
		virtual const FadeSwitch* asFadeLOD() const { return this; }

		inline const vec_type& getCenter() const { return getBound().center(); }
		float getDistanceToEye() { return m_fDistToEye; }

		// 当节点到视点的距离进入fDist范围内就显示，即LOD中的max
		virtual bool addChild(IVBF_SGNode *child, float fMin, float fMax);
		virtual void traverse(NodeVisitor& nv);

		typedef std::pair<float,float>  MinMaxPair;
		typedef std::vector<MinMaxPair> RangeList;

	protected:
		virtual ~FadeLOD() {}

		RangeList _rangeList;

		float		m_fDistToEye;
		int			m_iRangeNumPrev;
		int			m_iRangeNum;
	};
}
