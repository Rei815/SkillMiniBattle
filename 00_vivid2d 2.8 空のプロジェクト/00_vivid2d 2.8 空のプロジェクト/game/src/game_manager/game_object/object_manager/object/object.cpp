#include "object.h"

IObject::IObject()
{
}

IObject::~IObject()
{
}

void IObject::Initialize(const CVector3& pos)
{
	m_Transform.position = pos;
}

void IObject::Update(void)
{
	m_Transform.position += m_Velocity;
}

void IObject::Draw(void)
{
}

void IObject::Finalize(void)
{
}

bool IObject::GetActive(void)
{
	return m_ActiveFlag;
}

void IObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}
