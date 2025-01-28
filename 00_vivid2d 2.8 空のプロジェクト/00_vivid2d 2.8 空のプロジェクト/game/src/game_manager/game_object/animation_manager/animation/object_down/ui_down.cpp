//#include "ui_down.h"
//
//const float		CUIDown::m_speed = 100.0f;
//const float		CUIDown::m_up_time = 2.0f;
//const CVector3	CUIDown::m_scale = CVector3(2.0f, 2.0f, 1.0f);
//const float		CUIDown::m_up_final_height = 4000.0f;
//const CVector3	CUIDown::m_down_initial_position = CVector3(0.0f, 4000.0f, -1500.0f);
//const float		CUIDown::m_down_final_height = 800.0f;
//const float		CUIDown::m_end_time = 1.5f;
//CUIDown::CUIDown()
//{
//}
//
//CUIDown::~CUIDown()
//{
//}
//
//void CUIDown::Initialize(void* ui_pointer)
//{
//	if (!ui_pointer) return;
//
//	m_UI = (CUI*)ui_pointer;
//	m_StartValue = m_UI->GetTransform().position.y;
//	m_EaseTimer = 0.0f;
//	m_FinishValue = m_down_final_height;
//
//}
//
//void CUIDown::Update()
//{
//	//if (!m_UI) return;
//	CTransform transform = m_UI->GetTransform().position;
//		if (transform.position.y < m_up_final_height)
//		{
//			float current_y = Easing::OutSine(m_EaseTimer, m_end_time, m_StartValue, m_FinishValue);
//
//			transform.position.y = current_y;
//
//			m_EaseTimer += vivid::GetDeltaTime();
//		}
//		else
//		{
//			transform.position = m_down_initial_position;
//			transform.rotation.y = 0.0f;
//			m_UI->SetPosAngle(0.0f);
//			m_UI->SetSpeed(0.0f);
//			m_StartValue = transform.position.y;
//			m_EaseTimer = 0.0f;
//			m_FinishValue = m_down_final_height;
//
//			m_State = STATE::DOWN;
//		}
//		break;
//	}
//	m_UI->SetTransform(transform);
//}
//
//void CUIDown
//::Finalize()
//{
//	//m_UI = nullptr;
//}