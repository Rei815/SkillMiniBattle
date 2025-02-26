#include "title.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"

const int CTitle::m_fade_speed = 2;
CTitle::CTitle(void)
    : m_Color(0xff000000)
    , m_FadeSpeed(m_fade_speed)
{

}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(SCENE_ID scene_id)
{
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Specular = GetColorF(0.0f, 1.0f, 0.0f, 0.0f);
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Power = 20.0f;
    SetMaterialParam(Material);

    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();
    CUIManager& um = CUIManager::GetInstance();
    CUIManager::UI_LIST uiList = um.GetList();
    CSoundManager::GetInstance().Play_BGM(BGM_ID::READY_BGM, true);

    if (uiList.size() == 0)
    {
        um.Initialize();
        um.Create(UI_ID::TITLE_LOGO);
    }
    um.Create(UI_ID::TITLE_BUTTON);

    IScene* previousScene = (*CSceneManager::GetInstance().GetList().begin());

    //���̃V�[�������ꂽ�ۂɃ^�C�g������Ȃ̂��Z���N�g���[�h�V�[��������ꂽ���œ�����ς���
    //if (previousScene->GetSceneID() == SCENE_ID::SELECTPLAYER)
    //{
    //    m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() * 1.5));
    //    m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
    //}
    /*else */if (previousScene->GetSceneID() == SCENE_ID::TITLE)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() / 2));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::WAIT);
    }
    CControllerManager::GetInstance().Initialize();
}

void CTitle::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    cm.Update();

    unsigned int alpha = vivid::alpha::GetAlpha(m_Color);
    if (alpha == 255u || alpha == 0u)
        m_FadeSpeed = -m_FadeSpeed;

    CSceneManager& sm = CSceneManager::GetInstance();
    if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) || cm.GetAnyControllerButtonDown(BUTTON_ID::B)) && sm.GetList().size() == 1)
    {
        m_Color = 0xff000000;
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);

        //m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::ENTRY);

    }

    m_Color = vivid::alpha::AdjustAlpha(m_Color, m_FadeSpeed);
    if (m_SceneUIParent)
    {
        if (m_SceneUIParent->GetState() != CSceneUIParent::STATE::FINISH) return;

        const float min_height = -vivid::GetWindowHeight() / 2;
        const float max_height = vivid::GetWindowHeight() * 1.5;
        if (m_SceneUIParent->GetPosition().y <= min_height || max_height <= m_SceneUIParent->GetPosition().y)
            CSceneManager::GetInstance().PopScene(SCENE_ID::TITLE);
    }

}

void CTitle::Draw(void)
{
    vivid::Vector2 position = vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�{�^���������ĂˁI") / 2, vivid::WINDOW_HEIGHT / 2 + 100);
    vivid::DrawText(50, "�{�^���������ĂˁI", position, m_Color);

}

void CTitle::Finalize(void)
{
    IScene::Finalize();
    //CUIManager::GetInstance().Delete(m_SceneUIParent);
    CUIManager::GetInstance().Finalize();
}
