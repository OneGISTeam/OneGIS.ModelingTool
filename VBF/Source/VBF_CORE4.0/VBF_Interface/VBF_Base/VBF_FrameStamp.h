#ifndef VBF_FRAME_STAMP_H
#define VBF_FRAME_STAMP_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h>

#if defined(__sgi) || (defined(WIN32) && !defined(__MWERKS__))
#include <time.h>
#else
#include <ctime>
using std::tm;
#endif


// 帧号（时间戳），用于同步操作
class VBF_BASE_EXPORT CVBF_FrameStamp : public ::CVBF_Referenced
{
public:
	CVBF_FrameStamp();
	CVBF_FrameStamp(const CVBF_FrameStamp& fs);
	CVBF_FrameStamp& operator = (const CVBF_FrameStamp& fs);

	// 设置/获取帧号
	void setFrameNumber(unsigned int fnum) { _frameNumber = fnum; }
	unsigned int getFrameNumber() const { return _frameNumber; }

	// 设置/获取帧的相对时间
	void setReferenceTime(double refTime) { _referenceTime = refTime; }
	double getReferenceTime() const { return _referenceTime; }

	// 设置/获取帧的仿真时间
	void setSimulationTime(double refTime) { _simulationTime = refTime; }
	double getSimulationTime() const { return _simulationTime; }

	// 设置/获取帧的历法时间（历法时间是绝对时间，可以是虚拟的时间也可以是真实时间）
	void setCalendarTime(const tm& calendarTime);
	void getCalendarTime(tm& calendarTime) const;

	// 使用public方式是为了使用osgcluster在非堆上分配
	virtual ~CVBF_FrameStamp();

protected:
	// 说明：本类没有使用动态内存，因此数据可以通过简单的内存拷贝或在网络数据包中传递

	unsigned int    _frameNumber;
	double          _referenceTime;
	double          _simulationTime;        

	// time.h的tm结构的成员变量，拷贝一份而不直接使用tm结构是为了保证所有的数据是非动态的。
	// tm结构在不同的实现之间是不完全一致的，直接使用tm结构结构在网络传输过程中可能会引起问题（如混合Unix和Windows）
	int tm_sec;            /* 秒				[0-60] (1 leap second) */
	int tm_min;            /* 分				[0-59] */
	int tm_hour;           /* 时				[0-23] */
	int tm_mday;           /* 日				[1-31] */
	int tm_mon;            /* 月            [0-11] */
	int tm_year;           /* 年            - 1900.  */
	int tm_wday;           /* Day of week.  [0-6] */
	int tm_yday;           /* Days in year.	[0-365]    */
	int tm_isdst;          /* DST.          [-1/0/1]*/
};

#endif
