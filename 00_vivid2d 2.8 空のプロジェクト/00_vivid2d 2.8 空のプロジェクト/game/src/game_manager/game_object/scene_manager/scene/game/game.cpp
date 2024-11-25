
#include "game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../skill_manager/skill_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../gimmick_manager/gimmick_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../unit_manager/unit/player/player.h"

/*
 *  �R���X�g���N�^
 */
CGame::CGame(void)
    : m_DebugText()
    , m_SetActionflag(false)
    , m_FinishUIFlag(false)
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
    CGimmickManager::GetInstance().Initialize();
    CObjectManager::GetInstance().Initialize();
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
        else
            CUIManager::GetInstance().Create(UI_ID::PAUSE);

        m_PauseFlag ^= true;
    }
    if(!m_PauseFlag)
    {
        CUnitManager::GetInstance().Update();

        CSkillManager::GetInstance().Update();

        CUIManager::GetInstance().Update();

        CEffectManager::GetInstance().Update();
    }
    CControllerManager::GetInstance().Update();
    CGimmickManager::GetInstance().Update();
    CObjectManager::GetInstance().Update();

    CUnitManager::GetInstance().CheckDefeat();
}

/*
 *  �`��
 */
void
CGame::Draw(void)
{
    CUnitManager::GetInstance().Draw();
    CSkillManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();
    CEffectManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();
    CObjectManager::GetInstance().Draw();

#ifdef VIVID_DEBUG
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
        vivid::DrawText(20, std::to_string(CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1)->GetWins()),
            vivid::Vector2(vivid::GetWindowWidth() - 20, 0)
        );
        break;
    }
    vivid::DrawText(20, m_DebugText, vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
#endif
}

/*
 *  ���
 */
void
CGame::Finalize(void)
{
    CUnitManager::GetInstance().Finalize();
    CSkillManager::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
    CControllerManager::GetInstance().Finalize();
    CGimmickManager::GetInstance().Finalize();
    CObjectManager::GetInstance().Finalize();
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

     if ((CUnitManager::GetInstance().GetCurrentPlayer() - CUnitManager::GetInstance().GetDefeatList().size()) < 1)
        m_GameState = GAME_STATE::FINISH;

#ifdef VIVID_DEBUG

    if(vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        m_GameState = GAME_STATE::FINISH;

#endif // VIVID_DEBUG

}

/*
 *  �t�B�j�b�V��
 */
void
CGame::
Finish(void)
{
#ifdef VIVID_DEBUG

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::RESULT);
#endif
    if (!m_FinishUIFlag)
    {
        m_FinishUIFlag = true;
        CUIManager::GetInstance().Create(UI_ID::FINISH_BACKGROUND);
    }

}
