#include "Ogre_object.h"

const	float			COgreObject::m_remove_height = -500.0f;
const	float			COgreObject::m_start_height = -100.0f;
const	float			COgreObject::m_invisible_alpha = 0.0f;
const	std::string		COgreObject::m_file_name = "data\\circle.mv1";


COgreObject::COgreObject()
	: IObject()
	, m_FallSpeed()
	, m_Daruma_FallDownObjectState()
{
}

COgreObject::~COgreObject()
{
}

void COgreObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	IObject::Initialize(id, transform);


	m_Transform = transform;
	m_Model.Initialize(m_FileName, m_Transform.position);
	m_Timer.SetUp(1.0f);
}

void COgreObject::Update(void)
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
		m_Timer.Update();
	}

	if (m_Timer.Finished())
	{
		m_Timer.Reset();
		m_Transform.position.y = m_start_height;
		m_Alpha = m_limit_alpha;
		m_Velocity = CVector3::ZERO;
	}
}

void COgreObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();

}

void COgreObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool COgreObject::GetActive(void)
{
	return m_ActiveFlag;
}

void COgreObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}