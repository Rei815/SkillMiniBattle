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
const CVector3		CEntry::m_camera_position = CVector3(0, 400.0f, -1600.0f);
const CVector3		CEntry::m_camera_direction = CVector3(0, 0.0f, 0.6f);
CEntry::CEntry(void)
    : m_UnitID(UNIT_ID::PLAYER1)
    , m_StartTimer(m_start_time)
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
    //um.Create(UI_ID::TITLE_LOGO);

    CControllerManager& cm = CControllerManager::GetInstance();
    om.Initialize();
    cm.Initialize();

    om.Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT, CTransform(CVector3(0.0f,0.0f, 500.0f)));

    m_PlayerControllerList.clear();

    for (int i = 0; i < 4; i++)
    {
        m_PlayerArray[i] = UNIT_ID::NONE;
    }

}

void CEntry::Update(void)
{
    int playerNum = 0;
    for (int i = 0; i < 4; i++)
        if (m_PlayerArray[i] != UNIT_ID::NONE)
            playerNum++;

    //二人以上ならタイマースタート
    if(playerNum > 1)
        m_StartTimer.Update();
    CControllerManager& cm = CControllerManager::GetInstance();
    CEffectManager::GetInstance().Update();
    CObjectManager& om = CObjectManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();
    cm.Update();
    om.Update();
    um.Update();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    CController* controller_2 = cm.GetController(CONTROLLER_ID::TWO);
    CController* controller_3 = cm.GetController(CONTROLLER_ID::THREE);
    CController* controller_4 = cm.GetController(CONTROLLER_ID::FOUR);
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
    CController* controller = cm.GetSpecifiedButtonDownController(BUTTON_ID::ANY);
    if (controller)
    {
        if(controller->GetUnitID() == UNIT_ID::NONE)
        {
            if (m_UnitID != UNIT_ID::NONE)
            {
                controller->SetUnitID(m_UnitID);
                CUnitManager::GetInstance().Create(m_UnitID, m_spawn_position);
            }
        }
    }
    //controller = cm.GetSpecifiedButtonDownController(BUTTON_ID::Y);
    //if (controller)
    //{
    //    if(controller->GetUnitID() != UNIT_ID::NONE)
    //    {
    //        UNIT_ID deleteUnitID = controller->GetUnitID();
    //        um.Delete(deleteUnitID);
    //        controller->SetUnitID(UNIT_ID::NONE);
    //        m_PlayerArray[(int)deleteUnitID] = UNIT_ID::NONE;
    //    }
    //}

    //ゲーム開始
    if (m_StartTimer.Finished())
    {
        CDataManager::GetInstance().SetCurrentPlayer(playerNum);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTGAME);
    }
    controller = cm.GetSpecifiedButtonDownController(BUTTON_ID::START);
    if (controller)
    {
        bool correctFlag = true;
        for (int i = 0; i < playerNum; i++)
        {
            if (m_PlayerArray[i] == UNIT_ID::NONE)
            {
                correctFlag = false;
                break;
            }
        }
        if (correctFlag)
        {
        }
    }
    

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
    CEffectManager::GetInstance().Draw();
    CObjectManager& om = CObjectManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();
    om.Draw();
    um.Draw();
    std::string text, timerText;
    timerText = std::to_string((int)m_StartTimer.GetTimer());
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
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
    CObjectManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
}
