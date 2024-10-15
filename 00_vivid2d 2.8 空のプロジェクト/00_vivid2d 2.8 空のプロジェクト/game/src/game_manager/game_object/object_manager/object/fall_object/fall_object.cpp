#include "fall_object.h"

const	float			CFallObject::m_remove_height = -500.0f;
const	float			CFallObject::m_start_height = -100.0f;
const	float			CFallObject::m_invisible_alpha = 0.0f;
CFallObject::CFallObject()
	: IObject()
	, m_FallSpeed()
	, m_MarkID()
	, m_FallObjectState()
{
}

CFallObject::~CFallObject()
{
}

void CFallObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	IObject::Initialize(id, transform);
	switch (id)
	{
	case OBJECT_ID::NONE:
		break;
	case OBJECT_ID::MOON_FALL_OBJECT:
		break;
	case OBJECT_ID::SUN_FALL_OBJECT:
		break;
	case OBJECT_ID::CIRCLE_FALL_OBJECT:
		break;
	case OBJECT_ID::SQUARE_FALL_OBJECT:
		break;
	case OBJECT_ID::TRIANGLE_FALL_OBJECT:
		break;
	case OBJECT_ID::CROSS_FALL_OBJECT:
		break;
	case OBJECT_ID::MAX:
		break;
	default:
		break;
	}
	m_FileName = "data\\Models\\cube.mv1";
	m_Transform = transform;
	m_Model.Initialize(m_FileName, m_Transform.position);
	m_Timer.SetUp(1.0f);
	m_State = OBJECT_STATE::WAIT;
}

void CFallObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
	if (m_Transform.position.y <= m_remove_height)
	{
		m_Transform.position.y = m_remove_height;
		m_Alpha = m_invisible_alpha;
	}
	if (m_Alpha == m_invisible_alpha)
	{
		m_State = OBJECT_STATE::FALL_FINISH;
		m_Timer.Update();
	}

	if (m_Timer.Finished())
	{
		m_Timer.Reset();
		m_Transform.position.y = m_start_height;
		m_Alpha = m_limit_alpha;
		m_Velocity = CVector3::ZERO;
		m_State = OBJECT_STATE::WAIT;
	}
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