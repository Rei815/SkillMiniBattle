#include "fade.h"

const std::string CFade::m_file_name = "data\\Textures\\white.png";
const vivid::Vector2 CFade::m_position = vivid::Vector2(0, 0);
const int CFade::m_width = 1920;
const int CFade::m_height = 1360;
const int CFade::m_fade_speed = 5;
const float CFade::m_wait_time = 0.5f;
CFade::CFade(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Color()
	, m_FadeSpeed(m_fade_speed)
{
}

CFade::~CFade(void)
{
}

void CFade::Initialize(void)
{
	m_Color = 0x00ffffff;
	m_Timer.SetUp(m_wait_time);
}

void CFade::Update(void)
{
	unsigned int alpha = vivid::alpha::GetAlpha(m_Color);
	if (alpha == 255u)
	{
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Timer.SetActive(false);
			m_FadeSpeed *= -1;
		}
	}
	m_Color = vivid::alpha::AdjustAlpha(m_Color, m_FadeSpeed);
}

void CFade::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_position, m_Color);
}

void CFade::Finalize(void)
{
}
