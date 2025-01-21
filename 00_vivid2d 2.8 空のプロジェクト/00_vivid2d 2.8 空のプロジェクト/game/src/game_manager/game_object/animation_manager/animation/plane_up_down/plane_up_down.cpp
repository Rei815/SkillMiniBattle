#include "plane_up_down.h"

const float		CPlaneUpDown::m_speed = 100.0f;
const float		CPlaneUpDown::m_up_time = 2.0f;
const CVector3	CPlaneUpDown::m_scale = CVector3(2.0f, 2.0f,1.0f);
const float		CPlaneUpDown::m_up_final_height = 4000.0f;
const CVector3	CPlaneUpDown::m_down_initial_position = CVector3(0.0f, 4000.0f, -1500.0f);
const float		CPlaneUpDown::m_down_final_height = 800.0f;
const float		CPlaneUpDown::m_end_time = 1.5f;
CPlaneUpDown::CPlaneUpDown()
{
}

CPlaneUpDown::~CPlaneUpDown()
{
}

void CPlaneUpDown::Initialize(void* plane_pointer)
{
	if (!plane_pointer) return;
	m_State = STATE::UP;
	m_Plane = (CPlaneGameImage*)plane_pointer;
	m_Timer.SetUp(m_up_time);
	m_StartValue = m_Plane->GetTransform().position.y;
	m_EaseTimer = 0.0f;
	m_FinishValue = m_up_final_height;

}

void CPlaneUpDown::Update()
{
	if (!m_Plane) return;
	CTransform transform = m_Plane->GetTransform().position;
	switch (m_State)
	{
	case CPlaneUpDown::STATE::WAIT:
		break;
	case CPlaneUpDown::STATE::UP:
		if (transform.position.y < m_up_final_height)
		{
			float current_y = Easing::InSine(m_EaseTimer, m_end_time, m_StartValue, m_FinishValue);

			transform.position.y = current_y;

			m_EaseTimer += vivid::GetDeltaTime();
		}
		else
		{
			transform.position = m_down_initial_position;
			transform.rotation.y = 0.0f;
			m_Plane->SetPosAngle(0.0f);
			m_Plane->SetSpeed(0.0f);
			m_StartValue = transform.position.y;
			m_EaseTimer = 0.0f;
			m_FinishValue = m_down_final_height;

			m_State = STATE::DOWN;
		}
		break;
	case CPlaneUpDown::STATE::DOWN:
		if (transform.position.y > m_down_final_height)
		{
			float current_y = Easing::OutQuart(m_EaseTimer, m_end_time, m_StartValue, m_FinishValue);

			transform.position.y = current_y;

			m_EaseTimer += vivid::GetDeltaTime();
		}
		else
		{
			transform.position.y = m_down_final_height;
			m_State = STATE::WAIT;
		}
		break;
	}
	m_Plane->SetTransform(transform);
}

void CPlaneUpDown::Finalize()
{
	m_Plane = nullptr;
}