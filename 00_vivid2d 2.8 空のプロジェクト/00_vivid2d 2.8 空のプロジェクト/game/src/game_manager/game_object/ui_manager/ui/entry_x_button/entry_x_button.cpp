#include "entry_x_button.h"
#include "../../../unit_manager/unit_manager.h"

const int    CEntryXButton::m_width = 800;
const int    CEntryXButton::m_height = 130;
const vivid::Vector2    CEntryXButton::m_position = vivid::Vector2(0, 0);
const int    CEntryXButton::m_fade_speed = 2;

/*
 *  コンストラクタ
 */
CEntryXButton::
CEntryXButton(UI_ID id)
    : CUI(m_width, m_height, id)
    , m_Color()
    , m_FadeSpeed(m_fade_speed)
    , m_UINum(0)
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
    if (alpha == 255u || alpha == 0u)
        m_FadeSpeed = -m_FadeSpeed;
    if (alpha == 0u)
        m_UINum ^= 1;
    m_Color[m_UINum] = vivid::alpha::AdjustAlpha(m_Color[m_UINum], m_FadeSpeed);

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
