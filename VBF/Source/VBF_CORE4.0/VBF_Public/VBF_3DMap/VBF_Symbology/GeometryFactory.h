#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY
#define OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>


namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

	// 辅助创建集合体的工具类
    class OSGEARTHSYMBOLOGY_EXPORT GeometryFactory
    {
    public:
		// srs为创建的几何体的空间参考，如果为NULL则创建局部的几何体
        GeometryFactory( const CVBF_SpatialReference* srs =0L );
        virtual ~GeometryFactory();

		// 创建一个圆，center为中心点（空间参考为构造函数中提供的），radius为半径，
		// numSegments为分的线段数，如果为0则自动计算，如果geomToUse为空则创建一个新的，否则使用它
        Geometry* createCircle( const osg::Vec3d& center, const Distance& radius,
                                unsigned  numSegments =0, Geometry* geomToUse =0L) const;

		// 创建一个弧段，start起始角度，end终止角度，pie为true表示创建一个pie（面）而不是弧段（线）
        Geometry* createArc( const osg::Vec3d& center, const Distance& radius, const Angle& startAngle, const Angle& endAngle,
                             unsigned numSegments =0, Geometry* geomToUse =0L, bool pie = false) const;

		// 创建椭圆，Major长轴，Minor短轴，rotationAngle旋转角，其他参数同前
        Geometry* createEllipse( const osg::Vec3d& center, const Distance& radiusMajor, const Distance& radiusMinor,
								 const Angle& rotationAngle, unsigned numSegments =0, Geometry* geomToUse =0L) const;

  		// 创建椭圆弧段，参数同前
        Geometry* createEllipticalArc( const osg::Vec3d& center, const Distance& radiusMajor, const Distance& radiusMinor,
				const Angle& rotationAngle, const Angle& startAngle, const Angle& endAngle,
				unsigned numSegments =0, Geometry* geomToUse =0L, bool pie = false) const;

		// 创建一个矩形
        Geometry* createRectangle( const osg::Vec3d& center, const Distance& width, const Distance& height ) const;

    protected:

        ref_ptr<const CVBF_SpatialReference> _srs;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY
