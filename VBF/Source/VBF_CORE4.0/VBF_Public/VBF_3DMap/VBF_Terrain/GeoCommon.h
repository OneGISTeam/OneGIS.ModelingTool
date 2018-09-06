#ifndef VBF_EARTH_GEODATA_H
#define VBF_EARTH_GEODATA_H 1

namespace osgEarth
{
	#define NO_DATA_VALUE -FLT_MAX

	// 两个地理坐标间差值的类型
    enum GeoInterpolation
    {
        GEOINTERP_GREAT_CIRCLE,	// 大圆线
        GEOINTERP_RHUMB_LINE    // 等角航线
    };

    // 高程差值方法（通过不同位置的多个点差值）
    enum ElevationInterpolation
    {
        INTERP_AVERAGE,		// 均值
        INTERP_NEAREST,		// 最近的值
        INTERP_BILINEAR,	// 双线性
        INTERP_TRIANGULATE	// 三角差值
    };

	// 高程采样策略（通过同一位置的多个不同值差值）
    enum ElevationSamplePolicy
    {
        SAMPLE_FIRST_VALID,	// 第一个有效值
        SAMPLE_HIGHEST,		// 最大高程
        SAMPLE_LOWEST,		// 最小高程
        SAMPLE_AVERAGE		// 平均高程
    };


	// 高度模式（如何解释Z坐标的值）
    enum AltitudeMode
    {
        ALTMODE_ABSOLUTE,  // Z 值是绝对高度（从MSL/HAE起算）
        ALTMODE_RELATIVE   // Z 值是相对高度（从地表起算）
    };
}

#endif // VBF_EARTH_GEODATA_H
