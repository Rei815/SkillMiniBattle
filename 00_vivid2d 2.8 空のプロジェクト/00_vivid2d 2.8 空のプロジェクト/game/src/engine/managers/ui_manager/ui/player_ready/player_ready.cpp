#include "player_ready.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\controller_manager\controller_manager.h"
const std::string		CPlayerReady::m_file_names[] = {
	"data\\Textures\\player_icon_1.png",
	"data\\Textures\\player_icon_2.png",
	"data\\Textures\\player_icon_3.png",
	"data\\Textures\\player_icon_4.png"
};
const int               CPlayerReady::m_width = 164;
const int               CPlayerReady::m_height = 69;
const vivid::Vector2    CPlayerReady::m_offset = vivid::Vector2(100.0f, 0.0f);
const vivid::Vector2    CPlayerReady::m_position = vivid::Vector2(800.0f, 600.0f);
const vivid::Rect       CPlayerReady::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerReady::m_scale = vivid::Vector2(0.5f, 0.7f);
const vivid::Vector2    CPlayerReady::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const unsigned int		CPlayerReady::m_color[] = { 0xff808080,0xff808080 ,0xff808080, 0xff808080 };
CPlayerReady::CPlayerReady(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_ReadyFlag(false)
{
	for (int i = 0; i < 4; i++)
	{
		m_Color[i] = m_color[i];
	}
}

CPlayerReady::~CPlayerReady()
{
}

void CPlayerReady::Initialize()
{
	CUI::Initialize(m_position);
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		m_Color[i] = m_color[i];
	}
}

void CPlayerReady::Update(void)
{
	CUI::Update();
	if (m_ReadyFlag == true) return;
	CControllerManager& cm = CControllerManager::GetInstance();
	std::shared_ptr<CController> controller1 = cm.GetController(CONTROLLER_ID::ONE);
	std::shared_ptr<CController> controller2 = cm.GetController(CONTROLLER_ID::TWO);
	std::shared_ptr<CController> controller3 = cm.GetController(CONTROLLER_ID::THREE);
	std::shared_ptr<CController> controller4 = cm.GetController(CONTROLLER_ID::FOUR);
	std::shared_ptr<CController> keyboard = cm.GetController(CONTROLLER_ID::KEYBOARD);
	if (controller1)
		if (controller1->GetButtonDown(BUTTON_ID::B))
			m_Color[(int)controller1->GetPlayerID()] ^= 0x007f7f7f;
	if (controller2)
		if (controller2->GetButtonDown(BUTTON_ID::B))
			m_Color[(int)controller2->GetPlayerID()] ^= 0x007f7f7f;
	if (controller3)
		if (controller3->GetButtonDown(BUTTON_ID::B))
			m_Color[(int)controller3->GetPlayerID()] ^= 0x007f7f7f;
	if (controller4)
		if (controller4->GetButtonDown(BUTTON_ID::B))
			m_Color[(int)controller4->GetPlayerID()] ^= 0x007f7f7f;
	if (keyboard)
		if (keyboard->GetButtonDown(BUTTON_ID::B))
			m_Color[(int)keyboard->GetPlayerID()] ^= 0x007f7f7f;

	if (CDataManager::GetInstance().GetCurrentJoinPlayer() == 2 && cm.GetController(CONTROLLER_ID::DUMMY)->GetPlayerID() == PLAYER_ID::PLAYER2)
		m_Color[(int)PLAYER_ID::PLAYER2] = 0xffffffff;

	
#if _DEBUG
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD1))
	{
		m_Color[0] ^= 0x007f7f7f;
	}
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD2))
	{
		m_Color[1] ^= 0x007f7f7f;
	}
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD3))
	{
		m_Color[2] ^= 0x007f7f7f;
	}
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD4))
	{
		m_Color[3] ^= 0x007f7f7f;
	}

 #endif // _DEBUG


	bool flag = false;
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		if (m_Color[i] == 0xffffffff)
			flag = true;
		else
		{
			flag = false;
			break;
		}
	}
	if (flag == true)
		m_ReadyFlag = true;
}

void CPlayerReady::Draw(void)
{
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		vivid::DrawTexture(m_file_names[i], m_Position + (m_offset * i), m_Color[i], m_rect, m_anchor, m_scale);
	}
}

void CPlayerReady::Finalize(void)
{
}

bool CPlayerReady::GetReadyFlag()
{
	return m_ReadyFlag;
}
