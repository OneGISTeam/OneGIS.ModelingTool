#ifndef OSGEARTH_ANNOTATION_HIGHLIGHT_DECORATION_H
#define OSGEARTH_ANNOTATION_HIGHLIGHT_DECORATION_H 1

#include <VBF_3DMap/VBF_Annotation/Decoration.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

	// º”¡¡◊∞ Œ
    class OSGEARTHANNO_EXPORT HighlightDecoration : public InjectionDecoration
    {
    public:
        HighlightDecoration(const osg::Vec4f& color =osg::Vec4f(1,1,0,0.5));

        virtual ~HighlightDecoration() { }

        virtual Decoration* clone() const { return new HighlightDecoration(_color); }
        
        virtual bool apply(class OrthoNode& node, bool enable);

    protected:
        virtual bool apply(osg::IVBF_SGNodeGroup* attachPoint, bool enable);

        osg::Vec4f _color;
        ref_ptr<osg::StateSet> _passes[2];
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_HIGHLIGHT_DECORATION_H
