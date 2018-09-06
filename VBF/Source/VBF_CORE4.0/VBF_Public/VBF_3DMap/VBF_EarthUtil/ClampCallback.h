#ifndef OSGEARTHUTIL_CLAMPCALLBACK
#define OSGEARTHUTIL_CLAMPCALLBACK

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_3DMap/VBF_Terrain/NodeUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

#include <VBF_3DMap/VBF_EarthUtil/Common>

//!!!建议改名为CVBF_NodeCallbackClampToGround

namespace osgEarth { namespace Util
{	

	// 贴地表操作：可用于MatrixTransform和Geode，如果用于MatrixTransform则使对象贴地表，如果用于Geode则使所有的顶点贴地表
	class OSGEARTHUTIL_EXPORT ClampCallback : public osg::NodeCallback
	{
	public:

		// 参数表示要贴近的节点（一般为地形）
        ClampCallback(osg::IVBF_SGNode* terrainNode = NULL);

        virtual ~ClampCallback() { }

		 // 设置/获取地形（贴近）节点
        void setTerrainNode(osg::IVBF_SGNode* terrainNode);
        osg::IVBF_SGNode* getTerrainNode() const { return _terrainNode.get(); }

     
		// 设置/获取沿着world's up向量的偏移量（为0时完全贴地表，否则距地表的高度为Offset）
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
