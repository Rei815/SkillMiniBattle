#include "plane_up.h"
#include "..\..\..\ui_manager\ui_manager.h"
const float		CPlaneUp::m_speed = 100.0f;
const float		CPlaneUp::m_up_time = 2.0f;
const float		CPlaneUp::m_up_final_height = 2000.0f;
const CVector3	CPlaneUp::m_down_initial_position = CVector3(-200.0f, 1400.0f, -500.0f);
const float		CPlaneUp::m_end_time = 1.5f;
CPlaneUp::CPlaneUp()
{
}

CPlaneUp::~CPlaneUp()
{
}

void CPlaneUp::Initialize(void* plane_pointer)
{
	if (!plane_pointer) return;
	m_Plane = (CPlaneGameImage*)plane_pointer;
	m_Timer.SetUp(m_up_time);
	m_StartValue = m_Plane->GetTransform().position.y;
	m_EaseTimer = 0.0f;
	m_FinishValue = m_up_final_height;
	m_Plane->SetSpeed(0.0f);

}

void CPlaneUp::Update()
{
	if (!m_Plane) return;
	CTransform transform = m_Plane->GetTransform();
	if (transform.position.y < m_up_final_height)
	{
		float current_y = Easing::InBack(m_EaseTimer, m_end_time, m_StartValue, m_FinishValue);

		transform.position.y = current_y;

		m_EaseTimer += vivid::GetDeltaTime();
	}
	else
	{
		transform.position = m_down_initial_position;
		transform.rotation.y = 0.0f;

		m_Plane->SetPosAngle(0.0f);
		m_Plane->SetOrderInLayer(1);
		vivid::Vector2 bgPos = vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() / 2);
		CUIManager::GetInstance().Create(UI_ID::MENU_BG, bgPos);
		CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT);

		m_ActiveFlag = false;
	}
	m_Plane->SetTransform(transform);
}

void CPlaneUp::Finalize()
{
	m_Plane = nullptr;
}