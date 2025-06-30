#include "notice.h"
const std::string		CNotice::m_file_name = "data\\Textures\\notice.png";
const int               CNotice::m_width = 500;
const int               CNotice::m_height = 500;
const vivid::Rect       CNotice::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CNotice::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CNotice::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2.0f, (m_height * m_scale.y) / 2.0f);

CNotice::CNotice(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CNotice::~CNotice(void)
{
}

void CNotice::Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
	m_Scale = m_scale;
}

void CNotice::Update(void)
{
	CUI::Update();
}

void CNotice::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);

}

void CNotice::Finalize(void)
{
}
