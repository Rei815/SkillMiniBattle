#include "start_game_count.h"

const int				CStartGameCount::m_height = 200;
const int				CStartGameCount::m_width = 200;
const vivid::Rect		CStartGameCount::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2	CStartGameCount::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2	CStartGameCount::m_max_scale = vivid::Vector2(1.5f,1.5f);
const vivid::Vector2	CStartGameCount::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const std::string		CStartGameCount::m_file_name[] = 
{
	"data\\Textures\\number_1.png",
	"data\\Textures\\number_2.png",
	"data\\Textures\\number_3.png"
};

const float				CStartGameCount::m_movein_time = 0.3f;
const float				CStartGameCount::m_stop_time = 0.4f;
const float				CStartGameCount::m_moveout_time = 0.3f;

const vivid::Vector2	CStartGameCount::m_movein_position = vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, -m_height);
const float				CStartGameCount::m_stop_position_y = (vivid::WINDOW_HEIGHT - m_height) / 2.0f;
const float				CStartGameCount::m_moveout_position_y = vivid::WINDOW_HEIGHT + m_height;

CStartGameCount::CStartGameCount(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Scale(m_default_scale)
	, m_MoveState(START_COUNT_MOVE::MOVE_IN)
	, m_Timer()
	, m_CountDown(0)
{

}

CStartGameCount::~CStartGameCount(void)
{

}

void CStartGameCount::Initialize(void)
{
	CUI::Initialize();

	m_MoveState = START_COUNT_MOVE::MOVE_IN;
	m_Timer.SetUp(m_movein_time);
	m_CountDown = 3;
	
	m_Position = m_movein_position;
}

void CStartGameCount::Update(void)
{
	CUI::Update();

	m_Timer.Update();

	switch (m_MoveState)
	{
	case CStartGameCount::START_COUNT_MOVE::MOVE_IN:
		if (m_Timer.Finished())
		{
			m_Position = vivid::Vector2(m_movein_position.x, m_stop_position_y);
			m_MoveState = START_COUNT_MOVE::STOP;
			m_Timer.SetUp(m_stop_time);
		}
		else
		{
			m_Position = vivid::Vector2(m_movein_position.x, m_movein_position.y + (m_stop_position_y - m_movein_position.y) * m_Timer.GetTimer() / m_movein_time);
		}
		break;
	
	case CStartGameCount::START_COUNT_MOVE::STOP:
		if (m_Timer.Finished())
		{
			m_Scale = m_default_scale;
			m_MoveState = START_COUNT_MOVE::MOVE_OUT;
			m_Timer.SetUp(m_moveout_time);
		}
		else
		{
			float NowTime = m_Timer.GetTimer();
			float TimeRate = 0.0f;
			if (NowTime < (m_stop_time / 2.0f))
			{
				TimeRate = NowTime / (m_stop_time / 2.0f);
			}
			else
			{
				TimeRate = (m_stop_time - NowTime) / (m_stop_time / 2.0f);
			}
			m_Scale = vivid::Vector2(m_default_scale.x + (m_max_scale.x - m_default_scale.x) * TimeRate, m_default_scale.y + (m_max_scale.y - m_default_scale.y) * TimeRate);
		}
		break;

	case CStartGameCount::START_COUNT_MOVE::MOVE_OUT:
		if (m_Timer.Finished())
		{
			m_Position = vivid::Vector2(m_movein_position.x, m_moveout_position_y);
			if (m_CountDown <= 0)
			{
				m_ActiveFlag = false;
			}
			else
			{
				m_CountDown--;
				m_MoveState = START_COUNT_MOVE::MOVE_IN;
				m_Timer.SetUp(m_movein_time);
			}
		}
		else
		{
			m_Position = vivid::Vector2(m_movein_position.x, m_moveout_position_y - (m_moveout_position_y - m_stop_position_y) * (m_moveout_time - m_Timer.GetTimer()) / m_moveout_time);
		}
		break;
	}
}

void CStartGameCount::Draw(void)
{
	CUI::Draw();

	if(0 < m_CountDown && m_CountDown <= 3)
		vivid::DrawTexture(m_file_name[m_CountDown - 1], m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

void CStartGameCount::Finalize(void)
{
	CUI::Finalize();

}
