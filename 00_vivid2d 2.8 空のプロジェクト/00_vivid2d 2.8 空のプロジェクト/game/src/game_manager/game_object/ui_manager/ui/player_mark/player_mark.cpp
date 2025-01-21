#include "player_mark.h"

const std::string		CPlayerMark::m_file_names[] = 
{"data\\Textures\\player1_mark.png","data\\Textures\\player2_mark.png","data\\Textures\\player3_mark.png","data\\Textures\\player4_mark.png"};
const int               CPlayerMark::m_width = 300;
const int               CPlayerMark::m_height = 200;
const vivid::Rect       CPlayerMark::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerMark::m_scale = vivid::Vector2(0.5f, 0.7f);
const vivid::Vector2    CPlayerMark::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

CPlayerMark::CPlayerMark(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CPlayerMark::~CPlayerMark()
{
}

void CPlayerMark::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CPlayerMark::Update(void)
{

}

void CPlayerMark::Draw(void)
{
	vivid::DrawTexture(m_file_names[0], m_Position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CPlayerMark::Finalize(void)
{
}
