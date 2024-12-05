#include "timer.h"
#include "vivid.h"
CTimer::CTimer()
	: m_LimitTime(0)
	, m_Timer(0)
{
}


CTimer::CTimer(float time)
	: m_LimitTime(time)
	, m_Timer(0)
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
	m_Timer += vivid::GetDeltaTime();
}

void CTimer::Reset()
{
	m_Timer = 0;
}

void CTimer::AllReset()
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
