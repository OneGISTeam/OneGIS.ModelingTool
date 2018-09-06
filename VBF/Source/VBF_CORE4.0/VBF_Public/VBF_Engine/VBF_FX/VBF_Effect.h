#ifndef OSGFX__effect
#define OSGFX__effect

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/Technique>

#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupOccluder.h>

#include <vector>

/*  FX是一个附加库，是一个实现 "特殊效果" 的架构工具，这些效果可以添加到场景图的节点中。
	同时，还提供了一系列预定义好的特殊效果。
*/

// 辅助宏
#define META_Effect(library, classname, effectname, effectdescription, effectauthor) \
    META_Node(library, classname) \
    virtual const char *effectName() const        { return effectname; } \
    virtual const char *effectDescription() const { return effectdescription; } \
    virtual const char *effectAuthor() const      { return effectauthor; }


namespace osgFX
{

    /**
     特效的基类。 effect基本上是一个状态属性（state attributes）的集合和一个接口
	 用于配置预定义的样式。而且，由于它透明的处理了多遍渲染，允许定义多个"technique"。
	 每种技术（technique）用不同方式实现特效，常使用不同的OpenGL扩展。
     对于用户来说，仅把它当成一个组节点使用，创建一个期望的效果，加入到场景图，并把需要
	 该效果的节点加入到特效节点的子图中，
	 对于开发者来说，必须实现define_techniques()，以便定义不同的技术，这些技术被用来获得期望的效果。
	 在define_techniques()中常创建一个或多个具体技术（继承自Technique）的实例，并用addTechnique()添加到特效。
	 添加的顺序是非常重要的:     第一个添加的技术techniques具有更高的优先级，如果显卡支持将优先选择该技术。
     */
    class OSGFX_EXPORT Effect: public osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup> 
	{
    public:
        Effect();
        Effect(const Effect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual inline bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Effect*>(obj) != NULL; }
        virtual inline const char* libraryName() const { return "osgFX"; }
        virtual inline const char* className() const { return "Effect"; }

        // 获取特效的名称
        virtual const char *effectName() const        = 0;
        
        // 获取特效的简要描述
        virtual const char *effectDescription() const = 0;

        // 获取特效的作者
        virtual const char *effectAuthor() const      = 0;

		// 设置/判断是否可用
		inline bool getEnabled() const { return _enabled; }
		inline void setEnabled(bool v) { _enabled = v; } 
        
       
        // 可选项: 设置特效参数，以便产生一个可见的有代表性的效果，用于demo中，如osgfxbrowser。缺省时什么也不做。      
        inline virtual void setUpDemo()   {}

		// 获取该特效支持的技术数量
        inline int getNumTechniques() const;

		// 获取第i个技术
        inline Technique* getTechnique(int i);
        inline const Technique* getTechnique(int i) const;

        // 获取当前选择的技术的索引值
        inline int getSelectedTechnique() const;

        enum TechniqueSelection 
		{
            AUTO_DETECT = -1
        };

		// 选择一项技术或自动检测
        inline void selectTechnique(int i = AUTO_DETECT);

        // 遍历操作
        virtual void traverse(osg::NodeVisitor& nv);        

		// 默认的traversal
        inline void inherited_traverse(osg::NodeVisitor& nv);

    protected:
        virtual ~Effect();
        Effect &operator=(const Effect &) { return *this; }
       
		// 在下一次遍历操作时，强制重建该特效所用的技术
        inline void dirtyTechniques();

		// 添加一种技术实现
        inline void addTechnique(Technique* tech);

        
        // 定义技术。抽象方法，在子类中实现，通常在该函数中 addTechnique()     
        virtual bool define_techniques() = 0;
        
    private:
        friend class Validator;

        bool _enabled;			// 是否可用

        typedef std::vector<ref_ptr<Technique> > Technique_list;
        Technique_list _techs;	// 支持的技术的列表	

        mutable osg::buffered_value<int> _sel_tech;

        // use int instead of bool to avoid errors
        mutable osg::buffered_value<int> _tech_selected;
        
        int _global_sel_tech;

        bool _techs_defined;

        ref_ptr<osg::IVBF_SGNodeGeometry> _dummy_for_validation;
        
        void build_dummy_node();
    };

    // INLINE METHODS

  
    inline int Effect::getNumTechniques() const
    {
        return static_cast<int>(_techs.size());
    }

    inline Technique* Effect::getTechnique(int i)
    {
        return _techs[i].get();
    }

    inline const Technique* Effect::getTechnique(int i) const
    {
        return _techs[i].get();
    }

    inline int Effect::getSelectedTechnique() const
    {
        return _global_sel_tech;
    }

    inline void Effect::selectTechnique(int i)
    {
        _global_sel_tech = i;
    }

    inline void Effect::addTechnique(Technique* tech)
    {
        _techs.push_back(tech);
    }
    
    inline void Effect::dirtyTechniques()
    {
        _techs_defined = false;
    }
    
    inline void Effect::inherited_traverse(osg::NodeVisitor& nv)
    {
        typedef osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup> inherited;
        inherited::traverse(nv);
    }

}

#endif
