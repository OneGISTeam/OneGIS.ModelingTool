#ifndef OSGEARTH_CLAMPABLE_NODE_H
#define OSGEARTH_CLAMPABLE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDepthOffset.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

class CVBFO_SGNodeMap;

// 围墙遮挡覆盖地表节点（围墙遮挡覆盖）
// 用法: 创建该节点并添加到场景图的任何位置，则该节点的子图被覆盖到地表上(clamped)
class OSGEARTH_EXPORT CVBFO_SGNodeOverlayClampable : public CVBFO_SGNodeOverlay
{
public:
    CVBFO_SGNodeOverlayClampable( CVBFO_SGNodeMap* mapNode, bool clamped =true );

public:
    // 深度偏移属性. Clamped geometry自动的进行深度偏移，以减轻ZBuffer冲突
    CVBF_DepthOffsetOptions& depthOffset() { dirtyDepthOffsetOptions(); return _do; }
    const CVBF_DepthOffsetOptions& depthOffset() const { return _do; }
        
    // 根据对子图几何数据（subgraph's geometry）的分析，自动选择一个最小的偏移（bias） bias based on an analysis
    void setAutoCalculateDepthOffset();

    // 向后兼容函数
    void setClamped( bool value ) { setActive(value); }
    bool getClamped() const { return getActive(); }

public: // osg::Node

    virtual osg::BoundingSphere computeBound() const;

    virtual void traverse(osg::NodeVisitor& nv);

protected:
    virtual ~CVBFO_SGNodeOverlayClampable() { }

	void init();
    void dirtyDepthOffsetOptions();
    void applyDepthOffsetOptions();

protected:
    bool								_autoBias;
    mutable ref_ptr<osg::Uniform>	_biasUniform;
    mutable ref_ptr<osg::Uniform>	_rangeUniform;

    mutable CVBF_DepthOffsetOptions			_do;
    bool								_doDirty;
};



#endif // OSGEARTH_CLAMPABLE_NODE_H
