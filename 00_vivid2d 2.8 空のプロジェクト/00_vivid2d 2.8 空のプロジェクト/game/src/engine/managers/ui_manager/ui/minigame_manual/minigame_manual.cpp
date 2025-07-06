#include "minigame_manual.h"
#include "../../../data_manager/data_manager.h"
#include "../../ui_manager.h"

const vivid::Vector2    CMiniGameManual::m_position = vivid::Vector2(750, 120);
const vivid::Vector2    CMiniGameManual::m_bg_position = vivid::Vector2(700, 30);
const vivid::Vector2    CMiniGameManual::m_bg_scale = vivid::Vector2(0.9f, 0.9f);

const std::string CMiniGameManual::m_file_name[] =
{
		"data\\Textures\\manual_daruma_fall_down.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
		"data\\Textures\\manual_fall_out&dodge_ball.png",
};
/*
 *  コンストラクタ
 */
CMiniGameManual::
CMiniGameManual(UI_ID id)
	: CUI(id, -1)
{
}

/*
 *  デストラクタ
 */
CMiniGameManual::
~CMiniGameManual(void)
{
}

/*
 *  初期化
 */
void
CMiniGameManual::
Initialize(void)
{
	CUI::Initialize(m_position);
	std::shared_ptr<CUI> bg = CUIManager::GetInstance().Create(UI_ID::NOTICE, m_bg_position);
	bg->SetScale(m_bg_scale);

	SetOrderInLayer(1);

	m_FileName = m_file_name[(int)CDataManager::GetInstance().GetSelectGameID()];
}

/*
 *  更新
 */
void
CMiniGameManual::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CMiniGameManual::
Draw(void)
{
	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff);
}

/*
 *  解放
 */
void
CMiniGameManual::
Finalize(void)
{
}
