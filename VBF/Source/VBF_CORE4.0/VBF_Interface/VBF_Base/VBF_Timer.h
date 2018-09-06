#ifndef VBF_TIMER_H
#define VBF_TIMER_H 1

#include <VBF_Base/VBF_BaseExport.h>


#if defined(_MSC_VER)
	typedef __int64 CVBF_Timer_t;
#else
	typedef unsigned long long CVBF_Timer_t;
#endif

// ��ʱ�����ɻ�ȡ���ʱ���ʱ����
class VBF_BASE_EXPORT CVBF_Timer 
{
public:

	CVBF_Timer();
    ~CVBF_Timer();

	static CVBF_Timer* instance();

    // ��ȡ��ʱ����tickֵ
	CVBF_Timer_t tick() const;

	// ����/��ȡ��ʱ������ʼֵ
	void setStartTick() { _startTick = tick(); }       
	void setStartTick(CVBF_Timer_t t) { _startTick = t; }   
	CVBF_Timer_t getStartTick() const { return _startTick; }


    // ��ȡʱ�䣨�������ʼֵ������λ��
	inline double time_s() const { return delta_s(_startTick, tick()); }  // s
    // ��ȡʱ�䣨�������ʼֵ������λ����
	inline double time_m() const { return delta_m(_startTick, tick()); }  // ms

    // ��ȡʱ�䣨�������ʼֵ������λ΢�룺һ�����֮һ�룬10-6
	inline double time_u() const { return delta_u(_startTick, tick()); }  // us

    // ��ȡʱ�䣨�������ʼֵ������λ���룺10-9
	inline double time_n() const { return delta_n(_startTick, tick()); }  // ns

	// ����ʱ����
	inline double delta_s( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return (double)(t2 - t1)*_secsPerTick; } // ��
	inline double delta_m( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e3; }  // milliseconds
	inline double delta_u( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e6; }  // microseconds
	inline double delta_n( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e9; }  // nanoseconds

    // ��ȡÿ��tick�Ƕ�����
	inline double getSecondsPerTick() const { return _secsPerTick; }

protected :

	CVBF_Timer_t _startTick;   // ��ʼʱ��tick
	double		 _secsPerTick; // ÿ��tick�Ƕ�����
};

// ��ȡ���ʱ�䣬��CVBF_Timer�ļ�
class CVBF_ElapsedTime
{
public:
	inline CVBF_ElapsedTime(double* elapsedTime, CVBF_Timer* pTimer = 0): m_pTime(elapsedTime)
	{
		init(pTimer);
	}

	inline CVBF_ElapsedTime(CVBF_Timer* pTimer = 0): m_pTime(0)
	{
		init(pTimer);
	}

	inline ~CVBF_ElapsedTime()
	{
		finish();
	}

	inline void reset()
	{
		_startTick = m_pTimer->tick();
	}

	inline double elapsedTime() const   // ��
	{
		return m_pTimer->delta_s(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_m() const // ����
	{
		return m_pTimer->delta_m(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_u() const // ΢��
	{
		return m_pTimer->delta_u(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_n() const // ����
	{
		return m_pTimer->delta_n(_startTick, m_pTimer->tick());
	}

	inline void finish()
	{
		CVBF_Timer_t endTick = m_pTimer->tick();
		if (m_pTime) *m_pTime += m_pTimer->delta_s(_startTick, endTick);
		_startTick = endTick;
	}

protected:
	inline void init(CVBF_Timer* pTimer)
	{
		if (pTimer) m_pTimer = pTimer;
		else m_pTimer = CVBF_Timer::instance();

		_startTick = m_pTimer->tick();
	}

	double*		 m_pTime;	// ʱ�䣬�������ⲿ��������
	CVBF_Timer*  m_pTimer;	// ��ʱ��
	CVBF_Timer_t _startTick;

};

#endif
