#ifndef OSGEARTH_ANNOTATION_DECORATION_H
#define OSGEARTH_ANNOTATION_DECORATION_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

    class OSGEARTHANNO_EXPORT Decoration : public ::CVBF_Referenced
    {
    public:
        Decoration() { }
        virtual ~Decoration() { }

        virtual bool isShareable() const { return false; }
        virtual Decoration* clone() const =0;
        Decoration* copyOrClone() { return isShareable() ? this : clone(); }

    public:
        virtual bool apply(class AnnotationNode& node, bool enable);
        virtual bool apply(class LocalizedNode&  node, bool enable);
        virtual bool apply(class OrthoNode&      node, bool enable);
    };


	// 节点遍历操作器，用于给场景图中的注记节点（AnnotationNode）安装装饰
    class OSGEARTHANNO_EXPORT DecorationInstaller : public osg::NodeVisitor
    {
    public:
        struct Callback : public ::CVBF_Referenced
        {
            virtual void operator()( AnnotationNode* node ) =0;
        };

    public:

        DecorationInstaller( const std::string& name, Decoration* tech )
            : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
              _tech(tech), m_sName(name) 
		{
		}

        DecorationInstaller( const std::string& name, Callback* callback )
            : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
              _callback(callback), m_sName(name) 
		{
		}


        virtual ~DecorationInstaller() { }

    public:
        virtual void apply(osg::IVBF_SGNode& node);

    public:
        ref_ptr<Decoration> _tech;
        ref_ptr<Callback>   _callback;
        std::string         m_sName;
    };

    //-----------------------------------------------------------------------

	// 注入装饰，在装饰的节点与子节点之间插入一个新的节点（该节点可以做各种效果，如Effect或激活着色器的节点）
    class OSGEARTHANNO_EXPORT InjectionDecoration : public Decoration
    {
    public:
        InjectionDecoration( osg::IVBF_SGNodeGroup* group =0L );
        virtual ~InjectionDecoration() { }

        virtual Decoration* clone() const { return new InjectionDecoration(osg::clone(_injectionGroup.get(), osg::CopyOp::DEEP_COPY_ALL)); }
        virtual bool apply(class AnnotationNode& node, bool enable);

    protected:
        ref_ptr<osg::IVBF_SGNodeGroup> _injectionGroup;

        virtual bool apply(osg::IVBF_SGNodeGroup* attachPoint, bool enable);
    };


} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_DECORATION_H
