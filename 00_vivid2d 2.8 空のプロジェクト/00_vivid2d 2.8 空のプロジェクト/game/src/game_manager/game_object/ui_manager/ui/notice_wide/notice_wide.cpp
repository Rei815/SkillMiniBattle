#include "notice_wide.h"
const std::string		CNoticeWide::m_file_name = "data\\Textures\\notice_wide.png";
const int               CNoticeWide::m_width = 833;
const int               CNoticeWide::m_height = 338;
const vivid::Rect       CNoticeWide::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CNoticeWide::m_scale = vivid::Vector2(1.45f, 0.45f);
const vivid::Vector2    CNoticeWide::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CNoticeWide::CNoticeWide(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CNoticeWide::~CNoticeWide(void)
{
}

void CNoticeWide::Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
}

void CNoticeWide::Update(void)
{
	CUI::Update();
}

void CNoticeWide::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

void CNoticeWide::Finalize(void)
{
}
