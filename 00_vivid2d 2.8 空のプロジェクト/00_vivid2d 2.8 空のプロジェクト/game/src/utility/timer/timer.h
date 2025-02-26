#pragma once

class CTimer
{
public:

	//カウントの方法
	enum class COUNT_TYPE
	{
		UP,
		DOWN
	};
	CTimer();
	CTimer(float time);
	~CTimer();

	void Initialize();

	void SetUp(float time, COUNT_TYPE count_type = COUNT_TYPE::UP);

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
	float		m_StartTime;
	float		m_Timer;
	bool		m_Active;
	COUNT_TYPE	m_CountType;
};