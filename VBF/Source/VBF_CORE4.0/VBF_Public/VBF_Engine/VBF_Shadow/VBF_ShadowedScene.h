#ifndef OSGSHADOW_SHADOWEDSCENE
#define OSGSHADOW_SHADOWEDSCENE 1

#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_Shadow/VBF_ShadowSettings.h>
#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>


// 实时阴影是一种相对高级的技术，当场景中的几何体或光位置变动时，要计算Shadow volume，它实际上是一个三维物体，
// 是投影物体的轮廓，总是从光源方向投出。阴影的实现由很多种方法，现在比较流行的主要是shadow mapping和shadow volume。

namespace osgShadow {

// ShadowedScene提供了一种机制，用于给场景添加阴影。它是一个组节点，可以添加子节点，同时可以指定投影对象和接受投影的对象
class OSGSHADOW_EXPORT ShadowedScene : public osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup>
{
private:
	typedef osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup> BaseClass;

public:
    ShadowedScene(ShadowTechnique* st=0);
    ShadowedScene(const ShadowedScene& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);            
    META_Node(osgShadow, ShadowedScene);
        
    virtual void traverse(osg::NodeVisitor& nv);
        
	// 接受投影的对象（一批，通过mask筛选）
    void setReceivesShadowTraversalMask(unsigned int mask) { _receivesShadowTraversalMask = mask; }
    unsigned int getReceivesShadowTraversalMask() const { return _receivesShadowTraversalMask; }
        
	// 投影的对象（一批，通过mask筛选）
    void setCastsShadowTraversalMask(unsigned int mask) { _castsShadowTraversalMask = mask; }
    unsigned int getCastsShadowTraversalMask() const { return _castsShadowTraversalMask; }

	// 设置/获取阴影设置（杜莹添加：2018-04-07）
	void setShadowSettings(ShadowSettings* ss);
    ShadowSettings* getShadowSettings() { return _shadowSettings.get(); }
    const ShadowSettings* getShadowSettings() const { return _shadowSettings.get(); }
        
	// 指定/获取投影实现的方法（设置投影使用的技术）
    void setShadowTechnique(ShadowTechnique* technique);
    ShadowTechnique* getShadowTechnique() { return _shadowTechnique.get(); }
    const ShadowTechnique* getShadowTechnique() const { return _shadowTechnique.get(); }

	// 清除场景图中任何使用了阴影技术的节点、状态和可绘制对象
    void cleanSceneGraph();

	// Dirty 关联的阴影技术中的缓存数据
    void dirty();

    /** Resize any per context GLObject buffers to specified size. */
    virtual void resizeGLObjectBuffers(unsigned int maxSize);

    /** If State is non-zero, this function releases any associated OpenGL objects for
        * the specified graphics context. Otherwise, releases OpenGL objects
        * for all graphics contexts. */
    virtual void releaseGLObjects(osg::State* = 0) const;
    
protected:
    virtual ~ShadowedScene();

    unsigned int				_receivesShadowTraversalMask; // 接受投影的节点的掩码
    unsigned int				_castsShadowTraversalMask;    // 投影的节点的掩码
        
	ref_ptr<ShadowSettings>		_shadowSettings;
    ref_ptr<ShadowTechnique>	_shadowTechnique;
};

}

#endif
