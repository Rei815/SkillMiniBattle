#include "entry.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../data_manager/data_manager.h"

const   CVector3    CEntry::m_spawn_position = CVector3(0.0f, 100.0f, 0.0f);
const   float       CEntry::m_respawn_height = -200.0f;
const   float       CEntry::m_start_time = 30.0f;
const   float       CEntry::m_hold_start_time = 2.0f;
const   float       CEntry::m_exit_time = 0.3f;
const CVector3		CEntry::m_camera_position = CVector3(0, 400.0f, -1600.0f);
const CVector3		CEntry::m_camera_direction = CVector3(0, 0.0f, 0.6f);

CEntry::CEntry(void)
    : m_UnitID(UNIT_ID::PLAYER1)
    , m_GameStartTimer()
    , m_HoldStartTimer(m_hold_start_time)
    , m_HoldTimer()
    , m_WasPressd(false)
    , m_GameStartGauge(nullptr)
    , m_BackGround(UI_ID::GAME_BG)
{

}

CEntry::~CEntry(void)
{
}

void CEntry::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CEffectManager::GetInstance().Initialize();
    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(m_camera_position);
    CCamera::GetInstance().SetDirection(m_camera_direction);
    CObjectManager& om = CObjectManager::GetInstance();
    CUIManager& um = CUIManager::GetInstance();
    CUIManager::UI_LIST uiList = um.GetList();
    um.Initialize();
    m_BackGround.Initialize("data\\Textures\\dodge_ball_bg.jpg");

    CControllerManager& cm = CControllerManager::GetInstance();
    om.Initialize();
    cm.Initialize();

    om.Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT, CTransform(CVector3(0.0f,0.0f, 500.0f)));

    for (int i = 0; i < 4; i++)
    {
        m_PlayerArray[i] = UNIT_ID::NONE;
        m_HoldTimer[i].SetUp(m_hold_start_time);
    }
    m_GameStartTimer.SetUp(m_start_time, CTimer::COUNT_TYPE::DOWN);
    vivid::Vector2  GaugePos = vivid::Vector2(1200, 50);
    float  GaugeScale = 0.3f;
    m_GameStartGauge = (CSkillGauge*)um.Create(UI_ID::SKILL_GAUGE);
    if (m_GameStartGauge)
    {
        m_GameStartGauge->SetGauge(GaugePos,GaugeScale);
    }
}

void CEntry::Update(void)
{
    m_BackGround.Update();
    CControllerManager& cm = CControllerManager::GetInstance();
    CEffectManager::GetInstance().Update();
    CObjectManager& om = CObjectManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();
    cm.Update();
    om.Update();
    um.Update();

    m_WasPressdThisFrame = false;

    m_PlayerNum = 0;
    for (int i = 0; i < 4; i++)
        if (m_PlayerArray[i] != UNIT_ID::NONE)
            m_PlayerNum++;

    //二人以上ならカウントダウンする
    if (m_PlayerNum > 1)
        m_GameStartTimer.Update();
    CUnitManager::UNIT_LIST unitList = um.GetUnitList();
    CUnitManager::UNIT_LIST entryList = unitList;
    if (unitList.empty()) m_UnitID = UNIT_ID::PLAYER1;
    else
    {
        CUnitManager::UNIT_LIST::iterator it = unitList.begin();

        //存在しているプレイヤーのIDを持っておく
        while (it != unitList.end())
        {
            CPlayer* player = (CPlayer*)(*it);
            UNIT_ID unitID = player->GetUnitID();
            if (unitID == UNIT_ID::PLAYER1)
                m_PlayerArray[0] = unitID;
            if (unitID == UNIT_ID::PLAYER2)
                m_PlayerArray[1] = unitID;
            if (unitID == UNIT_ID::PLAYER3)
                m_PlayerArray[2] = unitID;
            if (unitID == UNIT_ID::PLAYER4)
                m_PlayerArray[3] = unitID;

            ++it;
        }
        m_UnitID = UNIT_ID::NONE;

        //IDからいないプレイヤーを探す
        for (int i = 0; i < 4; i++)
        {
            if (m_PlayerArray[i] == UNIT_ID::NONE)
            {
                m_UnitID = (UNIT_ID)i;
                break;
            }
        }
    }
    CheckButtonUp();

    CheckButtonHold();

    CheckButtonDown();

    ////ゲーム開始
    //if (m_GameStartTimer.Finished())
    //{
    //    CDataManager::GetInstance().SetCurrentPlayer(m_PlayerNum);
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTGAME);
    //}
    
#ifdef _DEBUG

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD1))
    {
        if(um.GetPlayer(UNIT_ID::PLAYER1) == nullptr)
            um.Create(UNIT_ID::PLAYER1, m_spawn_position);
        else
        {
            um.Delete(UNIT_ID::PLAYER1);
            m_PlayerArray[0] = UNIT_ID::NONE;
        }
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD2))
    {
        if (um.GetPlayer(UNIT_ID::PLAYER2) == nullptr)
            um.Create(UNIT_ID::PLAYER2, m_spawn_position);
        else
        {
            um.Delete(UNIT_ID::PLAYER2);
            m_PlayerArray[1] = UNIT_ID::NONE;
        }
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD3))
    {
        if (um.GetPlayer(UNIT_ID::PLAYER3) == nullptr)
            um.Create(UNIT_ID::PLAYER3, m_spawn_position);
        else
        {
            um.Delete(UNIT_ID::PLAYER3);
            m_PlayerArray[2] = UNIT_ID::NONE;
        }
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::NUMPAD4))
    {
        if (um.GetPlayer(UNIT_ID::PLAYER4) == nullptr)
            um.Create(UNIT_ID::PLAYER4, m_spawn_position);
        else
        {
            um.Delete(UNIT_ID::PLAYER4);
            m_PlayerArray[3] = UNIT_ID::NONE;
        }
    }
#endif // _DEBUG


    CUnitManager::UNIT_LIST::iterator it = unitList.begin();
    //落ちても戻す
    while (it != unitList.end())
    {
        CPlayer* player = (CPlayer*)(*it);

        ++it;
        if (!player) continue;

        if (player->GetPosition().y < m_respawn_height)
        {
            player->SetPosition(m_spawn_position);
        }

    }
}

void CEntry::Draw(void)
{
    m_BackGround.Draw();
    CEffectManager::GetInstance().Draw();
    CObjectManager& om = CObjectManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();
    om.Draw();
    um.Draw();
    std::string text, timerText;
    timerText = std::to_string((int)m_GameStartTimer.GetTimer());
    switch (m_UnitID)
    {
    case UNIT_ID::PLAYER1:
        text = "次はPLAYER1";
        break;
    case UNIT_ID::PLAYER2:
        text = "次はPLAYER2";
        break;
    case UNIT_ID::PLAYER3:
        text = "次はPLAYER3";

        break;
    case UNIT_ID::PLAYER4:
        text = "次はPLAYER4";

        break;
    case UNIT_ID::NONE:
        text = "最大人数";
        break;
    }
    vivid::DrawText(30, text, vivid::Vector2::ZERO);
    vivid::DrawText(30, timerText, vivid::Vector2(vivid::GetWindowWidth() /2.0f - vivid::GetTextWidth(30, timerText) / 2.0f, 30));

    for (int i = 0; i < 4; i++)
    {
        std::string _text = std::to_string((int)m_PlayerArray[i]);
        vivid::DrawText(30,_text, vivid::Vector2(0, 50 + (30* i)));
    }
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
    CController* buttonHoldController = cm.GetSpecifiedButtonHoldController(BUTTON_ID::X);
    if (buttonHoldController)
    {
        UNIT_ID unitID = buttonHoldController->GetUnitID();
        if (unitID == UNIT_ID::NONE || m_PlayerNum <= 1)
        {
            for (int i = 0; i < 4; i++)
            {
                m_HoldTimer[i].Reset();
            }
            m_GameStartGauge->SetPercent(0.0f);
            return;
        }
        m_HoldTimer[(int)unitID].Update();
        if (m_GameStartGauge)
        {
            float percent = (m_HoldTimer[(int)unitID].GetTimer() - m_exit_time) / (m_hold_start_time - m_exit_time) * 100.0f;
            //退室可能な0.5秒まではゲージを表示しない
            m_GameStartGauge->SetPercent(percent);
        }

        if (m_HoldTimer[(int)unitID].Finished())
        {
            CDataManager::GetInstance().SetCurrentPlayer(m_PlayerNum);
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTGAME);
        }
    }
    CController* controller = nullptr;
    bool         resetGaugeFlag = false;
    //長押ししていないコントローラーのタイマーをリセット
    for (int i = 0; i < 4; i++)
    {
        controller = cm.GetController((CONTROLLER_ID)i);
        UNIT_ID unitID = controller->GetUnitID();

        //プレイヤーを操作できるコントローラーが長押ししていない
        if (!controller->GetButtonHold(BUTTON_ID::X) && unitID != UNIT_ID::NONE)
        {
            resetGaugeFlag = true;
            m_HoldTimer[(int)controller->GetUnitID()].Reset();
        }
        if (controller->GetButtonHold(BUTTON_ID::X) && unitID != UNIT_ID::NONE)
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
    CController* buttonDownController = cm.GetSpecifiedButtonDownController(BUTTON_ID::X);
    if (buttonDownController)
    {
        if (buttonDownController->GetUnitID() == UNIT_ID::NONE)
        {
            if (m_UnitID != UNIT_ID::NONE)
            {
                m_WasPressdThisFrame = true;
                m_WasPressd = true;
                buttonDownController->SetUnitID(m_UnitID);
                CUnitManager::GetInstance().Create(m_UnitID, m_spawn_position);
            }
        }
    }

}

void CEntry::CheckButtonUp(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();

    //ボタンを離した時にm_exit_timeより長押ししてない場合プレイヤーを退出させる
    CController* buttonUpController = cm.GetSpecifiedButtonUpController(BUTTON_ID::X);
    if (buttonUpController)
    {
        UNIT_ID unitID = buttonUpController->GetUnitID();
        if (unitID == UNIT_ID::NONE || m_WasPressdThisFrame || m_WasPressd)
        {
            m_WasPressd = false;
            return;
        }
        float timer = m_HoldTimer[(int)unitID].GetTimer();
        if (timer == 0.0f) return;
        if (timer < m_exit_time)
        {
            UNIT_ID deleteUnitID = buttonUpController->GetUnitID();
            um.Delete(deleteUnitID);
            buttonUpController->SetUnitID(UNIT_ID::NONE);
            m_PlayerArray[(int)deleteUnitID] = UNIT_ID::NONE;
        }
    }

}
