#ifndef OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
#define OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD 1

#include "Common"
#include "MP_TileNode.h"
#include "MP_TileNodeRegistry.h"
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODPaged.h>

using namespace osgEarth;

// ��TileNodes���ӵ�����ͼ��ʱ��CMP_PagedLOD���Զ�ע��
class CMP_PagedLOD : public osg::PagedLOD
{
public:
	CMP_PagedLOD( CMP_TileNodeRegistry* liveTiles, CMP_TileNodeRegistry* deadTiles );
	virtual ~CMP_PagedLOD();

public: // osg::Group

    // ����Group�ķ�������Ϊ�˰�TileNode��ӵ�����ͼʱ�Զ�ע���ҳ�ڵ㣬��ӵ��κθ��ڵ�ʱ���ᷢ��AddChild��
    // ����ʵ��DatabasePager��Ψһ�����
    // DatabasePager������Ӻ��Ƴ��ӽڵ㣬���໹ʵ��һЩ�����ķ���(���롢�滻��)
	bool addChild( osg::IVBF_SGNode* child );
	bool removeChildren(unsigned pos, unsigned numChildrenToRemove );

private:

	ref_ptr<CMP_TileNodeRegistry> _live, _dead;
};

#endif // OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
