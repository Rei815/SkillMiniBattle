#include "timer.h"
#include "vivid.h"
CTimer::CTimer()
	: m_LimitTime(0)
	, m_Timer(0)
	, m_Active(true)
	, m_CountType(COUNT_TYPE::UP)
	, m_StartTime(0)
{
}


CTimer::CTimer(float time)
	: m_LimitTime(time)
	, m_Timer(0)
	, m_Active(true)
	, m_CountType(COUNT_TYPE::UP)
	, m_StartTime(0)
{

}

CTimer::~CTimer()
{
}

void CTimer::Initialize()
{
	SetUp(0.0f, COUNT_TYPE::UP);
	Reset();
	m_Active = true;
}

void CTimer::SetUp(float limit_time, COUNT_TYPE count_type)
{
	m_CountType = count_type;
	// カウントタイプに応じてタイマーと制限時間を設定
	if (m_CountType == COUNT_TYPE::UP)
	{
		m_LimitTime = limit_time;
		m_Timer = 0.0f;
	}
	else // COUNT_TYPE::DOWN
	{
		m_LimitTime = 0.0f;			// ダウンカウントの場合、m_LimitTime は終了値（通常は0）
		m_Timer = limit_time;		// m_Timer を開始値に設定
		m_StartTime = limit_time;	// 開始時間も保存
	}
}

void CTimer::Update()
{
	if (!m_Active || Finished()) return;
	switch (m_CountType)
	{
	case CTimer::COUNT_TYPE::UP:
		m_Timer += vivid::GetDeltaTime();
		break;
	case CTimer::COUNT_TYPE::DOWN:
		m_Timer -= vivid::GetDeltaTime();
		break;
	}
}

void CTimer::Reset()
{
	switch (m_CountType)
	{
	case CTimer::COUNT_TYPE::UP:
		m_Timer = 0;
		break;
	case CTimer::COUNT_TYPE::DOWN:
		m_Timer = m_StartTime;
		break;
	}
}

bool CTimer::Finished() const
{
	if (!m_Active) return false;

	// カウントタイプに応じて条件を切り替える
	return (m_CountType == COUNT_TYPE::UP) ? (m_Timer >= m_LimitTime) : (m_Timer <= m_LimitTime);
}

float CTimer::GetTimer() const
{
	return m_Timer;
}

void CTimer::SetLimitTime(float limit_time)
{
	m_LimitTime = limit_time;
}

float CTimer::GetLimitTime() const
{
	return m_LimitTime;
}

bool CTimer::IsActive() const
{
	return m_Active;
}

void CTimer::SetActive(bool active)
{
	m_Active = active;
}
