#pragma once

class CTimer
{
public:
	CTimer();
	CTimer(float time);
	~CTimer();

	void Initialize();

	void SetUp(float time);

	void Update();

	void Reset();


	bool Finished();

	float		GetTimer();

	void		SetLimitTime(float time);

	float		GetLimitTime();

	bool		GetActive();

	void		SetActive(bool active);
private:
	float		m_LimitTime;
	float		m_Timer;
	bool		m_Active;
};