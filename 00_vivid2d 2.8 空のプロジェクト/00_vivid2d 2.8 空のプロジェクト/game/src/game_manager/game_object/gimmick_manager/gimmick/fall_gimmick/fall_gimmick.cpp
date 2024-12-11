#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const float	CFallGimmick::m_fall_speed = 5.0f;
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

}

void CFallGimmick::Initialize(IObject* object, float time)
{
	CGimmick::Initialize(object, time);
	m_Object->SetGimmick(this);
}

void CFallGimmick::Update(void)
{
	CGimmick::Update();
	switch (m_State)
	{
	case GIMMICK_STATE::WAIT:
		break;
	case GIMMICK_STATE::PLAY:
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
			m_State = GIMMICK_STATE::FINISH;
		}
		break;
	case GIMMICK_STATE::FINISH:
		break;
	}

}
void CFallGimmick::Finalize(void)
{
}