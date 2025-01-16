#include "plane_up_down.h"

const float CPlaneUpDown::m_speed = 100.0f;
const vivid::Vector2 CPlaneUpDown::m_min_position = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2 CPlaneUpDown::m_max_position = vivid::Vector2(5.0f, 5.0f);
CPlaneUpDown::CPlaneUpDown()
{
}

CPlaneUpDown::~CPlaneUpDown()
{
}

void CPlaneUpDown::Initialize(void* plane_pointer)
{
	if (!plane_pointer) return;
	m_Plane = (CUI*)plane_pointer;
}

void CPlaneUpDown::Update()
{
	if (!m_Plane) return;

	CTransform transform = m_Plane->GetTransform().position;
	transform.position.y += m_speed;
	m_Plane->SetTransform(transform);
}

void CPlaneUpDown::Finalize()
{
	m_Plane = nullptr;
}
