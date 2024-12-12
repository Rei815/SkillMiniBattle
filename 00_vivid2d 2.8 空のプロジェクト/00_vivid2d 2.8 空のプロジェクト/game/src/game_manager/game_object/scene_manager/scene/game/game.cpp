
#include "game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../skill_manager/skill_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../gimmick_manager/gimmick_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../unit_manager/unit/player/player.h"

/*
 *  �R���X�g���N�^
 */
CGame::CGame(void)
    : m_DebugText()
    , m_SetActionflag(false)
    , m_FinishFlag(false)
    , m_EntryList()
    , m_ResultList()
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
CGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    m_EntryList.clear();
    m_ResultList.clear();
    CUnitManager::GetInstance().Initialize();
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
}

/*
 *  �`��
 */
void
CGame::Draw(void)
{
    CEffectManager::GetInstance().Draw();
    CUnitManager::GetInstance().Draw();
    CSkillManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();
    CObjectManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();

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
    IScene::Finalize();

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

void CGame::AddRanking(UNIT_ID unitID)
{
    IUnit* unit = CUnitManager::GetInstance().GetPlayer(unitID);

    for (ENTRY_LIST::iterator entry_it = m_EntryList.begin(); entry_it != m_EntryList.end(); entry_it++)
    {
        if (unitID != UNIT_ID::NONE)
        {
            if ((*entry_it)->GetUnitID() == unitID)
            {
                m_ResultList.push_back(CUnitManager::GetInstance().GetPlayer(unitID));
                m_EntryList.erase(entry_it);
                break;
            }
        }
    }
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

#ifdef VIVID_DEBUG

    if(vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        m_GameState = GAME_STATE::FINISH;

#endif // VIVID_DEBUG

    CheckFinish();
}

/*
 *  �t�B�j�b�V��
 */
void
CGame::
Finish(void)
{
#ifdef VIVID_DEBUG

#endif
    if (!m_FinishFlag)
    {
        Push(SCENE_ID::RESULT_MINIGAME);
        m_FinishFlag = true;
    }
}

void CGame::CheckFinish()
{
}
