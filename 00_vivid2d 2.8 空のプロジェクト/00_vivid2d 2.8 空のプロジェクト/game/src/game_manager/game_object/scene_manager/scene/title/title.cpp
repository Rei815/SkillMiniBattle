#include "title.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

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

    CUIManager::GetInstance().Initialize();
    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);
    CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG);
    m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT);
    m_SceneUIParent->SetState(CSceneUIParent::STATE::SCENE_IN);
}

void CTitle::Update(void)
{
    unsigned int alpha = vivid::alpha::GetAlpha(m_Color);
    if (alpha == 255u || alpha == 0u)
        m_FadeSpeed = -m_FadeSpeed;

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        m_Color = 0xff000000;

        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTPLAYER);
    }
    CUIManager::GetInstance().Update();
    m_Color = vivid::alpha::AdjustAlpha(m_Color, m_FadeSpeed);

    if (!m_SceneUIParent) return;

    if (m_SceneUIParent->GetPosition().y == vivid::GetWindowHeight() / 2)
        CSceneManager::GetInstance().PopScene(SCENE_ID::TITLE);
}

void CTitle::Draw(void)
{
    CUIManager::GetInstance().Draw();
    vivid::Vector2 position = vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�{�^���������ĂˁI") / 2, vivid::WINDOW_HEIGHT / 2 + 100);
    vivid::DrawText(50, "�{�^���������ĂˁI", position, m_Color);
    //vivid::DrawText(20, "ENTER�L�[�ŊJ�n,WASD�L�[�ňړ�,�X�y�[�X�L�[�ŃW�����v,Tab�L�[�ňꎞ��~", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CTitle::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();

}
