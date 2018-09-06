#ifndef OSGEARTH_DP_LINE_SEG_INTERSECTOR_H
#define OSGEARTH_DP_LINE_SEG_INTERSECTOR_H

//!!!#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>

namespace osgEarth
{
	// һ��˫���Ȱ汾��osgUtil::LineSegmentIntersector�����ڵ��Ŀռ䣨��������ϵ��
    class OSGEARTH_EXPORT DPLineSegmentIntersector : public osgUtil::LineSegmentIntersector
    {
    public:
        DPLineSegmentIntersector(const osgUtil::Intersector::CoordinateFrame& cf, const osg::Vec3d& start, const osg::Vec3d& end)
            : osgUtil::LineSegmentIntersector(cf, start, end) { }

        DPLineSegmentIntersector(const osg::Vec3d& start, const osg::Vec3d& end)
            : osgUtil::LineSegmentIntersector(start, end) { }

        virtual ~DPLineSegmentIntersector() { }

    public: // overrides
        
        virtual osgUtil::Intersector* clone(osgUtil::IntersectionVisitor& iv);
        virtual void intersect(osgUtil::IntersectionVisitor& iv, osg::Drawable* drawable);
    };

} // namespace osgEarth::Util

#endif // OSGEARTH_DP_LINE_SEG_INTERSECTOR_H
