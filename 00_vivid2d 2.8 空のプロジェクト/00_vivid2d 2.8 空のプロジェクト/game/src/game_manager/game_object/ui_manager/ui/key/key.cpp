#include "key.h"
const std::string		CKey::m_file_name = "data\\Textures\\key.png";
const int               CKey::m_width = 100;
const int               CKey::m_height = 50;
const vivid::Rect       CKey::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CKey::m_scale = vivid::Vector2(0.8f, 0.9f);
const vivid::Vector2    CKey::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CKey::CKey(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CKey::~CKey(void)
{
}

void CKey::Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
	m_Scale = m_scale;
}

void CKey::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);

}

void CKey::Finalize(void)
{
}
