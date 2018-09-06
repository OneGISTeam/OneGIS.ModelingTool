#ifndef OSGEARTH_ANNOTATION_SCALE_DECORATION_H
#define OSGEARTH_ANNOTATION_SCALE_DECORATION_H 1

#include <VBF_3DMap/VBF_Annotation/Decoration.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

 	// 缩放注记的装饰，插入了一个矩阵变换节点
    class ScaleDecoration : public InjectionDecoration
    {
    public:
        ScaleDecoration(float factor =1.1f) :
            InjectionDecoration(new osg::MatrixTransform(osg::Matrix::scale(factor,factor,factor))),
            _factor(factor) { }

        virtual ~ScaleDecoration() { }

        virtual Decoration* clone() const { return new ScaleDecoration(_factor); }

    protected:
        float _factor;
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_DECORATION_H
