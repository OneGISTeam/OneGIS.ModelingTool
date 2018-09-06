#ifndef OSGEARTH_UTIL_FORMATTER_H
#define OSGEARTH_UTIL_FORMATTER_H

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

	// 坐标格式化接口
    class Formatter : public ::CVBF_Referenced
    {
    public:
        virtual std::string format( const GeoPoint& mapCoords ) const =0;
        std::string operator()(const GeoPoint& p) const { return format(p); }

        virtual ~Formatter() { }
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_UTIL_FORMATTER_H
