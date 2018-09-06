#ifndef OSGEARTH_DRAPEABLE_NODE_H
#define OSGEARTH_DRAPEABLE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

class CVBFO_SGNodeMap;

// ���ر�ڵ㣨�������ǣ�
// �÷�: �����ýڵ㲢��ӵ�����ͼ���κ�λ�ã���ýڵ����ͼ����һ�������ǵ��ر���(draped)
class OSGEARTH_EXPORT CVBFO_SGNodeOverlayDrapeable : public CVBFO_SGNodeOverlay
{
public:
    CVBFO_SGNodeOverlayDrapeable( CVBFO_SGNodeMap* mapNode, bool active =true );

    // �����ݺ���
    void setDraped( bool value ) { setActive(value); }
    bool getDraped() const { return getActive(); }

protected:
    virtual ~CVBFO_SGNodeOverlayDrapeable() { }
};



#endif // OSGEARTH_DRAPEABLE_NODE_H
