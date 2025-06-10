#include "entry_x_button.h"
#include "../../../unit_manager/unit_manager.h"

const int    CEntryXButton::m_width = 800;
const int    CEntryXButton::m_height = 130;
const vivid::Vector2    CEntryXButton::m_position = vivid::Vector2(0, 0);
const int               CEntryXButton::m_fade_speed = 4;
const float             CEntryXButton::m_wait_time = 0.8f;

/*
 *  コンストラクタ
 */
CEntryXButton::
CEntryXButton(UI_ID id)
    : CUI(m_width, m_height, id)
    , m_Color()
    , m_FadeSpeed(m_fade_speed)
    , m_UINum(0)
    , m_WaitTimer(m_wait_time)
    , m_State(STATE::WAIT)
{
}

/*
 *  デストラクタ
 */
CEntryXButton::
~CEntryXButton(void)
{
}

/*
 *  初期化
 */
void
CEntryXButton::
Initialize(void)
{
    CUI::Initialize(m_position);
    m_Color[0] = 0xffffffff;
    m_Color[1] = 0x00ffffff;
    
}

/*
 *  更新
 */
void
CEntryXButton::
Update(void)
{
    CUI::Update();
    unsigned int alpha = vivid::alpha::GetAlpha(m_Color[m_UINum]);
    switch (m_State)
    {
    case CEntryXButton::STATE::WAIT:
        m_WaitTimer.Update();
        if (m_WaitTimer.Finished())
        {
            m_State = STATE::FADE_OUT;

            m_WaitTimer.Reset();
        }

        break;

    //２つのUIのアルファ値を切り替える
    case CEntryXButton::STATE::FADE_IN:
        m_Color[m_UINum] = vivid::alpha::AdjustAlpha(m_Color[m_UINum], m_fade_speed);
        if (alpha == 255u)
            m_State = STATE::WAIT;

        break;
    case CEntryXButton::STATE::FADE_OUT:
        m_Color[m_UINum] = vivid::alpha::AdjustAlpha(m_Color[m_UINum], -m_fade_speed);
        if (alpha == 0u)
        {
            m_State = STATE::FADE_IN;
            m_UINum ^= 1;
        }

        break;
    }

}

/*
 *  描画
 */
void
CEntryXButton::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\entrance_and_exit_ui.png", m_Position, m_Color[0]);
    vivid::DrawTexture("data\\Textures\\entry_start_ui.png", m_Position, m_Color[1]);


}

/*
 *  解放
 */
void
CEntryXButton::
Finalize(void)
{
}
