#include "text_overview.h"
const std::string		CTextOverview::m_file_name = "data\\Textures\\text_overview.png";
const vivid::Vector2    CTextOverview::m_position = vivid::Vector2(60, 485);
const int               CTextOverview::m_width = 600;
const int               CTextOverview::m_height = 150;
const vivid::Rect       CTextOverview::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CTextOverview::m_scale = vivid::Vector2(0.3f, 0.3f);
const vivid::Vector2    CTextOverview::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CTextOverview::CTextOverview(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CTextOverview::~CTextOverview(void)
{
}

void CTextOverview::Initialize()
{
	CUI::Initialize(m_position);
	m_Scale = m_scale;
}

void CTextOverview::Update(void)
{
	CUI::Update();
}

void CTextOverview::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

void CTextOverview::Finalize(void)
{
}
