#include "fallout_topic.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"

const std::string		CFallOutTopic::m_file_name = "data\\Textures\\fall_topic_ui.png";
const int               CFallOutTopic::m_height = 100;
const int               CFallOutTopic::m_width = 100;
const float             CFallOutTopic::m_wait_time = 2.0f;
const float             CFallOutTopic::m_change_time = 0.1f;
const vivid::Rect       CFallOutTopic::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFallOutTopic::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CFallOutTopic::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const vivid::Vector2    CFallOutTopic::m_adjust_position = vivid::Vector2(60.0f, 40.0f);
const float				CFallOutTopic::m_speed = 300;
const float				CFallOutTopic::m_end_y = 0.0f;
const float				CFallOutTopic::m_end_time = 2.0f;

/*
 *  コンストラクタ
 */
CFallOutTopic::
CFallOutTopic(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_CurrentID(MARK_ID::NONE)				   
	, m_State(STATE::APPEAR)
	, m_EaseTimer(0.0f)
	, m_FinishValue(0.0f)
	, m_BackGround(nullptr)
{
}

/*
 *  デストラクタ
 */
CFallOutTopic::
~CFallOutTopic(void)
{
}

/*
 *  初期化
 */
void
CFallOutTopic::
Initialize(const vivid::Vector2& position)
{
	CUI::Initialize(position);
	m_StartValue = m_Position.y;
	m_EaseTimer = 0.0f;
	m_FinishValue = m_end_y;
	m_Position = position;
	m_BackGround = CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG, m_Position);
	m_BackGround->SetParent(shared_from_this());
	m_Rect = m_rect;
	m_Timer.SetUp(m_change_time);
}

/*
 *  更新
 */
void
CFallOutTopic::
Update(void)
{
	m_Timer.Update();
	if (m_BackGround)
	{
		m_BackGround->SetPosition(m_Position);
	}
	switch (m_State)
	{
	case CFallOutTopic::STATE::APPEAR:
		if (m_Position.y != m_end_y)
		{
			float current_y = Easing::OutQuart(m_EaseTimer, m_end_time, m_StartValue, -m_FinishValue);

			m_Position.y = current_y;

			m_EaseTimer += vivid::GetDeltaTime();
		}
		else
		{
			m_Position.y = m_end_y;
			m_State = CFallOutTopic::STATE::SWITCHING;
		}
		break;
	case CFallOutTopic::STATE::WAIT:

		break;
	case CFallOutTopic::STATE::SWITCHING:
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Rect.top += m_height;
			m_Rect.bottom += m_height;
		}
		if (m_Rect.top >= m_height * 6)
		{
			m_Rect = m_rect;
		}
		break;
	case CFallOutTopic::STATE::PICK_UP:

		//初期値に戻す
		m_Rect = m_rect;

		//決定されているマークの位置にする
		m_Rect.top = m_rect.top + (5 - static_cast<int>(m_CurrentID)) * m_height;
		m_Rect.bottom = m_rect.bottom + (5 - static_cast<int>(m_CurrentID)) * m_height;

			
		m_State = STATE::WAIT;
		break;
	case CFallOutTopic::STATE::FINISH:
		m_BackGround = nullptr;
		break;
	}
}

/*
 *  描画
 */
void
CFallOutTopic::
Draw(void)
{
    vivid::DrawTexture(m_file_name, m_Position + m_adjust_position, 0xffffffff, m_Rect, m_anchor, m_scale, 0.0f, vivid::ALPHABLEND::NOBELEND, vivid::ADDRESS_MODE::MIRROR);
}

/*
 *  解放
 */
void
CFallOutTopic::
Finalize(void)
{
	m_BackGround = nullptr;
}

void CFallOutTopic::SetMarkID(MARK_ID markID)
{
	m_CurrentID = markID;
}

void CFallOutTopic::SetTimer(float time)
{
	m_SelectTimer.SetUp(time);
	m_State = STATE::PICK_UP;
}

CFallOutTopic::STATE CFallOutTopic::GetState()
{
	return m_State;
}

void CFallOutTopic::SetState(CFallOutTopic::STATE state)
{
	m_State = state;
}