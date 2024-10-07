#include "fall_object.h"

const	float	CFallObject::m_fall_speed = 10.0f;
CFallObject::CFallObject()
	: m_Model()
	, m_Transform()
	, m_FileName()
	, m_FallSpeed()
	, m_MarkID()
	, m_FallObjectState()
	, m_ActiveFlag()
{
}

CFallObject::~CFallObject()
{
}

void CFallObject::Initialize(MARK_ID id, const CVector3& position)
{
	m_MarkID = id;
	m_FallObjectState = FALL_OBJECT_STATE::WAIT;
	switch (id)
	{
	case MARK_ID::CIRCLE:	m_FileName = "data\\Models\\cube.mv1";	break;
	case MARK_ID::STAR:		m_FileName = "data\\Models\\cube.mv1";	break;
	}
	m_Transform.position = position;
	m_Model.Initialize(m_FileName,m_Transform.position);

	m_FallSpeed = m_fall_speed;
}

void CFallObject::Update(void)
{
	switch (m_FallObjectState)
	{
	case FALL_OBJECT_STATE::WAIT:
		break;
	case FALL_OBJECT_STATE::FALL:
		break;
	}
	if (m_FallObjectState == FALL_OBJECT_STATE::FALL)
		m_Transform.position.y -= m_FallSpeed;
	m_Model.Update(m_Transform);
}

void CFallObject::Draw(void)
{
	m_Model.Draw();
}

void CFallObject::Finalize(void)
{
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

void CFallObject::SetState(FALL_OBJECT_STATE state)
{
	m_FallObjectState = state;
}
