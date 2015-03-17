/**
  @file timer.h
  
  @brief 计时器类，sr使用的时间接口

  @author Kaiming

  更改日志 history
  ver:1.0
   
 */

#ifndef timer_h__
#define timer_h__

class xTimer
{
public:
	xTimer():m_time(0)
		,m_elapsedTime(0)
	{

	}
	~xTimer()
	{

	}

	void Init()
	{
		QueryPerformanceFrequency(&m_freq); // 获取cpu时钟周期   

		m_time = getRealTime();
		m_elapsedTime = 0;
	}

	void Update()
	{
		float newTime = getRealTime();
		m_elapsedTime = newTime - m_time;
		m_time = newTime;
	}

	void Stop()
	{
		m_elapsedTime = 0;
	}

	float getElapsedTime()
	{
		return m_elapsedTime;
	}

	float getTime()
	{
		float newTime = getRealTime();
		return newTime;
	}

	float getRealTime()
	{
		LARGE_INTEGER now;
		QueryPerformanceFrequency(&m_freq);
		QueryPerformanceCounter(&now); // 获取cpu时钟计数
		return (float)(now.QuadPart)/m_freq.QuadPart;
	}

	LONGLONG getRealTick()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now); // 获取cpu时钟计数
		return now.QuadPart;
	}

	LONGLONG getRealFreq()
	{
		LARGE_INTEGER now;
		QueryPerformanceFrequency(&now); // 获取cpu时钟计数
		return now.QuadPart;
	}

private:
	float m_time;
	float m_elapsedTime;

	// high precision
	LARGE_INTEGER m_freq;
};

#endif