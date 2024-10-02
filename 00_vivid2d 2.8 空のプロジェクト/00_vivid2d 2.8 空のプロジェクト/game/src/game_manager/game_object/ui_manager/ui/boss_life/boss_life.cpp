#include "boss_life.h"
#include "../../../unit_manager/unit_manager.h"

const int               CBossLife::m_height = 10;
const int               CBossLife::m_width = 1054;
const int               CBossLife::m_rect_speed = 6;
const vivid::Rect       CBossLife::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CBossLife::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CBossLife::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const vivid::Vector2    CBossLife::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2.0f - m_width / 2.0f, 50);

/*
 *  コンストラクタ
 */
CBossLife::
CBossLife(void)
    : CUI(m_width, m_height)
    , m_Rect(vivid::Rect())
{
}

/*
 *  デストラクタ
 */
CBossLife::
~CBossLife(void)
{
}

/*
 *  初期化
 */
void
CBossLife::
Initialize(void)
{
    m_Rect.bottom = m_rect.bottom;
}

/*
 *  更新
 */
void
CBossLife::
Update(void)
{


}

/*
 *  描画
 */
void
CBossLife::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\boss_life_gauge.png", m_position, 0xffffffff, m_Rect, m_anchor, m_scale);
}

/*
 *  解放
 */
void
CBossLife::
Finalize(void)
{
}
