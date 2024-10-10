#include "object.h"

IObject::IObject()
	: m_Color(0xfffffff)
{
}

IObject::~IObject()
{
}

void IObject::Initialize(OBJECT_ID id, const CVector3& pos)
{
	m_ObjectID = id;
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

OBJECT_ID IObject::GetObjectID(void)
{
	return m_ObjectID;
}

bool IObject::GetActive(void)
{
	return m_ActiveFlag;
}

void IObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}

CVector3 IObject::GetPosition()
{
	return m_Transform.position;
}

void IObject::SetPosition(const CVector3& position)
{
	m_Transform.position = position;
}

void IObject::SetVelocity(const CVector3& velocity)
{
	m_Velocity = velocity;
}
