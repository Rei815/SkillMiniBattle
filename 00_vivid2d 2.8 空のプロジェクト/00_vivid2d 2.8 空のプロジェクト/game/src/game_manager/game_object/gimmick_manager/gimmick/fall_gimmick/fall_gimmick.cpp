#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const	float				CFallGimmick::m_fall_speed = 5.0f;
const	float				CFallGimmick::m_return_height = -500.0f;
const	float				CFallGimmick::m_return_time = 3.0f;
CFallGimmick::CFallGimmick()
	: CGimmick()
	, m_ReturnTime(m_return_time)
	, m_StartHeight(0.0f)
	, m_ReturnTimer(m_return_time)
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object);
	object->SetGimmick(this);
	m_StartHeight = object->GetPosition().y;
	m_Timer.SetUp(m_ReturnTime);
	m_ReturnTimer.SetUp(m_ReturnTime);
}

void CFallGimmick::Update(void)
{
	CGimmick::Update();
	CVector3 objectPos = m_Object->GetPosition();
	float alpha = 0.0f;
	switch (m_State)
	{
	case GIMMICK_STATE::WAIT:
		break;
	case GIMMICK_STATE::PLAY:
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Timer.SetActive(false);
			m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
		}
		alpha = (objectPos.y - m_return_height) / (m_StartHeight - m_return_height);
		m_Object->SetAlpha(alpha);

		if (alpha <= 0.5f)
			m_Object->SetColliderActiveFlag(false);
		if (m_Object->GetPosition().y <= m_return_height)
		{
			m_Timer.SetActive(true);
			m_Timer.SetUp(m_ReturnTime);
			m_Object->SetVelocity(CVector3::ZERO);
			m_State = GIMMICK_STATE::FINISH;
		}
		break;
	case GIMMICK_STATE::FINISH:
		m_ReturnTimer.Update();
		if (m_ReturnTimer.Finished())
		{
			m_ReturnTimer.Reset();
			objectPos.y = m_StartHeight;
			m_Object->SetPosition(objectPos);
			m_Object->SetAlpha(1.0f);
			m_Object->SetColliderActiveFlag(true);

			m_State = GIMMICK_STATE::WAIT;
		}
		break;
	}

}
void CFallGimmick::Finalize(void)
{
}

void CFallGimmick::AddReturnTime(float time)
{
	m_ReturnTime += time;
	m_ReturnTimer.SetUp(m_ReturnTime);
}
