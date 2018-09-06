#ifndef OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER
#define OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Terrain/GeoMath.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/PrimitiveSet>

// ���飺�Ƶ�Features����
namespace osgEarth { namespace Symbology
{

	// �Ե�������ϵ�ļ����尴ָ�������Ƚ�������ݹ�ϸ��(tesselates)��ϸ�ֵ��������
    class OSGEARTHSYMBOLOGY_EXPORT MeshSubdivider
    {
    public:
        MeshSubdivider( const osg::Matrixd& world2local =osg::Matrixd::identity(),
                        const osg::Matrixd& local2world =osg::Matrixd::identity() );
        virtual ~MeshSubdivider();
		// ����ÿ������ͼԪ���ϵ����elements����
        void setMaxElementsPerEBO( unsigned int value ) { _maxElementsPerEBO = value; }

		// �Ѽ�����ϸ�ֵ�ָ�������ȣ����ȵ�λΪ���ȣ�������������֮���������Ľǣ����÷����Ѽ����������ж����ͼԪ���Ϻϲ���һ��GL_TRIANGLESͼԪ��
		// ˵��! ��ǰ���ù��߶��ڼ��������ɫ���������κβ���
        void run( osg::Geometry& geom, double granurality_radians, GeoInterpolation interp =GEOINTERP_RHUMB_LINE );

    protected:
        osg::Matrixd _local2world, _world2local;
        unsigned int _maxElementsPerEBO;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER
