#include "wave_start.h"
#include "../../../unit_manager/unit_manager.h"

const int               CWaveStart::m_height = 132;
const int               CWaveStart::m_width = 506;
const vivid::Vector2    CWaveStart::m_position = vivid::Vector2((float)vivid::WINDOW_WIDTH, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_height / 2.0f);
const vivid::Rect       CWaveStart::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CWaveStart::m_scale = vivid::Vector2(0.7f, 0.7f);
const vivid::Vector2    CWaveStart::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const float             CWaveStart::m_end_time = 1.25f;
const float             CWaveStart::m_relay_x = (float)vivid::WINDOW_WIDTH / 2.0f - (float)m_width / 2.0f;
const float             CWaveStart::m_end_x = 0 - (float)m_width;

/*
 *  コンストラクタ
 */
CWaveStart::
CWaveStart(void)
    : CUI(m_width, m_height)
    , m_Easing(CEasing())
    , m_StartTime(0.0f)
    , m_FinishValue(0.0f)
    , m_WaveCounter()
{
}

/*
 *  デストラクタ
 */
CWaveStart::
~CWaveStart(void)
{
}

/*
 *  初期化
 */
void
CWaveStart::
Initialize(void)
{
    m_Position = m_position;
    m_StartValue = m_position.x;
    m_StartTime = 0.0f;
    m_FinishValue = m_relay_x;
    m_Easing.easingState = CEasing::EASING_STATE::EASE_OUT;
    m_Attributes.push_back(UI_ATTRIBUTE::STOP_GENERATION);
    m_WaveCounter.Initialize();
}

/*
 *  更新
 */
void
CWaveStart::
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
    m_WaveCounter.Update(GetCenterPosition());
}

/*
 *  描画
 */
void
CWaveStart::
Draw(void)
{

    vivid::DrawTexture("data\\Textures\\wave_start.png", m_Position, 0xffffffff, m_rect, m_anchor, m_scale);
    m_WaveCounter.Draw();
}

/*
 *  解放
 */
void
CWaveStart::
Finalize(void)
{
    m_WaveCounter.Finalize();
}

vivid::Vector2 CWaveStart::GetCenterPosition(void)
{
    return vivid::Vector2(m_Position.x + m_width / 2.0, m_Position.y +  m_height / 2.0f);
}

void CWaveStart::EaseOut(void)
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

void CWaveStart::EaseIn(void)
{
    if (m_Position.x >= m_end_x)
    {
        float current_x = m_Easing.InQuart(m_StartTime, m_end_time, m_StartValue, m_FinishValue);

        m_Position.x = current_x;

        m_StartTime += vivid::GetDeltaTime();
    }
    else
    {
        CUnitManager::GetInstance().SetGenerateFlag(true);
        m_ActiveFlag = false;

    }
}

void CWaveStart::Reset(void)
{
    Initialize();
}
