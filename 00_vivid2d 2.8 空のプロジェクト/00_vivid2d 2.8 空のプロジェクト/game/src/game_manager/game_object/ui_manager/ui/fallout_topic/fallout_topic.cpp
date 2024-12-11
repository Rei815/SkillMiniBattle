#include "fallout_topic.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"

const int               CFallOutTopic::m_height = 184;
const int               CFallOutTopic::m_width = 200;
const float             CFallOutTopic::m_wait_time = 2.0f;
const float             CFallOutTopic::m_change_time = 0.1f;
const vivid::Rect       CFallOutTopic::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFallOutTopic::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFallOutTopic::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const vivid::Vector2    CFallOutTopic::m_adjustPosition = vivid::Vector2(77.0f, 27.0f);
const float				CFallOutTopic::m_speed = 300;

/*
 *  コンストラクタ
 */
CFallOutTopic::
CFallOutTopic(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_CurrentID(MARK_ID::NONE)
	, m_PreviousID(MARK_ID::NONE
	)
	, m_State(STATE::WAIT)
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

	m_Position = position;
	CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG, m_Position);
	m_Rect = m_rect;
	m_FileName = "data\\Textures\\fall_circle_ui.png";
	m_Timer.SetUp(m_wait_time);
}

/*
 *  更新
 */
void
CFallOutTopic::
Update(void)
{
	m_Timer.Update();
	switch (m_State)
	{
	case CFallOutTopic::STATE::WAIT:
		if (m_Timer.Finished())
		{
			m_State = STATE::CHANGE;
			m_Timer.SetUp(m_change_time);
		}
		break;
	case CFallOutTopic::STATE::CHANGE:
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
		//if (m_CurrentID == m_PreviousID) return;
		//m_SelectTimer.Update();
		//if (m_SelectTimer.Finished())
		//{
		//	m_State = STATE::SELECT;
		//}
		break;
	case CFallOutTopic::STATE::SELECT:

		//初期値に戻す
		m_Rect = m_rect;

		//決定されているマークの位置にする
		m_Rect.top = m_rect.top + (5 - static_cast<int>(m_CurrentID)) * m_height;
		m_Rect.bottom = m_rect.bottom + (5 - static_cast<int>(m_CurrentID)) * m_height;

			
		m_State = STATE::WAIT;
		m_Timer.SetUp(m_wait_time);
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
    vivid::DrawTexture(m_FileName, m_Position + m_adjustPosition, 0xffffffff, m_Rect, m_anchor, m_scale, 0.0f, vivid::ALPHABLEND::NOBELEND, vivid::ADDRESS_MODE::MIRROR);
}

/*
 *  解放
 */
void
CFallOutTopic::
Finalize(void)
{
}

void CFallOutTopic::SetMarkID(MARK_ID markID)
{
	m_PreviousID = m_CurrentID;
	m_CurrentID = markID;
}

void CFallOutTopic::SetTimer(float time)
{
	m_SelectTimer.SetUp(time);
	m_State = STATE::SELECT;
}

CFallOutTopic::STATE CFallOutTopic::GetState()
{
	return m_State;
}
