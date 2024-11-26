#include "ogre_object.h"

const	float			COgreObject::m_remove_height = -500.0f;
const	float			COgreObject::m_start_height = -100.0f;
const	float			COgreObject::m_invisible_alpha = 0.0f;
const	std::string		COgreObject::m_file_name = "data\\Models\\ogre.mv1";

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


	m_FileName = m_file_name;
	m_Transform = transform;
	m_Model.Initialize(m_FileName, m_Transform.position);
	m_Timer.SetUp(1.0f);
}

void COgreObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
}

void COgreObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
	vivid::DrawText(30, std::to_string((int)m_Gimmick->GetState()), vivid::Vector2(500,500));
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