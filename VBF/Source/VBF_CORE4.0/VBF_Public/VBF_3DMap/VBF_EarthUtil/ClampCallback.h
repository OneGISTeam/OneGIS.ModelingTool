#ifndef OSGEARTHUTIL_CLAMPCALLBACK
#define OSGEARTHUTIL_CLAMPCALLBACK

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_3DMap/VBF_Terrain/NodeUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

#include <VBF_3DMap/VBF_EarthUtil/Common>

//!!!�������ΪCVBF_NodeCallbackClampToGround

namespace osgEarth { namespace Util
{	

	// ���ر������������MatrixTransform��Geode���������MatrixTransform��ʹ�������ر��������Geode��ʹ���еĶ������ر�
	class OSGEARTHUTIL_EXPORT ClampCallback : public osg::NodeCallback
	{
	public:

		// ������ʾҪ�����Ľڵ㣨һ��Ϊ���Σ�
        ClampCallback(osg::IVBF_SGNode* terrainNode = NULL);

        virtual ~ClampCallback() { }

		 // ����/��ȡ���Σ��������ڵ�
        void setTerrainNode(osg::IVBF_SGNode* terrainNode);
        osg::IVBF_SGNode* getTerrainNode() const { return _terrainNode.get(); }

     
		// ����/��ȡ����world's up������ƫ������Ϊ0ʱ��ȫ���ر������ر�ĸ߶�ΪOffset��
        double getOffset() const { return _offset;}
        void setOffset(double offset);

         // Sets/Get the intersection mask to use when clamping
        void setIntersectionMask(unsigned int intersectionMask);
        unsigned int getIntersectionMask() const;

		virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

	private:

        bool clamp(const osg::Vec3d& pos, osg::Vec3d& out) const;
        bool clampGeometry(osg::Geometry* geom, const osg::Matrixd& localToWorld, const osg::Matrixd& worldToLocal) const;

        unsigned int _intersectionMask;

     	observer_ptr<osg::CVBF_SGNodeGroupCoordSys> _csn;

        ref_ptr< osg::IVBF_SGNode > _terrainNode;

        int _lastCulledFrame;

        double _offset;


	};

} } // namespace osgEarth::Util

#endif //OSGEARTHUTIL_CLAMPCALLBACK
