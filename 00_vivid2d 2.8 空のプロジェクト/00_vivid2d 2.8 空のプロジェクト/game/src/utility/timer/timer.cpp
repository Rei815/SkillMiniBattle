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
	m_LimitTime = 0;
	m_Timer = 0;
}

void CTimer::SetUp(float time, COUNT_TYPE count_type)
{
	switch (count_type)
	{
	case CTimer::COUNT_TYPE::UP:
		m_LimitTime = time;
		m_Timer = 0;
		break;
	case CTimer::COUNT_TYPE::DOWN:
		m_LimitTime = 0;
		m_Timer = time;
		m_StartTime = time;
		break;
	default:
		break;
	}
	m_CountType = count_type;
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

bool CTimer::Finished()
{
	if (!m_Active) return false;
	switch (m_CountType)
	{
	case CTimer::COUNT_TYPE::UP:	return m_Timer >= m_LimitTime; break;
	case CTimer::COUNT_TYPE::DOWN:	return m_Timer <= m_LimitTime; break;
	}
}

float CTimer::GetTimer()
{
	return m_Timer;
}

void CTimer::SetLimitTime(float time)
{
	m_LimitTime = time;
}

float CTimer::GetLimitTime()
{
	return m_LimitTime;
}

bool CTimer::GetActive()
{
	return m_Active;
}

void CTimer::SetActive(bool active)
{
	m_Active = active;
}
