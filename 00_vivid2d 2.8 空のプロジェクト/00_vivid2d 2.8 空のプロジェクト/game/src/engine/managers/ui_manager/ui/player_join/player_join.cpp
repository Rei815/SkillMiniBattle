#include "player_join.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\unit_manager\unit_manager.h"
#include "..\..\..\controller_manager\controller_manager.h"
const std::string		CPlayerJoin::m_file_names[] = {
	"data\\Textures\\player_icon_1.png",
	"data\\Textures\\player_icon_2.png",
	"data\\Textures\\player_icon_3.png",
	"data\\Textures\\player_icon_4.png"
};
const int               CPlayerJoin::m_width = 164;
const int               CPlayerJoin::m_height = 69;
const vivid::Vector2    CPlayerJoin::m_offset = vivid::Vector2(0.0f, 100.0f);
const vivid::Vector2    CPlayerJoin::m_position = vivid::Vector2(1100.0f, 150.0f);
const vivid::Rect       CPlayerJoin::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerJoin::m_scale = vivid::Vector2(1.0f, 1.2f);
const vivid::Vector2    CPlayerJoin::m_anchor = vivid::Vector2(m_width / 2.0f, m_height / 2.0f);
const unsigned int		CPlayerJoin::m_color_dark = 0xff808080;
const unsigned int		CPlayerJoin::m_color_light = 0xffffffff;

CPlayerJoin::CPlayerJoin(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CPlayerJoin::~CPlayerJoin()
{
}

void CPlayerJoin::Initialize()
{
	CUI::Initialize(m_position);

	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		m_Color[i] = m_color_dark;
	}
}

void CPlayerJoin::Update(void)
{
	CUI::Update();
}

void CPlayerJoin::Draw(void)
{
	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		vivid::DrawTexture(m_file_names[i], m_Position + (m_offset * i), m_Color[i], m_rect, m_anchor, m_scale);
	}
}

void CPlayerJoin::Finalize(void)
{
}


void CPlayerJoin::SetPlayer(UNIT_ID id, bool join)
{
	if (join)
		m_Color[(int)id] = m_color_light;
	else
		m_Color[(int)id] = m_color_dark;
}
