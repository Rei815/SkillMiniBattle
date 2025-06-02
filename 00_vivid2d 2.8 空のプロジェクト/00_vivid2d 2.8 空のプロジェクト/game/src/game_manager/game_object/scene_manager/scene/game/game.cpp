
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
const float CGame::m_finish_text_time = 1.2f;

/*
 *  コンストラクタ
 */
CGame::CGame(void)
    : m_WaitTimer()
    , m_CountFlag(true)
    , m_SetActionflag(false)
    , m_FinishFlag(false)
    , m_ResultFlag(false)
    , m_EntryList()
    , m_ResultList()
    , m_BackGround(UI_ID::GAME_BG)
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
    CGimmickManager::GetInstance().Initialize();
    CObjectManager::GetInstance().Initialize();
    CUIManager& um = CUIManager::GetInstance();
    um.Initialize();

    m_WaitTimer.SetUp(m_start_count_time);
    m_CountFlag = true;
    um.Create(UI_ID::START_COUNTDOWN);

    m_GameState = GAME_STATE::START;
}

/*
 *  更新
 */
void
CGame::Update(void)
{
    CEffectManager& em = CEffectManager::GetInstance();
    if(!CSceneManager::GetInstance().Pausing())
    {
        switch (m_GameState)
        {
        case GAME_STATE::START:     Start();        break;
        case GAME_STATE::PLAY:      Play();         break;
        case GAME_STATE::FINISH:    Finish();       break;
        }

        CUnitManager::GetInstance().Update();

        CSkillManager::GetInstance().Update();

        em.Update();

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
    CUnitManager::GetInstance().Draw();
    CSkillManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();
    CObjectManager::GetInstance().Draw();
    CEffectManager::GetInstance().Draw();
    CGimmickManager::GetInstance().Draw();}

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
        if ((*entry_it)->GetUnitID() == unitID)
        {
            //リザルトに登録、エントリーからは削除
            m_ResultList.emplace_back(CUnitManager::GetInstance().GetPlayer(unitID));
            m_EntryList.erase(entry_it);
            break;
        }
    }
}


/*
 *  スタート
 */
void
CGame::Start(void)
{
    CSoundManager::GetInstance().Play_SE(SE_ID::GAME_START, false);

    if (!m_SetActionflag)
    {
        m_SetActionflag = true;
        CUnitManager::GetInstance().SetAllPlayerAction(false);
    }


    if (!CSceneManager::GetInstance().Pausing())
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
    CSoundManager::GetInstance().Play_SE(SE_ID::GAME_FINISH, false);

    if (!m_FinishFlag)
    {
        m_WaitTimer.SetUp(m_finish_text_time);
        CUIManager::GetInstance().Create(UI_ID::FINISH_TEXT);
        m_FinishFlag = true;
    }

    if (m_WaitTimer.Finished())
    {
        if (!m_ResultFlag)
        {
            Push(SCENE_ID::MINIGAME_RESULT);
            m_ResultFlag = true;
        }
    }
    else
    {
        m_WaitTimer.Update();
    }
}

void CGame::CheckFinish()
{
}
