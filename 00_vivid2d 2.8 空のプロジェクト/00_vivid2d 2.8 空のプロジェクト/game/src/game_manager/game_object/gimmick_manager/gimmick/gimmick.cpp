#include "gimmick.h"

CGimmick::CGimmick()
	: m_Object(nullptr)
	, m_DelayTime()
	, m_DelayTimer()
	, m_DelayFlag(false)
	, m_Timer()
{
}

CGimmick::~CGimmick(void)
{
}

void CGimmick::Initialize(IObject* object)
{
	m_Object = object;
}

void CGimmick::Initialize(IObject* object, float time)
{
	m_Object = object;
	m_DelayTime = time;
	m_Timer.SetUp(time);


}

void CGimmick::Update(void)
{
	if (m_DelayFlag) return;

	m_Timer.Update();

	if (m_Timer.Finished())
	{
		m_DelayFlag = true;
	}

}

void CGimmick::Draw(void)
{
}

void CGimmick::Finalize(void)
{
}

GIMMICK_ID CGimmick::GetGimmickID(void)
{
	return GIMMICK_ID();
}

bool CGimmick::GetActive(void)
{
	return m_ActiveFlag;
}

void CGimmick::SetActive(bool active)
{
	m_ActiveFlag = active;
}
