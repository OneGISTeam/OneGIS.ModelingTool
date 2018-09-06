#ifndef OSGEARTH_OVERLAY_NODE_H
#define OSGEARTH_OVERLAY_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/MapNodeObserver.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>

class CVBFO_SGNodeMap;

// 抽象基类，该类节点把几何体（geometry）注入到地图节点的贴地表节点中
class OSGEARTH_EXPORT CVBFO_SGNodeOverlay : public osg::CVBF_SGNodeGroup, public MapNodeObserver
{
public:
    // signature for the function that provides the technique group.
    typedef osg::IVBF_SGNodeGroup* (*TechniqueProvider)(CVBFO_SGNodeMap*);      
        
public:
    CVBFO_SGNodeOverlay( CVBFO_SGNodeMap* mapNode, bool active, TechniqueProvider f =0L );

public:
    // 贴地表是否启用，如果启用贴地表绘制，否则正常绘制
    void setActive( bool value );
    bool getActive() const { return _active; }

public: // MapNodeObserver

    void setMapNode( CVBFO_SGNodeMap* mapNode );

    CVBFO_SGNodeMap* GetMapNode() { return _mapNode.get(); }
    void setTechniqueProvider(TechniqueProvider provider);

public: // osg::Node

    virtual void traverse( osg::NodeVisitor& nv );

public: // osg::Group

    // override these in order to manage the proxy container.
    virtual bool addChild( osg::IVBF_SGNode* child );
    virtual bool insertChild( unsigned index, osg::IVBF_SGNode* child );
    virtual bool removeChild( osg::IVBF_SGNode* child );
    virtual bool replaceChild( osg::IVBF_SGNode* origChild, osg::IVBF_SGNode* newChild );

protected:
    virtual ~CVBFO_SGNodeOverlay() { }

private:
    bool									_active;
    bool									m_bDirty;
    bool									_newActive;
    ref_ptr<osg::IVBF_SGNodeGroup>				_overlayProxyContainer;
    observer_ptr<CVBFO_SGNodeMap>		_mapNode;
    TechniqueProvider						_getGroup;

    void applyChanges();
};


#endif // OSGEARTH_OVERLAY_NODE_H
