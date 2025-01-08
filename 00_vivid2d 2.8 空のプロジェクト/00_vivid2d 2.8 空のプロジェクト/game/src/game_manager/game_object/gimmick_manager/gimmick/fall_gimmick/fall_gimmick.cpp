#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const	float				CFallGimmick::m_fall_speed = 5.0f;
const	float				CFallGimmick::m_remove_height = -500.0f;
const	float				CFallGimmick::m_remove_time = 3.0f;
CFallGimmick::CFallGimmick()
	: CGimmick()
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object);
	m_Object->SetGimmick(this);
	m_StartHeight = m_Object->GetPosition().y;
}

void CFallGimmick::Initialize(IObject* object, float time)
{
	CGimmick::Initialize(object, time);
	m_Object->SetGimmick(this);
}

void CFallGimmick::Update(void)
{
	CGimmick::Update();
	m_Timer.Update();
	CVector3 objectPos = m_Object->GetPosition();
	float alpha = 0.0f;
	switch (m_State)
	{
	case GIMMICK_STATE::WAIT:
		break;
	case GIMMICK_STATE::PLAY:
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Timer.SetActive(false);
			m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
		}
		alpha = (objectPos.y - m_remove_height) / (m_StartHeight - m_remove_height);
		m_Object->SetAlpha(alpha);
		if (m_Object->GetPosition().y <= m_remove_height)
		{
			m_Timer.SetActive(true);
			m_Timer.SetUp(m_remove_time);
			m_Object->SetVelocity(CVector3::ZERO);
			m_Object->SetColliderActiveFlag(false);
			m_State = GIMMICK_STATE::FINISH;
		}
		break;
	case GIMMICK_STATE::FINISH:
		if (m_Timer.Finished())
		{
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