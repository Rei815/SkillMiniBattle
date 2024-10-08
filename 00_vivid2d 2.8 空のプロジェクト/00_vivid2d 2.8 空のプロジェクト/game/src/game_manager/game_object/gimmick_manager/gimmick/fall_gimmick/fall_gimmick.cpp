#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const float	CFallGimmick::m_fall_speed = 10.0f;
CFallGimmick::CFallGimmick()
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize(IObject* object)
{
	m_Object = object;
	m_Object->SetVelocity(CVector3(0, -m_fall_speed, 0));
}

void CFallGimmick::Update(void)
{
}

void CFallGimmick::Finalize(void)
{
}