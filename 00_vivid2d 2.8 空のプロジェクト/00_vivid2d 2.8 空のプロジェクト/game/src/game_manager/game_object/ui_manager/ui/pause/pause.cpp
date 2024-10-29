#include "pause.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CPause::m_position = vivid::Vector2(0, 0);
const int    CPause::m_width = 1280;
const int    CPause::m_height = 780;

/*
 *  コンストラクタ
 */
CPause::
CPause(UI_ID id)
    : CUI(m_width, m_height, id)
{
}

/*
 *  デストラクタ
 */
CPause::
~CPause(void)
{
}

/*
 *  初期化
 */
void
CPause::
Initialize(void)
{
    m_UI_ID = UI_ID::PAUSE;
    m_Attributes.push_back(UI_ATTRIBUTE::BUTTON);
    m_Position = m_position;
}

/*
 *  更新
 */
void
CPause::
Update(void)
{

}

/*
 *  描画
 */
void
CPause::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\pause_bg.png", m_position, 0x80ffffff);

    vivid::DrawText(30, "一時停止中", vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f - (vivid::GetTextWidth(30, "一時停止中") / 2), vivid::WINDOW_HEIGHT / 2.0f));

}

/*
 *  解放
 */
void
CPause::
Finalize(void)
{
}
