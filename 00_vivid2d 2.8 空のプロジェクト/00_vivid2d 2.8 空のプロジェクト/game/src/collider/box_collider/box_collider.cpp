#include "box_collider.h"

const std::string CBoxCollider::m_file_name = "data\\BoxCollider.mv1";
CBoxCollider::CBoxCollider()
	: m_Model()
	, m_Transform()
{
}

CBoxCollider::~CBoxCollider()
{
}

void CBoxCollider::Initialize(void)
{
	m_Model.Initialize(m_file_name, m_Transform.position);
}

void CBoxCollider::Update(void)
{
	m_Model.Update(m_Transform);
}

void CBoxCollider::Finalize(void)
{
	m_Model.Finalize();
}
