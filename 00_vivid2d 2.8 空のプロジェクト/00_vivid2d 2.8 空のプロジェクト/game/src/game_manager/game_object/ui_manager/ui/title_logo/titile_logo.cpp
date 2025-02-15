#include "title_logo.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CTitleLogo::m_position = vivid::Vector2(0, 0);
const int    CTitleLogo::m_width = 1280;
const int    CTitleLogo::m_height = 780;

/*
 *  コンストラクタ
 */
CTitleLogo::CTitleLogo(UI_ID id)
    : CUI(m_width, m_height, id, -2)
{
}

/*
 *  デストラクタ
 */
CTitleLogo::~CTitleLogo(void)
{
}

/*
 *  初期化
 */
void
CTitleLogo::Initialize(void)
{
}

/*
 *  更新
 */
void
CTitleLogo::Update(void)
{

}

/*
 *  描画
 */
void
CTitleLogo::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title_logo.png", m_position, 0xffffffff);


}

/*
 *  解放
 */
void
CTitleLogo::Finalize(void)
{

}
