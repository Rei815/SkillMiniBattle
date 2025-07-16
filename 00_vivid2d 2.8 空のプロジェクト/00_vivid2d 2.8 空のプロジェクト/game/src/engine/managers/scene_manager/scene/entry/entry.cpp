#include "entry.h"
#include "..\..\scene_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../ui_manager/ui_manager.h"

#include "../../../../../game/components/player_component/player_id.h"
#include "../../../../../game/components/player_component/player_component.h"
#include "../../../../../engine/components/transform_component/transform_component.h"

const   CVector3        CEntry::m_spawn_position = CVector3(0.0f, 100.0f, 0.0f);
const   float           CEntry::m_respawn_height = -200.0f;
const   float           CEntry::m_start_time = 30.0f;
const   float           CEntry::m_hold_start_time = 2.0f;
const   float           CEntry::m_exit_time = 0.3f;
const   int             CEntry::m_min_player = 2;
const CVector3		    CEntry::m_camera_position = CVector3(0, 400.0f, -1600.0f);
const CVector3		    CEntry::m_camera_direction = CVector3(0, 0.0f, 0.6f);
const CVector3		    CEntry::m_stage_position = CVector3(0.0f, 0.0f, 500.0f);
const vivid::Vector2    CEntry::m_gauge_position = vivid::Vector2(1200, 50);
const float             CEntry::m_gauge_scale = 0.3f;

CEntry::CEntry(void)
    : m_NextUnitID(PLAYER_ID::PLAYER1)
    , m_GameStartTimer()
    , m_HoldStartTimer(m_hold_start_time)
    , m_HoldTimer()
    , m_WasPressd(false)
    , m_GameStartGauge(nullptr)
    , m_BackGround(UI_ID::GAME_BG)
    , m_CanStartFlag(false)
    , m_PlayerJoinUI(nullptr)
{

}

CEntry::~CEntry(void)
{
}

void CEntry::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CObjectManager& om = CObjectManager::GetInstance();
    CUIManager& um = CUIManager::GetInstance();
    CCamera& camera = CCamera::GetInstance();
    CControllerManager& cm = CControllerManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();
    CEffectManager::GetInstance().Initialize();
    camera.Initialize();
    camera.SetPosition(m_camera_position);
    camera.SetDirection(m_camera_direction);
    CUIManager::UI_LIST uiList = um.GetList();
    um.Initialize();
    m_BackGround.Initialize("data\\Textures\\dodge_ball_bg.jpg");

    om.Initialize();
    cm.Initialize();

    om.Create(OBJECT_ID::DODGEBALL_STAGE, CTransform(m_stage_position));
    const int maxPlayerNum = dm.GetMaxJoinPlayerNum();
    for (int i = 0; i < maxPlayerNum; i++)
    {
        m_PlayerArray[i] = PLAYER_ID::NONE;
    }
    const int ActiveControllerNum = dm.GetActiveControllerNum();
    for (int i = 0; i < ActiveControllerNum; i++)
    {
        m_HoldTimer[i].SetUp(m_hold_start_time);
    }
    m_GameStartTimer.SetUp(m_start_time, CTimer::COUNT_TYPE::DOWN);
    m_GameStartGauge = dynamic_pointer_cast<CSkillGauge>(um.Create(UI_ID::SKILL_GAUGE));
    if (m_GameStartGauge)
    {
        m_GameStartGauge->SetGauge(m_gauge_position,m_gauge_scale);
    }
    um.Create(UI_ID::ENTRY_X_BUTTON);

    m_PlayerJoinUI = dynamic_pointer_cast<CPlayerJoin>(um.Create(UI_ID::PLAYER_JOIN));

}

void CEntry::Update(void)
{
    IScene::Update();
    m_BackGround.Update();
    CControllerManager& cm = CControllerManager::GetInstance();
    CEffectManager::GetInstance().Update();
    CObjectManager& om = CObjectManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();

    cm.Update();
    om.Update();

    m_CanStartFlag = true;

    m_PlayerNum = 0;
    const int maxPlayerNum = dm.GetMaxJoinPlayerNum();
    for (int i = 0; i < maxPlayerNum; i++)
    {
        if (m_PlayerArray[i] != PLAYER_ID::NONE)
            m_PlayerNum++;
    }
    for (int i = 0; i < m_PlayerNum; i++)
    {
        if (m_PlayerArray[i] != (PLAYER_ID)i)
        {
            m_CanStartFlag = false;
            break;
        }
    }
    //二人以上ならカウントダウンする
    if (m_PlayerNum >= m_min_player)
        m_GameStartTimer.Update();
    auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
    if (allPlayers.empty())
        m_NextUnitID = PLAYER_ID::PLAYER1;
    else
    {
        for (auto& player : allPlayers)
        {
			if (auto playerComp = player->GetComponent<PlayerComponent>())
			{
				PLAYER_ID playerID = playerComp->GetPlayerID();
				if (playerID == PLAYER_ID::NONE) continue;
				//プレイヤーがいればそのIDを登録
				if (m_PlayerArray[(int)playerID] == PLAYER_ID::NONE)
				{
                    m_PlayerArray[(int)playerID] = playerID;
                }
			}
        }
        m_NextUnitID = PLAYER_ID::NONE;

        //IDからいないプレイヤーを探す
        for (int i = 0; i < maxPlayerNum; i++)
        {
            if (m_PlayerArray[i] == PLAYER_ID::NONE)
            {
                m_NextUnitID = (PLAYER_ID)i;
                break;
            }
        }
    }
    CheckButtonUp();

    CheckButtonHold();

    CheckButtonDown();

    //落ちても戻す
    for (auto& player : allPlayers)
    {
        if (auto transform = player->GetComponent<TransformComponent>())
        {
            if (transform->GetPosition().y < m_respawn_height)
                transform->SetPosition(m_spawn_position);
        }

    }
}

void CEntry::Draw(void)
{
    m_BackGround.Draw();
    CEffectManager::GetInstance().Draw();
    CObjectManager::GetInstance().Draw();
}

void CEntry::Finalize(void)
{
    m_BackGround.Finalize();
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
    CObjectManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
}

void CEntry::CheckButtonHold(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();

    //ボタンを長押ししている時の処理
    //人数が二人以上でm_hold_start_time以上長押ししているコントローラーがある時ゲーム開始
    std::shared_ptr<CController> buttonHoldController = cm.GetSpecifiedButtonHoldController(BUTTON_ID::X);
    if (buttonHoldController)
    {
        PLAYER_ID unitID = buttonHoldController->GetPlayerID();

        //プレイヤーがいなくなったらタイマーのリセット
        if (unitID == PLAYER_ID::NONE)
        {
            const int ActiveControllerNum = CDataManager::GetInstance().GetActiveControllerNum();
            for (int i = 0; i < ActiveControllerNum; i++)
            {
                m_HoldTimer[i].Reset();
            }
            //ゲージもリセット
            m_GameStartGauge->SetPercent(0.0f);
            return;
        }
        m_HoldTimer[(int)unitID].Update();
        if (m_GameStartGauge && m_CanStartFlag)
        {
            float percent = (m_HoldTimer[(int)unitID].GetTimer() - m_exit_time) / (m_hold_start_time - m_exit_time) * 100.0f;
            //退室可能な0.5秒まではゲージを表示しない
            m_GameStartGauge->SetPercent(percent);
        }

        //ゲージ最大まで長押ししたら開始
        if (m_HoldTimer[(int)unitID].Finished() && m_CanStartFlag)
        {
            //一人の場合、ダミーコントローラーを2Pとして扱う
            if (m_PlayerNum == 1)
            {
                std::shared_ptr<CController> dummy = cm.GetController(CONTROLLER_ID::DUMMY);
                dummy->SetPlayerID(m_NextUnitID);

                CObjectManager::GetInstance().Create(OBJECT_ID::PLAYER, m_spawn_position, m_NextUnitID);
                m_PlayerNum++;
            }

            CDataManager::GetInstance().SetCurrentJoinPlayer(m_PlayerNum);
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAME_ROLL_AND_REVEAL);
        }
    }
    std::shared_ptr<CController> controller = nullptr;
    bool         resetGaugeFlag = false;
    //長押ししていないコントローラーのタイマーをリセット
    for (int i = 0; i < 5; i++)
    {
        controller = cm.GetController((CONTROLLER_ID)i);
        PLAYER_ID unitID = controller->GetPlayerID();

        //プレイヤーを操作できるコントローラーが長押ししていない
        if (!controller->GetButtonHold(BUTTON_ID::X) && unitID != PLAYER_ID::NONE)
        {
            resetGaugeFlag = true;
            m_HoldTimer[(int)controller->GetPlayerID()].Reset();
        }
        if (controller->GetButtonHold(BUTTON_ID::X) && unitID != PLAYER_ID::NONE)
        {
            resetGaugeFlag = false;
            break;
        }
    }
    if (m_GameStartGauge && resetGaugeFlag)
        m_GameStartGauge->SetPercent(0.0f);
}

void CEntry::CheckButtonDown(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    //ボタンを押したときにコントローラーが動かせるプレイヤーがいない場合プレイヤー生成
    std::shared_ptr<CController> buttonDownController = cm.GetSpecifiedButtonDownController(BUTTON_ID::X);
    if (buttonDownController)
    {
        if (buttonDownController->GetPlayerID() == PLAYER_ID::NONE && m_NextUnitID != PLAYER_ID::NONE)
        {
            m_WasPressd = true;
            buttonDownController->SetPlayerID(m_NextUnitID);
            CObjectManager::GetInstance().Create(OBJECT_ID::PLAYER, m_spawn_position, m_NextUnitID);
            m_PlayerJoinUI->SetPlayer(m_NextUnitID, true);
        }
    }

}

void CEntry::CheckButtonUp(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();

    std::shared_ptr<CController> buttonUpController = cm.GetSpecifiedButtonUpController(BUTTON_ID::X);

    if (buttonUpController)
    {
        PLAYER_ID playerID = buttonUpController->GetPlayerID();
        if (playerID == PLAYER_ID::NONE || m_WasPressd)
        {
            m_WasPressd = false;
            return;
        }
        float timer = m_HoldTimer[(int)playerID].GetTimer();
        if (timer == 0.0f) return;
        //ボタンを離した時にm_exit_timeより長押ししてない場合プレイヤーを退出させる
        if (timer < m_exit_time)
        {
            PLAYER_ID deletePlayerID = buttonUpController->GetPlayerID();
			CObjectManager::GetInstance().DeletePlayer(deletePlayerID);
            buttonUpController->SetPlayerID(PLAYER_ID::NONE);
            m_PlayerArray[(int)deletePlayerID] = PLAYER_ID::NONE;
            m_PlayerJoinUI->SetPlayer(deletePlayerID, false);
        }
    }

}
