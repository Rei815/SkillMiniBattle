#pragma once

class CTimer
{
public:
	CTimer();
	~CTimer();

	void SetUp(float time);

	void Update();

	void Reset();

	bool Finished();

	float		GetTimer();
private:
	float		m_LimitTime;
	float		m_Timer;
};