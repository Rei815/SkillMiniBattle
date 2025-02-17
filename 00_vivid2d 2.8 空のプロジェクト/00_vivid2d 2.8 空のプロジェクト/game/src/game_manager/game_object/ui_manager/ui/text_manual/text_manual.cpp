#include "text_manual.h"
const std::string		CTextManual::m_file_name = "data\\Textures\\text_manual.png";
const vivid::Vector2    CTextManual::m_position = vivid::Vector2(750, 60);
const int               CTextManual::m_width = 300;
const int               CTextManual::m_height = 110;
const vivid::Rect       CTextManual::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CTextManual::m_scale = vivid::Vector2(0.3f, 0.3f);
const vivid::Vector2    CTextManual::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CTextManual::CTextManual(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CTextManual::~CTextManual(void)
{
}

void CTextManual::Initialize()
{
	CUI::Initialize(m_position);
	m_Scale = m_scale;
}

void CTextManual::Update(void)
{
	CUI::Update();
}

void CTextManual::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);

}

void CTextManual::Finalize(void)
{
}
