#include "fallout_topic_bg.h"

const std::string		CFalloutTopicBG::m_file_name = "data\\Textures\\fallout_topic_bg.png";
const int               CFalloutTopicBG::m_width = 300;
const int               CFalloutTopicBG::m_height = 200;
const vivid::Rect       CFalloutTopicBG::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFalloutTopicBG::m_scale = vivid::Vector2(0.5f, 0.7f);
const vivid::Vector2    CFalloutTopicBG::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

CFalloutTopicBG::CFalloutTopicBG(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CFalloutTopicBG::~CFalloutTopicBG()
{
}

void CFalloutTopicBG::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CFalloutTopicBG::Update(void)
{
}

void CFalloutTopicBG::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CFalloutTopicBG::Finalize(void)
{
}
