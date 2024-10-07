
#include "game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../gimmick_manager/gimmick_manager.h"
#include "../../../unit_manager/unit/player/player.h"

/*
 *  �R���X�g���N�^
 */
CGame::CGame(void)
    : m_DebugText()
    , m_SetActionflag(false)
{
}

/*
 *  �f�X�g���N�^
 */
CGame::~CGame(void)
{
}

/*
 *  ������
 */
void
CGame::Initialize(void)
{
    CUnitManager::GetInstance().Initialize();
    CUIManager::GetInstance().Initialize();
    CEffectManager::GetInstance().Initialize();
    CControllerManager::GetInstance().Initialize();
    CStage::GetInstance().Initialize();
    CGimmickManager::GetInstance().Initialize();
    m_WaitTime = 0;


    m_GameState = GAME_STATE::START;

    m_PauseFlag = false;
    m_DebugText = "�e�Q�[���V�[��";
}

/*
 *  �X�V
 */
void
CGame::Update(void)
{
    switch (m_GameState)
    {
    case GAME_STATE::START:     Start();        break;
    case GAME_STATE::PLAY:      Play();         break;
    case GAME_STATE::FINISH:    Finish();       break;
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TAB))
    {
        if (m_PauseFlag)
             CUIManager::GetInstance().Delete(UI_ID::PAUSE);
        else CUIManager::GetInstance().Create(UI_ID::PAUSE);

        m_PauseFlag ^= true;
    }
    if(!m_PauseFlag)
    {
        CStage::GetInstance().Update();
        CUnitManager::GetInstance().Update();

        CEffectManager::GetInstance().Update();

        CUIManager::GetInstance().Update();
    }
    CControllerManager::GetInstance().Update();
    CGimmickManager::GetInstance().Update();
}

/*
 *  �`��
 */
void
CGame::Draw(void)
{
    CStage::GetInstance().Draw();

    CEffectManager::GetInstance().Draw();
    CUnitManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();
    switch (m_GameState)
    {
    case GAME_STATE::START:
        vivid::DrawText(20, "�X�^�[�g", vivid::Vector2(0, 0));

        break;
    case GAME_STATE::PLAY:
        vivid::DrawText(20, "�v���C", vivid::Vector2(0, 0));

        break;
    case GAME_STATE::FINISH:
        vivid::DrawText(20, "�t�B�j�b�V��", vivid::Vector2(0, 0));

        break;
    }
    vivid::DrawText(20, m_DebugText, vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

/*
 *  ���
 */
void
CGame::Finalize(void)
{
    CUnitManager::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
    CControllerManager::GetInstance().Finalize();
    CGimmickManager::GetInstance().Finalize();
    CStage::GetInstance().Finalize();
}

/*
 *  �Q�[���̏�Ԏ擾
 */
GAME_STATE
CGame::GetGameState(void)
{
    return m_GameState;
}

/*
 *  �Q�[���̏�Ԑݒ�
 */
void
CGame::
SetGameState(GAME_STATE state)
{
    m_GameState = state;
}


/*
 *  �X�^�[�g
 */
void
CGame::Start(void)
{
    if (!m_SetActionflag)
    {
        m_SetActionflag = true;
        CUnitManager::GetInstance().SetAllPlayerAction(false);
    }
    if (m_WaitTime > 120)
    {
        m_WaitTime = 0;

        m_GameState = GAME_STATE::PLAY;
    }

    ++m_WaitTime;

}

/*
 *  �v���C
 */
void CGame::Play(void)
{
    if (m_SetActionflag)
    {
        m_SetActionflag = false;
        CUnitManager::GetInstance().SetAllPlayerAction(true);
    }

    if(vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        m_GameState = GAME_STATE::FINISH;

}

/*
 *  �t�B�j�b�V��
 */
void
CGame::
Finish(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::RESULT);
}
