#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H
#define OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/Image>

namespace osgEarth { namespace Symbology
{
	// ��ͼ���ϻ��Ƽ����壨ʹ�����������
    class OSGEARTHSYMBOLOGY_EXPORT GeometryRasterizer
    {
    public:
        GeometryRasterizer( int width, int height, const Style& style =Style() );
        virtual ~GeometryRasterizer();

		// ��ͼ���ϻ��Ƽ�����
        void draw( const Geometry* geom, const osg::Vec4f& color =osg::Vec4f(1,1,1,1) );

 		// �������Ʋ�����ͼ�񣬴˺����draw()��Ч
        osg::Image* finalize();

    private:
        ref_ptr<osg::Image>      _image;
        Style                    _style;
        ref_ptr<CVBF_Referenced> _state;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_GEOMETRY_RASTERIZER_H
