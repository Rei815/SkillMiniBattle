
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


const float CGame::m_start_count_time = 3.0f;
const float CGame::m_start_text_time = 1.0f;

/*
 *  コンストラクタ
 */
CGame::CGame(void)
    : m_DebugText()
    , m_WaitTimer()
    , m_CountFlag(true)
    , m_SetActionflag(false)
    , m_FinishFlag(false)
    , m_EntryList()
    , m_ResultList()
{
}

/*
 *  デストラクタ
 */
CGame::~CGame(void)
{
}

/*
 *  初期化
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

    m_WaitTimer.SetUp(m_start_count_time);
    m_CountFlag = true;
    CUIManager::GetInstance().Create(UI_ID::START_COUNTDOWN);

    m_GameState = GAME_STATE::START;

    m_PauseFlag = false;
    m_DebugText = "親ゲームシーン";
}

/*
 *  更新
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

        CObjectManager::GetInstance().Update();
        CGimmickManager::GetInstance().Update();
    }
    CControllerManager::GetInstance().Update();
}

/*
 *  描画
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
        vivid::DrawText(20, "スタート", vivid::Vector2(0, 0));

        break;
    case GAME_STATE::PLAY:
        vivid::DrawText(20, "プレイ", vivid::Vector2(0, 0));

        break;
    case GAME_STATE::FINISH:
        vivid::DrawText(20, "フィニッシュ", vivid::Vector2(0, 0));
        break;
    }
    vivid::DrawText(20, m_DebugText, vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
#endif
}

/*
 *  解放
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
 *  ゲームの状態取得
 */
GAME_STATE
CGame::GetGameState(void)
{
    return m_GameState;
}

/*
 *  ゲームの状態設定
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
 *  スタート
 */
void
CGame::Start(void)
{
    if (!m_SetActionflag)
    {
        m_SetActionflag = true;
        CUnitManager::GetInstance().SetAllPlayerAction(false);
    }


    if (!m_PauseFlag)
    {
        m_WaitTimer.Update();

        if (m_WaitTimer.Finished())
        {
            if (m_CountFlag)
            {
                m_CountFlag = false;
                m_WaitTimer.SetUp(m_start_text_time);

                CUIManager::GetInstance().Create(UI_ID::START_TEXT);
            }
            else
            {
                m_GameState = GAME_STATE::PLAY;

                CPlayer* TempPlayer;

                for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
                {
                    TempPlayer = CUnitManager::GetInstance().GetPlayer((UNIT_ID)i);
                    TempPlayer->SetActionFlag(true);
                }
            }
        }
    }
}

/*
 *  プレイ
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
 *  フィニッシュ
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
