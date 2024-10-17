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

void CFallGimmick::Initialize(IObject* object, int delayFrame)
{
	CGimmick::Initialize(object, delayFrame);
	m_Object->SetGimmick(this);
}

void CFallGimmick::Update(void)
{
	if (!m_Switch) return;
	CGimmick::Update();
	if (m_Timer.Finished())
	{
		m_Timer.Reset();
		m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
	}
	m_Switch = false;

}

void CFallGimmick::Finalize(void)
{
}

void CFallGimmick::SetSwitch(bool sw)
{
	m_Switch = sw;

}
