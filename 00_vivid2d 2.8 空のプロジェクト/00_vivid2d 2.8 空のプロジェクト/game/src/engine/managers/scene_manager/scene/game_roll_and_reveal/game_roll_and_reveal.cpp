#include "game_roll_and_reveal.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"
#include "../../../animation_manager/animation/animation.h"
#include "../../../animation_manager/animation_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../ui_manager/ui/game_video/game_video.h"
#include "../../../ui_manager/ui/player_ready/player_ready.h"
#include "../../../controller_manager/controller_manager.h"
#include <random>
#include <iostream>

const int CGameRollAndReveal::m_games_num = 4;
const float CGameRollAndReveal::m_circle_radius = 500.0f;
const float CGameRollAndReveal::m_circle_height = 500.0f;
CGameRollAndReveal::CGameRollAndReveal(void)
    : m_SelectedGameFlag(false)
    , m_GameInfomationFlag(false)
    , m_PlaneUIParent(nullptr)
    , m_RevealUIParent(nullptr)
    , m_SelectedGameID(GAME_ID::MAX)
    , m_SelectedPlane(nullptr)
{

}

CGameRollAndReveal::~CGameRollAndReveal(void)
{
}

void CGameRollAndReveal::Initialize(SCENE_ID scene_id)
{
    SetLightDirection(CVector3::DOWN);
    //���C�e�B���O�̏����ݒ�
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Power = 20.0f;
    SetMaterialParam(Material);

    IScene::Initialize(scene_id);
    CUIManager& um = CUIManager::GetInstance();

    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -1000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CAnimationManager::GetInstance().Initialize();

    um.Initialize();
    um.Create(UI_ID::TITLE_LOGO);
    CSoundManager::GetInstance().Play_BGM(BGM_ID::READY_BGM, true);

    CUIManager::UI_LIST uiList = um.GetList();
    int maxGameNum = CDataManager::GetInstance().GetMaxGameNum();
    //�Q�[���̉摜���~�󂩂ϓ��ɔz�u
    for (int i = 0; i < maxGameNum; i++)
    {
        CTransform transform;
        const float rad = i / (float)maxGameNum * DX_TWO_PI;
        const float _x = m_circle_radius * sin(rad);
        const float _z = m_circle_radius * cos(rad);
        transform.rotation.y = i * (360.0f / (float)maxGameNum);
        transform.position.y = m_circle_height;
        transform.position.x = 0.0f;//_x;
        transform.position.z = -m_circle_radius;//_z;
        
        std::shared_ptr<CPlaneGameImage> planeGameImage = dynamic_pointer_cast<CPlaneGameImage>(um.Create(UI_ID::PLANE_GAME_IMAGE, transform));
        planeGameImage->SetGameID((GAME_ID)i);
    }

    m_PlaneUIParent = dynamic_pointer_cast<CSceneUIParent>(um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2)));
    m_PlaneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

    //�~�j�Q�[���̌���
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, (int)GAME_ID::MAX - 1);
    int game_id = dist(gen);
    m_SelectedGameID = (GAME_ID)game_id;
    CDataManager::GetInstance().SetGameID(m_SelectedGameID);
}

void CGameRollAndReveal::Update(void)
{

    CControllerManager& cm = CControllerManager::GetInstance();
    CAnimationManager& am = CAnimationManager::GetInstance();
    CUIManager& um = CUIManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();

    cm.Update();

    CCamera::GetInstance().Update();
    am.Update();

#if _DEBUG

    //�L�[�{�[�h��1,2,3,4�L�[�ŔC�ӂ̃~�j�Q�[����I�ׂ�

    //1�L�[�ł���܂��񂪂����
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
    {
        m_SelectedGameID = GAME_ID::DARUMA_FALL_DOWN_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }

    //�Q�L�[�Ńt�H�[���A�E�g
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
    {
        m_SelectedGameID = GAME_ID::FALLOUT_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }

    //�R�L�[�Ńh�b�a�{�[��
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
    {
        m_SelectedGameID = GAME_ID::DODGE_BALL_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }

    //�S�L�[�Ńx���g�R���x�A�[
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::FOUR))
    {
        m_SelectedGameID = GAME_ID::BELT_CONVEYOR_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }
#endif // _DEBUG

    CUIManager::UI_LIST uiList = um.GetList();
    if (m_PlaneUIParent)
    {
        //���S�ɂ�����e�q�֌W������
        if (m_PlaneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
        {
            m_PlaneUIParent->ReleaseChildren();
            m_PlaneUIParent->Delete();
            m_PlaneUIParent = nullptr;
        }

    }

    //�~�j�Q�[���摜���^�񒆗������ƁA�����ꂩ�̃R���g���[���[��B�{�^���������ꂽ��I�΂ꂽ�~�j�Q�[���摜���㏸�A����ȊO�͎��k
    if (cm.GetSpecifiedButtonDownController(BUTTON_ID::B) && m_PlaneUIParent == nullptr && m_SelectedGameFlag == false)
    {

            uiList = um.GetList();
            CUIManager::UI_LIST::iterator it = uiList.begin();

            while (it != uiList.end())
            {
                std::shared_ptr<CPlaneGameImage> planeGameImage = dynamic_pointer_cast<CPlaneGameImage>(*it);
                ++it;

                //�_�E���L���X�g�`�F�b�N
                if (planeGameImage == nullptr) continue;

                if (planeGameImage->GetGameID() == m_SelectedGameID)
                {
                    m_SelectedPlane = dynamic_pointer_cast<CPlaneGameImage>(planeGameImage);
                    if (m_SelectedPlane == nullptr) return;

                    std::shared_ptr<IAnimation> animation = nullptr;
                    animation = am.Create(ANIMATION_ID::PLANE_UP, planeGameImage);
                    if (animation == nullptr) return;

                    m_SelectedPlane->SetAnimation(animation);
                    m_SelectedGameFlag = true;
                }
                else
                {
                    // �I�΂�Ă��Ȃ����̂͏������Ȃ�
                    std::shared_ptr<IAnimation> animation = nullptr;
                    animation = am.Create(ANIMATION_ID::PLANE_SCALE, planeGameImage);
                    if (animation == nullptr) return;

                    planeGameImage->SetAnimation(animation);
                }
            }
    }
    if (m_SelectedGameFlag == true)
    {
        //�㏸�A�j���[�V�������I���������ƁA������ʂ��o��
        if (m_SelectedPlane->GetAnimation() == nullptr && m_GameInfomationFlag == false)
        {
            m_SelectedPlane->Delete();
            m_GameInfomationFlag = true;
            um.Create(UI_ID::MENU_BG);
            um.Create(UI_ID::MINIGAME_OVERVIEW);
            um.Create(UI_ID::MINIGAME_MANUAL);
            um.Create(UI_ID::TEXT_OVERVIEW);
            um.Create(UI_ID::TEXT_MANUAL);

            um.Create(UI_ID::PLAYER_READY);

            std::shared_ptr<CGameVideo> gameVideo = dynamic_pointer_cast<CGameVideo>(um.Create(UI_ID::GAME_VIDEO));
            gameVideo->SetGameVideo(m_SelectedGameID);
            um.Create(UI_ID::MINIGAME_TITLE);

            m_RevealUIParent = dynamic_pointer_cast<CSceneUIParent>
                (um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2)));
            if (m_RevealUIParent == nullptr) return;
            m_RevealUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
        }
    }

    if (m_RevealUIParent)
    {
        std::shared_ptr<CPlayerReady> playerReady = dynamic_pointer_cast<CPlayerReady>(um.GetUI(UI_ID::PLAYER_READY));
        if (playerReady == nullptr) return;
        //�~�j�Q�[����񂪒��S�ɂ�����
        if (playerReady->GetReadyFlag() == true && m_RevealUIParent->GetState() == CSceneUIParent::STATE::WAIT && m_GameInfomationFlag == true)
        {
            CSceneManager::GetInstance().PushScene(SCENE_ID::SELECT_SKILL);
            CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);

            m_RevealUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

        }
        if (m_RevealUIParent->GetState() == CSceneUIParent::STATE::FINISH)
        {

            //�Q�[���I���������̃V�[��������
            const float min_height = -vivid::GetWindowHeight() / 2;
            const float max_height = vivid::GetWindowHeight() * 1.5;
            m_RevealUIParent->Delete();
            m_RevealUIParent = nullptr;
            CSceneManager::GetInstance().RemoveScene(SCENE_ID::GAME_ROLL_AND_REVEAL);
        }

    }
}
void CGameRollAndReveal::Draw(void)
{
}

void CGameRollAndReveal::Finalize(void)
{
    IScene::Finalize();

    CCamera::GetInstance().Finalize();
}