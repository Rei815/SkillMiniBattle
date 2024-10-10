#include "fall_object.h"

const	float			CFallObject::m_remove_height = -500.0f;
const	float			CFallObject::m_start_height = -100.0f;
const	unsigned int	CFallObject::m_invisible_color = 0x00ffffff;
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
	m_Timer.SetUp(1.0f);
}

void CFallObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
	if (m_Transform.position.y <= m_remove_height)
	{
		m_Transform.position.y = m_remove_height;
		m_Color = m_invisible_color;

	}
	if(m_Color == m_invisible_color)
		m_Timer.Update();

	if (m_Timer.Finished())
	{
		m_Transform.position.y = m_start_height;
		m_Color = 0xfffffff;
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