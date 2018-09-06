#ifndef OSGSHADOW_SHADOWEDSCENE
#define OSGSHADOW_SHADOWEDSCENE 1

#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_Shadow/VBF_ShadowSettings.h>
#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>


// ʵʱ��Ӱ��һ����Ը߼��ļ������������еļ�������λ�ñ䶯ʱ��Ҫ����Shadow volume����ʵ������һ����ά���壬
// ��ͶӰ��������������Ǵӹ�Դ����Ͷ������Ӱ��ʵ���ɺܶ��ַ��������ڱȽ����е���Ҫ��shadow mapping��shadow volume��

namespace osgShadow {

// ShadowedScene�ṩ��һ�ֻ��ƣ����ڸ����������Ӱ������һ����ڵ㣬��������ӽڵ㣬ͬʱ����ָ��ͶӰ����ͽ���ͶӰ�Ķ���
class OSGSHADOW_EXPORT ShadowedScene : public osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup>
{
private:
	typedef osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup> BaseClass;

public:
    ShadowedScene(ShadowTechnique* st=0);
    ShadowedScene(const ShadowedScene& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);            
    META_Node(osgShadow, ShadowedScene);
        
    virtual void traverse(osg::NodeVisitor& nv);
        
	// ����ͶӰ�Ķ���һ����ͨ��maskɸѡ��
    void setReceivesShadowTraversalMask(unsigned int mask) { _receivesShadowTraversalMask = mask; }
    unsigned int getReceivesShadowTraversalMask() const { return _receivesShadowTraversalMask; }
        
	// ͶӰ�Ķ���һ����ͨ��maskɸѡ��
    void setCastsShadowTraversalMask(unsigned int mask) { _castsShadowTraversalMask = mask; }
    unsigned int getCastsShadowTraversalMask() const { return _castsShadowTraversalMask; }

	// ����/��ȡ��Ӱ���ã���Ө��ӣ�2018-04-07��
	void setShadowSettings(ShadowSettings* ss);
    ShadowSettings* getShadowSettings() { return _shadowSettings.get(); }
    const ShadowSettings* getShadowSettings() const { return _shadowSettings.get(); }
        
	// ָ��/��ȡͶӰʵ�ֵķ���������ͶӰʹ�õļ�����
    void setShadowTechnique(ShadowTechnique* technique);
    ShadowTechnique* getShadowTechnique() { return _shadowTechnique.get(); }
    const ShadowTechnique* getShadowTechnique() const { return _shadowTechnique.get(); }

	// �������ͼ���κ�ʹ������Ӱ�����Ľڵ㡢״̬�Ϳɻ��ƶ���
    void cleanSceneGraph();

	// Dirty ��������Ӱ�����еĻ�������
    void dirty();

    /** Resize any per context GLObject buffers to specified size. */
    virtual void resizeGLObjectBuffers(unsigned int maxSize);

    /** If State is non-zero, this function releases any associated OpenGL objects for
        * the specified graphics context. Otherwise, releases OpenGL objects
        * for all graphics contexts. */
    virtual void releaseGLObjects(osg::State* = 0) const;
    
protected:
    virtual ~ShadowedScene();

    unsigned int				_receivesShadowTraversalMask; // ����ͶӰ�Ľڵ������
    unsigned int				_castsShadowTraversalMask;    // ͶӰ�Ľڵ������
        
	ref_ptr<ShadowSettings>		_shadowSettings;
    ref_ptr<ShadowTechnique>	_shadowTechnique;
};

}

#endif
