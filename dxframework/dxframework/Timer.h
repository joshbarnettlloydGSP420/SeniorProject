#pragma once
#include <windows.h>

class CTimer
{
	INT64			m_ticksPerSecond;
	INT64			m_currentTime;
	INT64			m_lastTime;
	INT64			m_lastFPSUpdate;
	INT64			m_FPSUpdateInterval;
	unsigned int	m_numFrames;
	float			m_runningTime;
	float			m_timeElapsed;
	float			m_FPS;
	bool			m_timerStopped;
	
	// making a nice looking clock
	int minutes;
	int seconds;
	int miliseconds;

public:
	CTimer(void);
	~CTimer(void);

	void Start(void);
	void Stop(void);
	void Update(void);
	void DisplayTime(void);

	inline bool IsStopped(void) { return m_timerStopped; }
	inline float GetFPS(void) { return m_FPS; }
	inline float GetRunningTime(void) { return m_runningTime; }
	inline float GetElapsedTime(void) { return m_timerStopped ? 0.0f : m_timeElapsed; }

	//getting seconds and minutes
	inline float GetSeconds(void) { return seconds; }
	inline float GetMinutes(void) { return minutes; }

};
