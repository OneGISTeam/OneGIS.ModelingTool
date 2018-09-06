#ifndef OSGSIM_IMPOSTOR
#define OSGSIM_IMPOSTOR 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>
#include <VBF_Engine/VBF_SceneGraph/buffered_value>

#include <VBF_Engine/VBF_SGUtil/CullVisitor>

#include <VBF_Engine/VBF_Sim/ImpostorSprite>

namespace osgSim {

/** Impostor：替代节点，是一个LOD控制节点，使用该功能，可以不绘制远处的几何体，只需要将6个面用贴图来表示，
	目的是使用假象的方法提高渲染效率。有点像布告牌，但Impostor是实时更新的

  * For more details have a look at:
  * 
  *    http://grail.cs.washington.edu/projects/hic/
  * 
  
  * All you need to do to use Impostors is to set up the visible
  * range values for each LOD child of the Impostor, as per osg::LOD,
  * and set an Impostor threshold to tell the renderer at what distance
  * the Impostor's image caching should cut in.  The osg::CullVisitor
  * automatically handles all the setting of pre-rendering stages to
  * calculate the required ImpostorSprites (which encapsulates the image
  * cache and quad), and updates them as the view point changes. If you 
  * use osg::SceneView/CullVisitor all the complexity of supporting 
  * Impostor will be nicely hidden away.
  *
  * TODO:
  * Various improvements are planned for the Impostor-
  * 1) Estimation of how many frames an ImpostorSprite will be reused, if
  * it won't be used more often than a minimum threshold then do not create
  * ImpostorSprite - use the real geometry.
  * 2) Sharing of texture memory between ImpostorSprites.
  * 3) Simple 3D geometry for ImpostorSprite's rather than Billboarding.
  * 4) Shrinking of the ImpostorSprite size to more closely fit the underlying
  * geometry.
  */
class OSGSIM_EXPORT Impostor : public osg::IVBF_SGNodeGroupLODImpl<osg::IVBF_SGNodeGroupLOD>
{
    public :
        Impostor();

        Impostor(const Impostor& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):
            osg::IVBF_SGNodeGroupLODImpl<osg::IVBF_SGNodeGroupLOD>(es,copyop),
            _impostorThreshold(es._impostorThreshold) 
		{
		}
            
        META_Node(osgSim, Impostor);
        
        virtual void traverse(osg::NodeVisitor& nv);

  
		// 设置/获取Impostor开始的距离，超过该距离采用Imposter，否则与LOD相同
        inline void setImpostorThreshold(float distance) { _impostorThreshold = distance; }
        inline float getImpostorThreshold() const { return _impostorThreshold; }

		// 设置/获取Impostor的开始距离相对物体包围球半径的比例
        inline void setImpostorThresholdToBound(float ratio=1.0f) { _impostorThreshold = getBound().radius()*ratio; }

 		// 查找适合当前视点的ImposterSprite
        ImpostorSprite* findBestImpostorSprite(unsigned int contextID, const osg::Vec3& currLocalEyePoint) const;
        
		// 添加ImpostorSprite
        void addImpostorSprite(unsigned int contextID, ImpostorSprite* is);


        typedef std::vector< ref_ptr<ImpostorSprite> > ImpostorSpriteList;

		// 获取ImpostorSprites的列表
        inline ImpostorSpriteList& getImpostorSpriteList(unsigned int contexID) { return _impostorSpriteListBuffer[contexID]; }
        inline const ImpostorSpriteList& getImpostorSpriteList(unsigned int contexID) const { return _impostorSpriteListBuffer[contexID]; }

		// 计算包围球
        virtual osg::BoundingSphere computeBound() const;
        
    protected :

        virtual ~Impostor() {}

        mutable osg::buffered_object<ImpostorSpriteList>  _impostorSpriteListBuffer;
        
		// 利用筛选器（cull）创建ImpostorSprite
        ImpostorSprite* createImpostorSprite(osgUtil::CullVisitor* cv);

        float _impostorThreshold;

};

}

#endif
