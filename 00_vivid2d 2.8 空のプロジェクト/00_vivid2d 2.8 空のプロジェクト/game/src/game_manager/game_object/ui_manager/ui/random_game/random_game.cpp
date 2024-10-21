#include "random_game.h"

const TCHAR*            CRandomGame::m_file_name = "data\\Textures\\test.png";
const int               CRandomGame::m_height = 960;
const int               CRandomGame::m_width = 540;
const vivid::Vector2    CRandomGame::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2.0f, vivid::GetWindowHeight() / 2.0f);
const vivid::Rect       CRandomGame::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CRandomGame::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CRandomGame::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  コンストラクタ
 */
CRandomGame::
CRandomGame(void)
    : CUI(m_width, m_height)
{
}

/*
 *  デストラクタ
 */
CRandomGame::
~CRandomGame(void)
{
}

/*
 *  初期化
 */
void
CRandomGame::
Initialize(void)
{
    // 画像の読み込み
    m_Handle = LoadGraph(m_file_name);
}

/*
 *  更新
 */
void
CRandomGame::
Update(void)
{

}

/*
 *  描画
 */
void
CRandomGame::
Draw(void)
{
    DrawGraph(m_position.x, m_position.y, m_Handle, true);
}

/*
 *  解放
 */
void
CRandomGame::
Finalize(void)
{
    // 読み込んだ画像のグラフィックハンドルを削除
    DeleteGraph(m_Handle);
}
