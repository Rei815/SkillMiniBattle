#include "plane_scale.h"
#include "..\..\..\ui_manager\ui_manager.h"
const float CPlaneScale::m_speed = 0.01f;
const CVector3 CPlaneScale::m_min_scale = CVector3(0.0f, 0.0f, 0.0f);
CPlaneScale::CPlaneScale()
	: m_Plane(nullptr)
{
}

CPlaneScale::~CPlaneScale()
{
}

void CPlaneScale::Initialize(std::shared_ptr<void> plane_pointer)
{
	m_Plane = std::static_pointer_cast<CPlaneGameImage>(plane_pointer);
	if (!m_Plane) return;

	m_Plane->SetSpeed(0.0f);

}

void CPlaneScale::Update()
{
	if (!m_Plane)
	{
		return;
	}

	CTransform transform = m_Plane->GetTransform();
	CVector3 scale = transform.scale;
	scale.x -= m_speed;
	scale.y -= m_speed;
	scale.z -= m_speed;
	transform.scale = scale;
	m_Plane->SetTransform(transform);
	if (scale.x <= m_min_scale.x || scale.y <= m_min_scale.y || scale.z <= m_min_scale.z)
	{
		m_ActiveFlag = false;
		m_Plane->Delete();
	}
}

void CPlaneScale::Finalize()
{
}
