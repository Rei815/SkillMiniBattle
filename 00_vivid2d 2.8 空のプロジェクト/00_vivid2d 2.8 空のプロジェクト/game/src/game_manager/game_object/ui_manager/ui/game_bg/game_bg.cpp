#include "game_bg.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CGameBG::m_position = vivid::Vector2(0, 0);
const int    CGameBG::m_width = 1280;
const int    CGameBG::m_height = 780;

/*
 *  コンストラクタ
 */
CGameBG::
CGameBG(UI_ID id)
    : CUI(m_width, m_height, id)
{
}

/*
 *  デストラクタ
 */
CGameBG::
~CGameBG(void)
{
}

/*
 *  初期化
 */
void
CGameBG::
Initialize(void)
{
}

/*
 *  更新
 */
void
CGameBG::
Update(void)
{

}

/*
 *  描画
 */
void
CGameBG::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\sea.jpg", m_position, 0xffffffff);


}

/*
 *  解放
 */
void
CGameBG::
Finalize(void)
{
}
