#include "select_mode.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CSelectMode::CSelectMode(void)
{

}

CSelectMode::~CSelectMode(void)
{
}

void CSelectMode::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG);
    IScene* scene = (*CSceneManager::GetInstance().GetList().begin());
    if (scene->GetSceneID() == SCENE_ID::SELECTPLAYER)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
    }
    else if (scene->GetSceneID() == SCENE_ID::SELECTGAME)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() * 1.5));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
    }

}

void CSelectMode::Update(void)
{
    CUIManager::GetInstance().Update();

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTGAME);
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::BACK) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTPLAYER);
    }

    if (!m_SceneUIParent || m_SceneUIParent->GetState() != CSceneUIParent::STATE::WAIT) return;

    const float min_height = -vivid::GetWindowHeight() / 2;
    const float max_height = vivid::GetWindowHeight() * 1.5;
    if (m_SceneUIParent->GetPosition().y <= min_height || max_height <= m_SceneUIParent->GetPosition().y)
        CSceneManager::GetInstance().PopScene(SCENE_ID::SELECTMODE);

}

void CSelectMode::Draw(void)
{
    CUIManager::GetInstance().Draw();
    vivid::DrawText(50, "カジュアルモード", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "カジュアルモード") / 2, vivid::WINDOW_HEIGHT / 2 ));

    vivid::DrawText(20, "ゲームモードセレクト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectMode::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Delete(m_SceneUIParent);

}
