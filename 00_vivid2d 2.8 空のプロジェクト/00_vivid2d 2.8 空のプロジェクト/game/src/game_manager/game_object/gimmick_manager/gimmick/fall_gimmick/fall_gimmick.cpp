#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const float	CFallGimmick::m_fall_speed = 5.0f;
CFallGimmick::CFallGimmick()
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object);
	m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
	m_Object->SetState(OBJECT_STATE::FALL);
}

void CFallGimmick::Initialize(IObject* object, int delayFrame)
{
	CGimmick::Initialize(object, delayFrame);
	m_Object->SetState(OBJECT_STATE::FALL);
}

void CFallGimmick::Update(void)
{
	CGimmick::Update();
	if (m_DelayFlag)
	{
		m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
	}
	if (m_Object->GetState() == OBJECT_STATE::FALL_FINISH)
		m_ActiveFlag = false;

}

void CFallGimmick::Finalize(void)
{
}