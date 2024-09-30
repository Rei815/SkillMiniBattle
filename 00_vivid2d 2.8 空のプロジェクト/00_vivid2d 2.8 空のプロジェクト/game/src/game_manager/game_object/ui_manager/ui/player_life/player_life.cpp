#include "player_life.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CPlayerLife::m_position = vivid::Vector2(0, vivid::GetWindowHeight() - m_height * 0.25f);
const int               CPlayerLife::m_height = 256;
const int               CPlayerLife::m_width = 256;
const vivid::Rect       CPlayerLife::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerLife::m_scale = vivid::Vector2(0.1f, 0.1f);
const vivid::Vector2    CPlayerLife::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  コンストラクタ
 */
CPlayerLife::
CPlayerLife(void)
    : CUI(m_width, m_height)
{
}

/*
 *  デストラクタ
 */
CPlayerLife::
~CPlayerLife(void)
{
}

/*
 *  初期化
 */
void
CPlayerLife::
Initialize(void)
{
}

/*
 *  更新
 */
void
CPlayerLife::
Update(void)
{

}

/*
 *  描画
 */
void
CPlayerLife::
Draw(void)
{
    IUnit* player = CUnitManager::GetInstance().GetPlayer();

    if (!player)
        return;
    vivid::Vector2 pos = m_position;
    for (int i = 0; i < player->GetMaxLife(); i++)
    {
        vivid::Vector2 pos = m_position;

        pos.x += i * m_width * m_scale.x;
        vivid::DrawTexture("data\\Textures\\player_life_outLine.png", pos, 0xffffffff, m_rect, m_anchor, m_scale);

    }
    for (int i = 0; i < player->GetLife() -1.0f; i++)
    {

        vivid::DrawTexture("data\\Textures\\player_life.png", pos, 0xffffffff, m_rect, m_anchor, m_scale);
        pos.x += m_width * m_scale.x;


    }
    float fractional_part = std::fmod(player->GetLife(), 1.0f);
    vivid::Rect rect = m_rect;
    if (fractional_part != 0)
    {
        rect.right *= fractional_part;
    }

    vivid::DrawTexture("data\\Textures\\player_life.png", pos, 0xffffffff, rect, m_anchor, m_scale);

}

/*
 *  解放
 */
void
CPlayerLife::
Finalize(void)
{
}
