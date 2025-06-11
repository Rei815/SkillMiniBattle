#include "entry.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../data_manager/data_manager.h"

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
    : m_NextUnitID(UNIT_ID::PLAYER1)
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

    om.Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT, CTransform(m_stage_position));
    const int maxPlayerNum = dm.GetMaxJoinPlayerNum();
    for (int i = 0; i < maxPlayerNum; i++)
    {
        m_PlayerArray[i] = UNIT_ID::NONE;
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
    CUnitManager& um = CUnitManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();

    cm.Update();
    om.Update();
    um.Update();

    m_CanStartFlag = true;

    m_PlayerNum = 0;
    const int maxPlayerNum = dm.GetMaxJoinPlayerNum();
    for (int i = 0; i < maxPlayerNum; i++)
    {
        if (m_PlayerArray[i] != UNIT_ID::NONE)
            m_PlayerNum++;
    }
    for (int i = 0; i < m_PlayerNum; i++)
    {
        if (m_PlayerArray[i] != (UNIT_ID)i)
        {
            m_CanStartFlag = false;
            break;
        }
    }
    //��l�ȏ�Ȃ�J�E���g�_�E������
    if (m_PlayerNum >= m_min_player)
        m_GameStartTimer.Update();
    CUnitManager::UNIT_LIST unitList = um.GetUnitList();
    CUnitManager::UNIT_LIST entryList = unitList;
    if (unitList.empty()) m_NextUnitID = UNIT_ID::PLAYER1;
    else
    {
        CUnitManager::UNIT_LIST::iterator it = unitList.begin();

        //���݂��Ă���v���C���[��ID�������Ă���
        while (it != unitList.end())
        {
            std::shared_ptr<CPlayer> player = dynamic_pointer_cast<CPlayer>(*it);
            ++it;
            if (player == nullptr) continue;
            UNIT_ID unitID = player->GetUnitID();
            if (unitID == UNIT_ID::PLAYER1)
                m_PlayerArray[0] = unitID;
            if (unitID == UNIT_ID::PLAYER2)
                m_PlayerArray[1] = unitID;
            if (unitID == UNIT_ID::PLAYER3)
                m_PlayerArray[2] = unitID;
            if (unitID == UNIT_ID::PLAYER4)
                m_PlayerArray[3] = unitID;

        }
        m_NextUnitID = UNIT_ID::NONE;

        //ID���炢�Ȃ��v���C���[��T��
        for (int i = 0; i < maxPlayerNum; i++)
        {
            if (m_PlayerArray[i] == UNIT_ID::NONE)
            {
                m_NextUnitID = (UNIT_ID)i;
                break;
            }
        }
    }
    CheckButtonUp();

    CheckButtonHold();

    CheckButtonDown();

    CUnitManager::UNIT_LIST::iterator it = unitList.begin();
    //�����Ă��߂�
    while (it != unitList.end())
    {
        std::shared_ptr<CPlayer> player = dynamic_pointer_cast<CPlayer>(*it);

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
    CObjectManager::GetInstance().Draw();
    CUnitManager::GetInstance().Draw();
}

void CEntry::Finalize(void)
{
    m_BackGround.Finalize();
    IScene::Finalize();
    CUnitManager::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    CObjectManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
}

void CEntry::CheckButtonHold(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();

    //�{�^���𒷉������Ă��鎞�̏���
    //�l������l�ȏ��m_hold_start_time�ȏ㒷�������Ă���R���g���[���[�����鎞�Q�[���J�n
    std::shared_ptr<CController> buttonHoldController = cm.GetSpecifiedButtonHoldController(BUTTON_ID::X);
    if (buttonHoldController)
    {
        UNIT_ID unitID = buttonHoldController->GetUnitID();

        //�v���C���[�����Ȃ��Ȃ�����^�C�}�[�̃��Z�b�g
        if (unitID == UNIT_ID::NONE)
        {
            const int ActiveControllerNum = CDataManager::GetInstance().GetActiveControllerNum();
            for (int i = 0; i < ActiveControllerNum; i++)
            {
                m_HoldTimer[i].Reset();
            }
            //�Q�[�W�����Z�b�g
            m_GameStartGauge->SetPercent(0.0f);
            return;
        }
        m_HoldTimer[(int)unitID].Update();
        if (m_GameStartGauge && m_CanStartFlag)
        {
            float percent = (m_HoldTimer[(int)unitID].GetTimer() - m_exit_time) / (m_hold_start_time - m_exit_time) * 100.0f;
            //�ގ��\��0.5�b�܂ł̓Q�[�W��\�����Ȃ�
            m_GameStartGauge->SetPercent(percent);
        }

        //�Q�[�W�ő�܂Œ�����������J�n
        if (m_HoldTimer[(int)unitID].Finished() && m_CanStartFlag)
        {
            //��l�̏ꍇ�A�_�~�[�R���g���[���[��2P�Ƃ��Ĉ���
            if (m_PlayerNum == 1)
            {
                std::shared_ptr<CController> dummy = cm.GetController(CONTROLLER_ID::DUMMY);
                dummy->SetUnitID(m_NextUnitID);

                CUnitManager::GetInstance().Create(m_NextUnitID, m_spawn_position);
                m_PlayerNum++;
            }

            CDataManager::GetInstance().SetCurrentJoinPlayer(m_PlayerNum);
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAME_ROLL_AND_REVEAL);
        }
    }
    std::shared_ptr<CController> controller = nullptr;
    bool         resetGaugeFlag = false;
    //���������Ă��Ȃ��R���g���[���[�̃^�C�}�[�����Z�b�g
    for (int i = 0; i < 5; i++)
    {
        controller = cm.GetController((CONTROLLER_ID)i);
        UNIT_ID unitID = controller->GetUnitID();

        //�v���C���[�𑀍�ł���R���g���[���[�����������Ă��Ȃ�
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
    //�{�^�����������Ƃ��ɃR���g���[���[����������v���C���[�����Ȃ��ꍇ�v���C���[����
    std::shared_ptr<CController> buttonDownController = cm.GetSpecifiedButtonDownController(BUTTON_ID::X);
    if (buttonDownController)
    {
        if (buttonDownController->GetUnitID() == UNIT_ID::NONE && m_NextUnitID != UNIT_ID::NONE)
        {
            m_WasPressd = true;
            buttonDownController->SetUnitID(m_NextUnitID);
            CUnitManager::GetInstance().Create(m_NextUnitID, m_spawn_position);
            m_PlayerJoinUI->SetPlayer(m_NextUnitID, true);
        }
    }

}

void CEntry::CheckButtonUp(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();

    std::shared_ptr<CController> buttonUpController = cm.GetSpecifiedButtonUpController(BUTTON_ID::X);

    if (buttonUpController)
    {
        UNIT_ID unitID = buttonUpController->GetUnitID();
        if (unitID == UNIT_ID::NONE || m_WasPressd)
        {
            m_WasPressd = false;
            return;
        }
        float timer = m_HoldTimer[(int)unitID].GetTimer();
        if (timer == 0.0f) return;
        //�{�^���𗣂�������m_exit_time��蒷�������ĂȂ��ꍇ�v���C���[��ޏo������
        if (timer < m_exit_time)
        {
            UNIT_ID deleteUnitID = buttonUpController->GetUnitID();
            um.Delete(deleteUnitID);
            buttonUpController->SetUnitID(UNIT_ID::NONE);
            m_PlayerArray[(int)deleteUnitID] = UNIT_ID::NONE;
            m_PlayerJoinUI->SetPlayer(deleteUnitID, false);
        }
    }

}
