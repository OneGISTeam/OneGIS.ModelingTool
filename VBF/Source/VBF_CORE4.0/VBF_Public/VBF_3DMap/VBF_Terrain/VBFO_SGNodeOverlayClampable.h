#ifndef OSGEARTH_CLAMPABLE_NODE_H
#define OSGEARTH_CLAMPABLE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDepthOffset.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

class CVBFO_SGNodeMap;

// Χǽ�ڵ����ǵر�ڵ㣨Χǽ�ڵ����ǣ�
// �÷�: �����ýڵ㲢��ӵ�����ͼ���κ�λ�ã���ýڵ����ͼ�����ǵ��ر���(clamped)
class OSGEARTH_EXPORT CVBFO_SGNodeOverlayClampable : public CVBFO_SGNodeOverlay
{
public:
    CVBFO_SGNodeOverlayClampable( CVBFO_SGNodeMap* mapNode, bool clamped =true );

public:
    // ���ƫ������. Clamped geometry�Զ��Ľ������ƫ�ƣ��Լ���ZBuffer��ͻ
    CVBF_DepthOffsetOptions& depthOffset() { dirtyDepthOffsetOptions(); return _do; }
    const CVBF_DepthOffsetOptions& depthOffset() const { return _do; }
        
    // ���ݶ���ͼ�������ݣ�subgraph's geometry���ķ������Զ�ѡ��һ����С��ƫ�ƣ�bias�� bias based on an analysis
    void setAutoCalculateDepthOffset();

    // �����ݺ���
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
