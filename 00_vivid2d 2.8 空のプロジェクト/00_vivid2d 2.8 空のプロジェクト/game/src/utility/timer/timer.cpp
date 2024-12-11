#include "timer.h"
#include "vivid.h"
CTimer::CTimer()
	: m_LimitTime(0)
	, m_Timer(0)
	, m_Active(true)
{
}


CTimer::CTimer(float time)
	: m_LimitTime(time)
	, m_Timer(0)
	, m_Active(true)
{

}

CTimer::~CTimer()
{
}

void CTimer::SetUp(float time)
{
	m_LimitTime = time;
	m_Timer = 0;
}

void CTimer::Update()
{
	if (!m_Active) return;

	m_Timer += vivid::GetDeltaTime();
}

void CTimer::Reset()
{
	m_Timer = 0;
}

void CTimer::Initialize()
{
	m_LimitTime = 0;
	m_Timer = 0;
}

bool CTimer::Finished()
{
	return m_Timer >= m_LimitTime;
}

float CTimer::GetTimer()
{
	return m_Timer;
}

float CTimer::GetLimitTime()
{
	return m_LimitTime;
}

void CTimer::SetActive(bool active)
{
	m_Active = active;
}
