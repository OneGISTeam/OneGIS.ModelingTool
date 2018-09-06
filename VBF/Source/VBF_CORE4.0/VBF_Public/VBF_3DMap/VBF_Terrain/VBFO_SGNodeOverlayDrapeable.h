#ifndef OSGEARTH_DRAPEABLE_NODE_H
#define OSGEARTH_DRAPEABLE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

class CVBFO_SGNodeMap;

// 贴地表节点（布帘覆盖）
// 用法: 创建该节点并添加到场景图的任何位置，则该节点的子图象布帘一样被覆盖到地表上(draped)
class OSGEARTH_EXPORT CVBFO_SGNodeOverlayDrapeable : public CVBFO_SGNodeOverlay
{
public:
    CVBFO_SGNodeOverlayDrapeable( CVBFO_SGNodeMap* mapNode, bool active =true );

    // 向后兼容函数
    void setDraped( bool value ) { setActive(value); }
    bool getDraped() const { return getActive(); }

protected:
    virtual ~CVBFO_SGNodeOverlayDrapeable() { }
};



#endif // OSGEARTH_DRAPEABLE_NODE_H
