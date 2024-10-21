#include "object.h"

const float IObject::m_limit_alpha = 1.0f;
IObject::IObject()
	: m_Alpha(m_limit_alpha)
	, m_Velocity()
{
}

IObject::~IObject()
{
}

void IObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_ObjectID = id;
	m_Transform = transform;
}

void IObject::Update(void)
{
	m_Transform.position += m_Velocity;
}

void IObject::Draw(void)
{
	MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);
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

CVector3 IObject::GetRotation()
{
	return m_Transform.rotation;
}

void IObject::SetRotation(const CVector3& rotation)
{
	m_Transform.rotation = rotation;
}

void IObject::SetVelocity(const CVector3& velocity)
{
	m_Velocity = velocity;
}

CModel IObject::GetModel()
{
	return m_Model;
}

void IObject::SetGimmick(CGimmick* gimmick)
{
	m_Gimmick = gimmick;
}

CGimmick* IObject::GetGimmick()
{
	return m_Gimmick;
}

std::string IObject::GetTag()
{
	return m_Tag;
}
