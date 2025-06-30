#include "player_icon.h"

const int               CPlayerIcon::m_width = 164;
const int               CPlayerIcon::m_height = 69;
const vivid::Vector2    CPlayerIcon::m_position = vivid::Vector2(800.0f, 600.0f);
const vivid::Rect       CPlayerIcon::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerIcon::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CPlayerIcon::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const std::string		CPlayerIcon::m_file_name[] = {
	"data\\Textures\\player_icon_1.png",
	"data\\Textures\\player_icon_2.png",
	"data\\Textures\\player_icon_3.png",
	"data\\Textures\\player_icon_4.png"
};

CPlayerIcon::CPlayerIcon(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_PlayerID(0)
{
}

CPlayerIcon::~CPlayerIcon(void)
{
}

void CPlayerIcon::Initialize(void)
{
	CUI::Initialize(m_position);
}

void CPlayerIcon::Update(void)
{
	CUI::Update();
}

void CPlayerIcon::Draw(void)
{
	vivid::DrawTexture(m_file_name[m_PlayerID], m_Position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CPlayerIcon::Finalize(void)
{
}

void CPlayerIcon::SetPlayerID(UNIT_ID unit_id)
{
	m_PlayerID = (int)unit_id;
}
