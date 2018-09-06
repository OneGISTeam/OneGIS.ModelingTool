#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY
#define OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>


namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

	// ��������������Ĺ�����
    class OSGEARTHSYMBOLOGY_EXPORT GeometryFactory
    {
    public:
		// srsΪ�����ļ�����Ŀռ�ο������ΪNULL�򴴽��ֲ��ļ�����
        GeometryFactory( const CVBF_SpatialReference* srs =0L );
        virtual ~GeometryFactory();

		// ����һ��Բ��centerΪ���ĵ㣨�ռ�ο�Ϊ���캯�����ṩ�ģ���radiusΪ�뾶��
		// numSegmentsΪ�ֵ��߶��������Ϊ0���Զ����㣬���geomToUseΪ���򴴽�һ���µģ�����ʹ����
        Geometry* createCircle( const osg::Vec3d& center, const Distance& radius,
                                unsigned  numSegments =0, Geometry* geomToUse =0L) const;

		// ����һ�����Σ�start��ʼ�Ƕȣ�end��ֹ�Ƕȣ�pieΪtrue��ʾ����һ��pie���棩�����ǻ��Σ��ߣ�
        Geometry* createArc( const osg::Vec3d& center, const Distance& radius, const Angle& startAngle, const Angle& endAngle,
                             unsigned numSegments =0, Geometry* geomToUse =0L, bool pie = false) const;

		// ������Բ��Major���ᣬMinor���ᣬrotationAngle��ת�ǣ���������ͬǰ
        Geometry* createEllipse( const osg::Vec3d& center, const Distance& radiusMajor, const Distance& radiusMinor,
								 const Angle& rotationAngle, unsigned numSegments =0, Geometry* geomToUse =0L) const;

  		// ������Բ���Σ�����ͬǰ
        Geometry* createEllipticalArc( const osg::Vec3d& center, const Distance& radiusMajor, const Distance& radiusMinor,
				const Angle& rotationAngle, const Angle& startAngle, const Angle& endAngle,
				unsigned numSegments =0, Geometry* geomToUse =0L, bool pie = false) const;

		// ����һ������
        Geometry* createRectangle( const osg::Vec3d& center, const Distance& width, const Distance& height ) const;

    protected:

        ref_ptr<const CVBF_SpatialReference> _srs;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_GEOMETRY_FACTORY
