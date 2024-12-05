#pragma once

class CTimer
{
public:
	CTimer();
	CTimer(float time);
	~CTimer();

	void SetUp(float time);

	void Update();

	void Reset();

	void AllReset();

	bool Finished();

	float		GetTimer();
private:
	float		m_LimitTime;
	float		m_Timer;
};