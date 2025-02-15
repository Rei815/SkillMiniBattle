#include "minigame_manual.h"
#include "../../../data_manager/data_manager.h"

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
 *  �R���X�g���N�^
 */
CMiniGameManual::
CMiniGameManual(UI_ID id)
	: CUI(id)
{
}

/*
 *  �f�X�g���N�^
 */
CMiniGameManual::
~CMiniGameManual(void)
{
}

/*
 *  ������
 */
void
CMiniGameManual::
Initialize(void)
{
	CUI::Initialize(m_position);
	CUI* bg = CUIManager::GetInstance().Create(UI_ID::NOTICE, m_bg_position);
	bg->SetScale(m_bg_scale);
	CUIManager::GetInstance().Create(UI_ID::TEXT_MANUAL);

	SetOrderInLayer(1);

	m_FileName = m_file_name[(int)CDataManager::GetInstance().GetSelectGameID()];
}

/*
 *  �X�V
 */
void
CMiniGameManual::
Update(void)
{
	CUI::Update();
}

/*
 *  �`��
 */
void
CMiniGameManual::
Draw(void)
{
	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff);
}

/*
 *  ���
 */
void
CMiniGameManual::
Finalize(void)
{
}
