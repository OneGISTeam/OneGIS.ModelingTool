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


// ֡�ţ�ʱ�����������ͬ������
class VBF_BASE_EXPORT CVBF_FrameStamp : public ::CVBF_Referenced
{
public:
	CVBF_FrameStamp();
	CVBF_FrameStamp(const CVBF_FrameStamp& fs);
	CVBF_FrameStamp& operator = (const CVBF_FrameStamp& fs);

	// ����/��ȡ֡��
	void setFrameNumber(unsigned int fnum) { _frameNumber = fnum; }
	unsigned int getFrameNumber() const { return _frameNumber; }

	// ����/��ȡ֡�����ʱ��
	void setReferenceTime(double refTime) { _referenceTime = refTime; }
	double getReferenceTime() const { return _referenceTime; }

	// ����/��ȡ֡�ķ���ʱ��
	void setSimulationTime(double refTime) { _simulationTime = refTime; }
	double getSimulationTime() const { return _simulationTime; }

	// ����/��ȡ֡������ʱ�䣨����ʱ���Ǿ���ʱ�䣬�����������ʱ��Ҳ��������ʵʱ�䣩
	void setCalendarTime(const tm& calendarTime);
	void getCalendarTime(tm& calendarTime) const;

	// ʹ��public��ʽ��Ϊ��ʹ��osgcluster�ڷǶ��Ϸ���
	virtual ~CVBF_FrameStamp();

protected:
	// ˵��������û��ʹ�ö�̬�ڴ棬������ݿ���ͨ���򵥵��ڴ濽�������������ݰ��д���

	unsigned int    _frameNumber;
	double          _referenceTime;
	double          _simulationTime;        

	// time.h��tm�ṹ�ĳ�Ա����������һ�ݶ���ֱ��ʹ��tm�ṹ��Ϊ�˱�֤���е������ǷǶ�̬�ġ�
	// tm�ṹ�ڲ�ͬ��ʵ��֮���ǲ���ȫһ�µģ�ֱ��ʹ��tm�ṹ�ṹ�����紫������п��ܻ��������⣨����Unix��Windows��
	int tm_sec;            /* ��				[0-60] (1 leap second) */
	int tm_min;            /* ��				[0-59] */
	int tm_hour;           /* ʱ				[0-23] */
	int tm_mday;           /* ��				[1-31] */
	int tm_mon;            /* ��            [0-11] */
	int tm_year;           /* ��            - 1900.  */
	int tm_wday;           /* Day of week.  [0-6] */
	int tm_yday;           /* Days in year.	[0-365]    */
	int tm_isdst;          /* DST.          [-1/0/1]*/
};

#endif
