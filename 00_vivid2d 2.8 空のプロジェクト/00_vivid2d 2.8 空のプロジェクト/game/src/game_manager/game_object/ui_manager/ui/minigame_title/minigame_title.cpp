#include "minigame_title.h"
#include "../../../data_manager/data_manager.h"

const vivid::Vector2    CMiniGameTitle::m_position = vivid::Vector2(80, 10);
const int    CMiniGameTitle::m_width = 500;
const int    CMiniGameTitle::m_height = 150;

const std::string CMiniGameTitle::m_file_name[] =
{
		"data\\Textures\\minigame_title_daruma_fall_down.png",
		"data\\Textures\\minigame_title_fallout.png",
		"data\\Textures\\minigame_title_dodge_ball.png",
		"data\\Textures\\minigame_title_dodge_ball.png",
		"data\\Textures\\minigame_title_dodge_ball.png",
		"data\\Textures\\minigame_title_dodge_ball.png",
		"data\\Textures\\minigame_title_dodge_ball.png",
};

/*
 *  コンストラクタ
 */
CMiniGameTitle::
CMiniGameTitle(UI_ID id)
    : CUI(m_width, m_height, id)
{
}

/*
 *  デストラクタ
 */
CMiniGameTitle::
~CMiniGameTitle(void)
{
}

/*
 *  初期化
 */
void
CMiniGameTitle::
Initialize(void)
{
	CUI::Initialize(m_position);
	m_FileName = m_file_name[(int)CDataManager::GetInstance().GetSelectGameID()];
}

/*
 *  更新
 */
void
CMiniGameTitle::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CMiniGameTitle::
Draw(void)
{
    vivid::DrawTexture(m_FileName, m_Position, 0xffffffff);


}

/*
 *  解放
 */
void
CMiniGameTitle::
Finalize(void)
{
}
