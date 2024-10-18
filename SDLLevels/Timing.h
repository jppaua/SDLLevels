#ifndef TIMING_H
#define TIMING_H

#include "StandardIncludes.h"

class Timing : public Singleton<Timing>
{
public:
	Timing();
	virtual ~Timing();

	unsigned int GetFPS() { return m_fpsLast; }
	float GetDeltaTime() { return m_deltaTime; }
	float GetTotalGameTime() { return m_totalGameTime; }  // New method

	void Tick();

private:
	unsigned int m_currentTime;
	unsigned int m_lastTime;
	unsigned int m_fpsStart;
	unsigned int m_fpsCount;
	unsigned int m_fpsLast;
	float m_deltaTime;
	float m_totalGameTime; // New variable to store total game time
};

#endif // !TIMING_H

