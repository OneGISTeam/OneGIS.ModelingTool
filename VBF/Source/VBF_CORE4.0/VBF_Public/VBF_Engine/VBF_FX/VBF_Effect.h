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

/*  FX��һ�����ӿ⣬��һ��ʵ�� "����Ч��" �ļܹ����ߣ���ЩЧ��������ӵ�����ͼ�Ľڵ��С�
	ͬʱ�����ṩ��һϵ��Ԥ����õ�����Ч����
*/

// ������
#define META_Effect(library, classname, effectname, effectdescription, effectauthor) \
    META_Node(library, classname) \
    virtual const char *effectName() const        { return effectname; } \
    virtual const char *effectDescription() const { return effectdescription; } \
    virtual const char *effectAuthor() const      { return effectauthor; }


namespace osgFX
{

    /**
     ��Ч�Ļ��ࡣ effect��������һ��״̬���ԣ�state attributes���ļ��Ϻ�һ���ӿ�
	 ��������Ԥ�������ʽ�����ң�������͸���Ĵ����˶����Ⱦ����������"technique"��
	 ÿ�ּ�����technique���ò�ͬ��ʽʵ����Ч����ʹ�ò�ͬ��OpenGL��չ��
     �����û���˵������������һ����ڵ�ʹ�ã�����һ��������Ч�������뵽����ͼ��������Ҫ
	 ��Ч���Ľڵ���뵽��Ч�ڵ����ͼ�У�
	 ���ڿ�������˵������ʵ��define_techniques()���Ա㶨�岻ͬ�ļ�������Щ�������������������Ч����
	 ��define_techniques()�г�����һ���������弼�����̳���Technique����ʵ��������addTechnique()��ӵ���Ч��
	 ��ӵ�˳���Ƿǳ���Ҫ��:     ��һ����ӵļ���techniques���и��ߵ����ȼ�������Կ�֧�ֽ�����ѡ��ü�����
     */
    class OSGFX_EXPORT Effect: public osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup> 
	{
    public:
        Effect();
        Effect(const Effect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual inline bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Effect*>(obj) != NULL; }
        virtual inline const char* libraryName() const { return "osgFX"; }
        virtual inline const char* className() const { return "Effect"; }

        // ��ȡ��Ч������
        virtual const char *effectName() const        = 0;
        
        // ��ȡ��Ч�ļ�Ҫ����
        virtual const char *effectDescription() const = 0;

        // ��ȡ��Ч������
        virtual const char *effectAuthor() const      = 0;

		// ����/�ж��Ƿ����
		inline bool getEnabled() const { return _enabled; }
		inline void setEnabled(bool v) { _enabled = v; } 
        
       
        // ��ѡ��: ������Ч�������Ա����һ���ɼ����д����Ե�Ч��������demo�У���osgfxbrowser��ȱʡʱʲôҲ������      
        inline virtual void setUpDemo()   {}

		// ��ȡ����Ч֧�ֵļ�������
        inline int getNumTechniques() const;

		// ��ȡ��i������
        inline Technique* getTechnique(int i);
        inline const Technique* getTechnique(int i) const;

        // ��ȡ��ǰѡ��ļ���������ֵ
        inline int getSelectedTechnique() const;

        enum TechniqueSelection 
		{
            AUTO_DETECT = -1
        };

		// ѡ��һ������Զ����
        inline void selectTechnique(int i = AUTO_DETECT);

        // ��������
        virtual void traverse(osg::NodeVisitor& nv);        

		// Ĭ�ϵ�traversal
        inline void inherited_traverse(osg::NodeVisitor& nv);

    protected:
        virtual ~Effect();
        Effect &operator=(const Effect &) { return *this; }
       
		// ����һ�α�������ʱ��ǿ���ؽ�����Ч���õļ���
        inline void dirtyTechniques();

		// ���һ�ּ���ʵ��
        inline void addTechnique(Technique* tech);

        
        // ���弼�������󷽷�����������ʵ�֣�ͨ���ڸú����� addTechnique()     
        virtual bool define_techniques() = 0;
        
    private:
        friend class Validator;

        bool _enabled;			// �Ƿ����

        typedef std::vector<ref_ptr<Technique> > Technique_list;
        Technique_list _techs;	// ֧�ֵļ������б�	

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
