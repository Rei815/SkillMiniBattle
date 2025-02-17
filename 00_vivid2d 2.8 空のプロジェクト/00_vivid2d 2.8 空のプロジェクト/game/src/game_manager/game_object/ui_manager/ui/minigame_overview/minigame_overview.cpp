#include "minigame_overview.h"
#include "../../../data_manager/data_manager.h"

const vivid::Vector2    CMiniGameOverView::m_position = vivid::Vector2(120, 540);
const vivid::Vector2    CMiniGameOverView::m_bg_position = vivid::Vector2(300, 450);
const vivid::Vector2    CMiniGameOverView::m_bg_scale = vivid::Vector2(1.45f, 0.45f);

const int    CMiniGameOverView::m_width = 500;
const int    CMiniGameOverView::m_height = 150;

const std::string CMiniGameOverView::m_file_name[] =
{
		"data\\Textures\\overview_daruma_fall_down.png",
		"data\\Textures\\overview_fall_out.png",
		"data\\Textures\\overview_dodge_ball.png",
		"data\\Textures\\overview_dodge_ball.png",
		"data\\Textures\\overview_dodge_ball.png",
		"data\\Textures\\overview_dodge_ball.png",
		"data\\Textures\\overview_dodge_ball.png",
};
/*
 *  コンストラクタ
 */
CMiniGameOverView::
CMiniGameOverView(UI_ID id)
	: CUI(id)
{
}

/*
 *  デストラクタ
 */
CMiniGameOverView::
~CMiniGameOverView(void)
{
}

/*
 *  初期化
 */
void
CMiniGameOverView::
Initialize(void)
{
	CUI::Initialize(m_position);
	CUI* bg = CUIManager::GetInstance().Create(UI_ID::NOTICE_WIDE, m_bg_position);
	bg->SetScale(m_bg_scale);
	CUIManager::GetInstance().Create(UI_ID::TEXT_OVERVIEW);
	SetOrderInLayer(1);
	m_FileName = m_file_name[(int)CDataManager::GetInstance().GetSelectGameID()];
}

/*
 *  更新
 */
void
CMiniGameOverView::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CMiniGameOverView::
Draw(void)
{

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff);


}

/*
 *  解放
 */
void
CMiniGameOverView::
Finalize(void)
{
}
