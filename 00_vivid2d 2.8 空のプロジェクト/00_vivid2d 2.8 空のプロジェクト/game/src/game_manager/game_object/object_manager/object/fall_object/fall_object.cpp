#include "fall_object.h"

const	float	CFallObject::m_fall_speed = 10.0f;
CFallObject::CFallObject()
	: m_FallSpeed()
	, m_MarkID()
	, m_FallObjectState()
{
}

CFallObject::~CFallObject()
{
}

void CFallObject::Initialize(OBJECT_ID id, const CVector3& position)
{
	IObject::Initialize(id, position);
	m_FileName = "data\\Models\\cube.mv1";
	m_Transform.position = position;
	m_Model.Initialize(m_FileName, m_Transform.position);
}

void CFallObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
}

void CFallObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CFallObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool CFallObject::GetActive(void)
{
	return m_ActiveFlag;
}

void CFallObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}

MARK_ID CFallObject::GetID(void)
{
	return m_MarkID;
}