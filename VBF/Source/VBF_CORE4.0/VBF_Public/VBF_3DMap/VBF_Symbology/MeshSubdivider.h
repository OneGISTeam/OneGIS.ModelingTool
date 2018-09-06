#ifndef OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER
#define OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Terrain/GeoMath.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/PrimitiveSet>

// 建议：移到Features库中
namespace osgEarth { namespace Symbology
{

	// 对地心坐标系的几何体按指定的粒度进行网格递归细分(tesselates)，细分到椭球表面
    class OSGEARTHSYMBOLOGY_EXPORT MeshSubdivider
    {
    public:
        MeshSubdivider( const osg::Matrixd& world2local =osg::Matrixd::identity(),
                        const osg::Matrixd& local2world =osg::Matrixd::identity() );
        virtual ~MeshSubdivider();
		// 设置每个产生图元集合的最大elements数量
        void setMaxElementsPerEBO( unsigned int value ) { _maxElementsPerEBO = value; }

		// 把几何体细分到指定的粒度，粒度单位为弧度（三角形两个点之间的最大球心角），该方法把几何体中所有多边形图元集合合并到一个GL_TRIANGLES图元集
		// 说明! 当前，该工具对于几何体的颜色和纹理不做任何操作
        void run( osg::Geometry& geom, double granurality_radians, GeoInterpolation interp =GEOINTERP_RHUMB_LINE );

    protected:
        osg::Matrixd _local2world, _world2local;
        unsigned int _maxElementsPerEBO;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MESH_SUBDIVIDER
