#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H
#define OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/Image>

namespace osgEarth { namespace Symbology
{
	// 在图像上绘制几何体（使用软件方法）
    class OSGEARTHSYMBOLOGY_EXPORT GeometryRasterizer
    {
    public:
        GeometryRasterizer( int width, int height, const Style& style =Style() );
        virtual ~GeometryRasterizer();

		// 在图像上绘制几何体
        void draw( const Geometry* geom, const osg::Vec4f& color =osg::Vec4f(1,1,1,1) );

 		// 结束绘制并返回图像，此后调用draw()无效
        osg::Image* finalize();

    private:
        ref_ptr<osg::Image>      _image;
        Style                    _style;
        ref_ptr<CVBF_Referenced> _state;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H
