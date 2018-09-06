
#ifndef OSGEARTH_UTIL_LATLONG_FORMATTER_H
#define OSGEARTH_UTIL_LATLONG_FORMATTER_H

#include <VBF_3DMap/VBF_EarthUtil/VBF_Formatter.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // 格式化地理坐标（经纬度）
    class OSGEARTHUTIL_EXPORT LatLongFormatter : public Formatter
    {
    public:
        enum AngularFormat // 格式
		{
            FORMAT_DEFAULT,
            FORMAT_DECIMAL_DEGREES,         // 度（带小数）
            FORMAT_DEGREES_DECIMAL_MINUTES, // 度、分（带小数）
            FORMAT_DEGREES_MINUTES_SECONDS  // 度、分、秒
        };

        // 格式选项
        enum Options
        {
            USE_SYMBOLS     = 1 << 0,   // 是否使用符号
            USE_COLONS      = 1 << 1,   // 是否用冒号分割
            USE_SPACES      = 1 << 2    // 是否用空格分隔
        };

    public:
        LatLongFormatter( const AngularFormat& defaultFormat =FORMAT_DECIMAL_DEGREES, unsigned optionsMask=0u );
        virtual ~LatLongFormatter() { }

        // 设置十进制数的精度（默认是5）
        void setPrecision( int value ) { _prec = value; }

        // 设置格式选项
        void setOptions( const Options& options ) { _options = options; }

        // 格式化一个角度
        std::string format( const Angular& angle, int precision =-1,
            const AngularFormat& outputFormat =FORMAT_DEFAULT) const;

        // 分析一个格式化的字符串，转化为角度
        bool parseAngle( const std::string& input, Angular& out_value );

    public: // Formatter
        virtual std::string format( const GeoPoint& p ) const;

    protected:
        unsigned      _options;
        AngularFormat _defaultFormat;
        int           _prec;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_UTIL_LATLONG_FORMATTER_H
