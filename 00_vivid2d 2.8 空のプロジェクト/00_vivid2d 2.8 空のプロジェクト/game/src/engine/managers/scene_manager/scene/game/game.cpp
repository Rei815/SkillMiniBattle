
#include "game.h"
#include "..\..\scene_manager.h"
#include "../../../skill_manager/skill_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../../../game/components/player_component/player_component.h"


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

        CSkillManager::GetInstance().Update();

        em.Update();

        CObjectManager::GetInstance().Update();
    }

    CControllerManager::GetInstance().Update();
}

/*
 *  描画
 */
void
CGame::Draw(void)
{
    CSkillManager::GetInstance().Draw();
    CObjectManager::GetInstance().Draw();
    CEffectManager::GetInstance().Draw();
}
/*
 *  解放
 */
void
CGame::Finalize(void)
{
    IScene::Finalize();

    CSkillManager::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
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

void CGame::AddRanking(PLAYER_ID playerID)
{
    auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

    for (ENTRY_LIST::iterator entry_it = m_EntryList.begin(); entry_it != m_EntryList.end(); entry_it++)
    {
        if ((*entry_it)->GetComponent<PlayerComponent>()->GetPlayerID() == playerID)
        {

            //リザルトに登録、エントリーからは削除
            m_ResultList.emplace_back(*entry_it);
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
		auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
        for (auto& player : allPlayers)
        {
			if (auto playerComp = player->GetComponent<PlayerComponent>())
			{
				playerComp->SetActionFlag(false);
			}
        }
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

                auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
                for (auto& player : allPlayers)
                {
                    if (auto playerComp = player->GetComponent<PlayerComponent>())
                    {
                        playerComp->SetActionFlag(true);
                    }
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
