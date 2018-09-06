#ifndef _VBF_TIME_CONVERTER_H_
#define _VBF_TIME_CONVERTER_H_

#include <VBF_Common/VBF_Math/VBF_Export.h>


const double SA_S2D = 1.0 / 86400.0; // 把秒转换到天
const double SA_M2D = 1.0 / 1440.0;  // 把分转换到天
const double SA_H2D = 1.0 / 24.0;    // 把小时转换到天
const double SA_M2H = 1.0 / 60.0;    // 把分转换到小时
const double SA_S2H = 1.0 / 3600.0;  // 把秒转换到小时
const double SA_S2M = 1.0 / 60.0;    // 把秒转换到分
const double SA_D2C = 1.0 / 36525.0; // 把天转换到世纪

// 儒略日(JD)是一?不用年、月的?期?日法。它以倒推到公元前4713年1月1日格林尼治平?正午?起算日期，每天??而下。
const double SA_JD2MJD = 2400000.5; // JD与MJD之间的变换参数 MJD = JD - 2400000.5




/* 不同时间系统之间的转换
 * 国际原子时(TAI)：1967年的第13届国际度量衡会议上通过的，一秒为铯-133原子基态两个超精细能级间跃迁辐射9,192,631,770周所持续的时间。
                  TAI是根据以上秒的定义的一种国际参照时标，属国际单位制(SI)。
                  TAI是一种连续性时标，由1958年1月1日0时0分0秒起，以日、时、分、秒计算。原子时标的准确度为每日数纳秒，而世界时的准确度则只为数毫秒。
 * 协调世界时(UTC)：一种折中时标，于1972年面世。为了确保协调世界时与世界时(UT1)相差不会超过0.9秒，
                   有需要时便会在协调世界时内加上正或负闰秒。因此协调世界时与国际原子时(TAI)
                   之间会出现若干整数秒的差别。位于巴黎的国际地球自转事务中央局(IERS)负责决定何时加入闰秒。
   视太阳时：是一种源于太阳所见位置的时间标准
   世界时(UT)及格林尼治平时(GMT)：由于地球轨道并非圆形，其运行速度又随着地球与太阳的距离改变而出现变化，
                   因此视太阳时欠缺均匀性。视太阳日的长度同时亦受到地球自转轴相对轨道面的倾斜度所影响。
                   为着要纠正上述的不均匀性，天文学家计算地球非圆形轨迹与极轴倾斜对视太阳时的效应。
                   平太阳时就是指经修订后的视太阳时。
                   在格林尼治子午线上的平太阳时称为世界时(UT0)，又叫格林尼治平时(GMT)。

   格林尼治标准时间（GMT）：是指位于格林尼治天文台的标准时间，因为本初子午线被定义在通过那里的经线。

 *		-MST Means Sidereal Time
 *		-GMST Mean sun time of Greenwich
 *		-GAST True sun time of Greenwich
 *		-TDT Terrestrial Dynamic Time
 *		-TDB Barycentric Dynamic Time
 * 儒略日(JD)：一种不用年、月的长期纪日法。它以倒推到公元前4713年1月1日格林尼治平时正午为起算日期，每天顺数而下。
 * 约化儒略日(MJD)：MJD = JD - 2400000.5

 */


class VBF_MATH_EXPORT CVF_TimeConverter
{
public:

	static double convertTDTtoTAI(double TDT);
	static double convertTAItoTDT(double TAI);

	static double convertUTCtoTAI(double MUTC);
	static double convertTAItoUTC(double MTAI);

//	static double convertUT1toTDT(double MUT1);
//	static double convertTDTtoUT1(double MTDT);

//	static double convertUT1toUTC(double MUT1);
//	static double convertUTCtoUT1(double MUTC);

	static double convertTDTtoTDB(double MTDT);
	static double convertUT1toGMST(double MUT1);


    // MJD（约化儒略日）与JD（儒略日）之间的变换
	static double convertJDtoMJD(double JD);
	static double convertMJDtoJD(double MJD);


    // 根据给定的日期和时间，转换为JD（儒略日）
	static double convertDTtoJD(int year, int month, int day,
			int hour, int minute, double second);

    // 根据给定的JD（儒略日），转换为日期和时间
	static void convertJDtoDT(double JD, int &year, int &month, int &day,
			int &hour, int &minute, double &second);

    // Convert datetime to MTDT directly
//    static double convertDTtoMTDT(int year, int month, int day, int hour, int minute, double second);
    // Convert UTC to MTDT directly
//    static double convertUTCtoMTDT(double UTC);
    static double deltaUTCtoTAI(double MUTC);
};

#endif
