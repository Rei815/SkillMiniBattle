#include "key_bg.h"
const std::string		CKeyBG::m_file_name = "data\\Textures\\key_bg.png";
const int               CKeyBG::m_width = 100;
const int               CKeyBG::m_height = 50;
const vivid::Rect       CKeyBG::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CKeyBG::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CKeyBG::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CKeyBG::CKeyBG(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CKeyBG::~CKeyBG(void)
{
}

void CKeyBG::Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
}

void CKeyBG::Update(void)
{
}

void CKeyBG::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CKeyBG::Finalize(void)
{
}
