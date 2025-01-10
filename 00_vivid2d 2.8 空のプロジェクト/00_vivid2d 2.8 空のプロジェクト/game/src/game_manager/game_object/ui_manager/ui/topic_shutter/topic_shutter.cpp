#include "topic_shutter.h"
const std::string		CTopicShutter::m_file_name = "data\\Textures\\topic_shutter.png";
const int               CTopicShutter::m_width = 255;
const int               CTopicShutter::m_height = 160;
const int               CTopicShutter::m_speed = 2;
const vivid::Rect       CTopicShutter::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CTopicShutter::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CTopicShutter::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const float				CTopicShutter::m_duration_time = 5.0f;
CTopicShutter::CTopicShutter(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Rect(m_rect)
{
}

CTopicShutter::~CTopicShutter(void)
{
}

void CTopicShutter::Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
	m_Timer.SetUp(m_duration_time);
	m_Rect.top = m_Rect.bottom;
}

void CTopicShutter::Update(void)
{
	m_Timer.Update();
	if (m_Timer.Finished())
	{
		m_Rect.top += m_speed;
		if (m_Rect.top > m_Rect.bottom)
		{
			m_Rect.top = m_Rect.bottom;
		}

	}
	else
	{
		m_Rect.top -= m_speed;
		if (m_Rect.top < 0)
		{
			m_Rect.top = 0;
		}

	}
}

void CTopicShutter::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_Rect, m_anchor, m_scale);

}

void CTopicShutter::Finalize(void)
{
}
