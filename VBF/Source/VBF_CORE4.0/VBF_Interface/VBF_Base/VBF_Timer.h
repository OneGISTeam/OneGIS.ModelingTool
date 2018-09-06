#ifndef VBF_TIMER_H
#define VBF_TIMER_H 1

#include <VBF_Base/VBF_BaseExport.h>


#if defined(_MSC_VER)
	typedef __int64 CVBF_Timer_t;
#else
	typedef unsigned long long CVBF_Timer_t;
#endif

// 计时器：可获取相对时间和时间间隔
class VBF_BASE_EXPORT CVBF_Timer 
{
public:

	CVBF_Timer();
    ~CVBF_Timer();

	static CVBF_Timer* instance();

    // 获取计时器的tick值
	CVBF_Timer_t tick() const;

	// 设置/获取计时器的起始值
	void setStartTick() { _startTick = tick(); }       
	void setStartTick(CVBF_Timer_t t) { _startTick = t; }   
	CVBF_Timer_t getStartTick() const { return _startTick; }


    // 获取时间（相对于起始值），单位秒
	inline double time_s() const { return delta_s(_startTick, tick()); }  // s
    // 获取时间（相对于起始值），单位毫秒
	inline double time_m() const { return delta_m(_startTick, tick()); }  // ms

    // 获取时间（相对于起始值），单位微秒：一百万分之一秒，10-6
	inline double time_u() const { return delta_u(_startTick, tick()); }  // us

    // 获取时间（相对于起始值），单位纳秒：10-9
	inline double time_n() const { return delta_n(_startTick, tick()); }  // ns

	// 计算时间间隔
	inline double delta_s( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return (double)(t2 - t1)*_secsPerTick; } // 秒
	inline double delta_m( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e3; }  // milliseconds
	inline double delta_u( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e6; }  // microseconds
	inline double delta_n( CVBF_Timer_t t1, CVBF_Timer_t t2 ) const { return delta_s(t1,t2)*1e9; }  // nanoseconds

    // 获取每个tick是多少秒
	inline double getSecondsPerTick() const { return _secsPerTick; }

protected :

	CVBF_Timer_t _startTick;   // 起始时的tick
	double		 _secsPerTick; // 每个tick是多少秒
};

// 获取相对时间，是CVBF_Timer的简化
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

	inline double elapsedTime() const   // 秒
	{
		return m_pTimer->delta_s(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_m() const // 毫秒
	{
		return m_pTimer->delta_m(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_u() const // 微秒
	{
		return m_pTimer->delta_u(_startTick, m_pTimer->tick());
	}

	inline double elapsedTime_n() const // 纳秒
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

	double*		 m_pTime;	// 时间，用于向外部传递数据
	CVBF_Timer*  m_pTimer;	// 计时器
	CVBF_Timer_t _startTick;

};

#endif
