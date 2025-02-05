#include "select_mode.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../sound_manager/sound_manager.h"

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

    CUIManager::GetInstance().Create(UI_ID::MENU_BG);

    IScene* previousScene = (*CSceneManager::GetInstance().GetList().begin());
    if (previousScene->GetSceneID() == SCENE_ID::SELECTPLAYER)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
    }
    else if (previousScene->GetSceneID() == SCENE_ID::SELECTGAME)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() * 1.5));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
    }

}

void CSelectMode::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTGAME);
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);

        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::BACK) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTPLAYER);
    }

    if (m_SceneUIParent)
    {
        if (m_SceneUIParent->GetState() != CSceneUIParent::STATE::FINISH) return;

        const float min_height = -vivid::GetWindowHeight() / 2;
        const float max_height = vivid::GetWindowHeight() * 1.5;
        if (m_SceneUIParent->GetPosition().y <= min_height || max_height <= m_SceneUIParent->GetPosition().y)
            CSceneManager::GetInstance().PopScene(SCENE_ID::SELECTMODE);
    }

}

void CSelectMode::Draw(void)
{
}

void CSelectMode::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Delete(m_SceneUIParent);

}
