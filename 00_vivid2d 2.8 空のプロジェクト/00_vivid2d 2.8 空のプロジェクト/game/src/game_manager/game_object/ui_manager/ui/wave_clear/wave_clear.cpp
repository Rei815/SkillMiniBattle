#include "wave_clear.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../ui_manager.h"

const int               CWaveClear::m_height = 267;
const int               CWaveClear::m_width = 577;
const vivid::Vector2    CWaveClear::m_position = vivid::Vector2((float)vivid::WINDOW_WIDTH, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_height / 2.0f);
const vivid::Rect       CWaveClear::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CWaveClear::m_scale = vivid::Vector2(0.7f, 0.7f);
const vivid::Vector2    CWaveClear::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const float             CWaveClear::m_end_time = 1.25f;
const float             CWaveClear::m_relay_x = (float)vivid::WINDOW_WIDTH / 2.0f - (float)m_width / 2.0f;
const float             CWaveClear::m_end_x = 0 - (float)m_width;

/*
 *  コンストラクタ
 */
CWaveClear::
CWaveClear(void)
    : CUI(m_width, m_height)
    , m_Easing(CEasing())
    , m_StartTime(0.0f)
    , m_FinishValue(0.0f)
{
}

/*
 *  デストラクタ
 */
CWaveClear::
~CWaveClear(void)
{
}

/*
 *  初期化
 */
void
CWaveClear::
Initialize(void)
{
    m_Position = m_position;
    m_StartValue = m_position.x;
    m_StartTime = 0.0f;
    m_FinishValue = m_relay_x;
    m_Easing.easingState = CEasing::EASING_STATE::EASE_OUT;
    m_Attributes.push_back(UI_ATTRIBUTE::STOP_GENERATION);
    m_UI_ID = UI_ID::WAVE_CLEAR;
}

/*
 *  更新
 */
void
CWaveClear::
Update(void)
{
    switch (m_Easing.easingState)
    {
    case CEasing::EASING_STATE::EASE_OUT:
        EaseOut();
        break;
    case CEasing::EASING_STATE::EASE_IN:
        EaseIn();
        break;
    }
}

/*
 *  描画
 */
void
CWaveClear::
Draw(void)
{

    vivid::DrawTexture("data\\Textures\\wave_clear.png", m_Position, 0xffffffff, m_rect, m_anchor, m_scale);
}

/*
 *  解放
 */
void
CWaveClear::
Finalize(void)
{
}

vivid::Vector2 CWaveClear::GetCenterPosition(void)
{
    return vivid::Vector2(m_Position.x + m_width / 2.0, m_Position.y + m_height / 2.0f);
}

void CWaveClear::EaseOut(void)
{
    if (m_Position.x != m_relay_x)
    {
        float current_x = m_Easing.OutQuart(m_StartTime, m_end_time, m_StartValue, m_FinishValue);

        m_Position.x = current_x;

        m_StartTime += vivid::GetDeltaTime();
    }
    else
    {
        m_Position.x = m_relay_x;
        m_StartTime = 0.0f;
        m_StartValue = m_relay_x;
        m_FinishValue = m_end_x;
        m_Easing.easingState = CEasing::EASING_STATE::EASE_IN;
    }

}

void CWaveClear::EaseIn(void)
{
    if (m_Position.x >= m_end_x)
    {
        float current_x = m_Easing.InQuart(m_StartTime, m_end_time, m_StartValue, m_FinishValue);

        m_Position.x = current_x;

        m_StartTime += vivid::GetDeltaTime();
    }
    else
    {
        CUIManager::GetInstance().SetWaveClearUIActive(false);
        m_ActiveFlag = false;
    }
}

void CWaveClear::Reset(void)
{
    Initialize();
}
