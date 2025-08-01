#include "finish_game_text.h"

const int				CFinishGameText::m_height = 354;
const int				CFinishGameText::m_width = 800;
const vivid::Rect		CFinishGameText::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2	CFinishGameText::m_default_scale = vivid::Vector2(0.0f, 0.0f);
const vivid::Vector2	CFinishGameText::m_max_scale = vivid::Vector2(1.5f,1.5f);
const vivid::Vector2	CFinishGameText::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);
const vivid::Vector2	CFinishGameText::m_default_position = vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, (vivid::WINDOW_HEIGHT - m_height) / 2.0f);
const unsigned int      CFinishGameText::m_default_color = 0xffffffff;

const std::string		CFinishGameText::m_file_name = "data\\Textures\\finish_text.png";

const float				CFinishGameText::m_zoomin_time = 0.5f;
const float				CFinishGameText::m_stop_time = 0.2f;
const float				CFinishGameText::m_fadeout_time = 0.3f;


CFinishGameText::CFinishGameText(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Scale(m_default_scale)
	, m_MoveState(START_TEXT_MOVE::ZOOM_IN)
	, m_Timer()
	, m_Color(m_default_color)
{

}

CFinishGameText::~CFinishGameText(void)
{

}

void CFinishGameText::Initialize(void)
{
	CUI::Initialize();

	m_MoveState = START_TEXT_MOVE::ZOOM_IN;
	m_Timer.SetUp(m_zoomin_time);
	m_Color = 0xffffffff;
	
	m_Position = m_default_position;
}

void CFinishGameText::Update(void)
{
	CUI::Update();

	m_Timer.Update();

	switch (m_MoveState)
	{
	case CFinishGameText::START_TEXT_MOVE::ZOOM_IN:
		if (m_Timer.Finished())
		{
			m_Scale = m_max_scale;
			m_MoveState = START_TEXT_MOVE::STOP;
			m_Timer.SetUp(m_stop_time);
		}
		else
		{
			float TimeRate = m_Timer.GetTimer() / m_zoomin_time;
			m_Scale = vivid::Vector2(m_default_scale.x + (m_max_scale.x - m_default_scale.x) * TimeRate, m_default_scale.y + (m_max_scale.y - m_default_scale.y) * TimeRate);
		}
		break;
	
	case CFinishGameText::START_TEXT_MOVE::STOP:
		if (m_Timer.Finished())
		{
			m_MoveState = START_TEXT_MOVE::FADE_OUT;
			m_Timer.SetUp(m_fadeout_time);
		}
		break;

	case CFinishGameText::START_TEXT_MOVE::FADE_OUT:
		if (m_Timer.Finished())
		{
			m_ActiveFlag = false;
		}
		else
		{
			unsigned int RGB = m_default_color & 0x00ffffff;
			unsigned int Alpha = m_default_color & 0xff000000;
			Alpha = Alpha >> 24;
			Alpha = Alpha * ((m_fadeout_time - m_Timer.GetTimer()) / m_fadeout_time);
			Alpha = Alpha << 24;

			m_Color = Alpha | RGB;
		}
		break;
	}
}

void CFinishGameText::Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_rect, m_anchor, m_Scale);
}

void CFinishGameText::Finalize(void)
{
	CUI::Finalize();

}
