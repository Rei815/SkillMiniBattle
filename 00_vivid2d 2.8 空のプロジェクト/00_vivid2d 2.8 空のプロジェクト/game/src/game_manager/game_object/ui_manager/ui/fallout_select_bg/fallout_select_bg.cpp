#include "fallout_select_bg.h"

const std::string		CFalloutSellectBG::m_file_name = "data\\Textures\\fallout_select_bg.png";
const int               CFalloutSellectBG::m_width = 410;
const int               CFalloutSellectBG::m_height = 254;
const vivid::Rect       CFalloutSellectBG::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFalloutSellectBG::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFalloutSellectBG::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

CFalloutSellectBG::CFalloutSellectBG(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CFalloutSellectBG::~CFalloutSellectBG()
{
}

void CFalloutSellectBG::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CFalloutSellectBG::Update(void)
{
}

void CFalloutSellectBG::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CFalloutSellectBG::Finalize(void)
{
}
