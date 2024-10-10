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
}

void CFallGimmick::Initialize(IObject* object, int delayFrame)
{
	CGimmick::Initialize(object, delayFrame);
}

void CFallGimmick::Update(void)
{
	CGimmick::Update();
	if (m_DelayFlag)
	{
		m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));

	}
}

void CFallGimmick::Finalize(void)
{
}