#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"

CSelectPlayer::CSelectPlayer(void)
{

}

CSelectPlayer::~CSelectPlayer(void)
{
}

void CSelectPlayer::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();

    CDataManager::GetInstance().Initialize();
    CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG, vivid::Vector2(0,vivid::GetWindowHeight() - 300));
    IScene* scene = (*CSceneManager::GetInstance().GetList().begin());
    if (scene->GetSceneID() == SCENE_ID::TITLE)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
    }
    else if(scene->GetSceneID() == SCENE_ID::SELECTMODE)
    {
        m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() * 1.5));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
    }

}

void CSelectPlayer::Update(void)
{
    CUIManager::GetInstance().Update();
    CDataManager& dm = CDataManager::GetInstance();
    int currentPlayer = dm.GetCurrentPlayer();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
    {
        currentPlayer--;
        dm.SetCurrentPlayer(currentPlayer);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
    {
        currentPlayer++;
        dm.SetCurrentPlayer(currentPlayer);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::BACK) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
        CSceneManager::GetInstance().PushScene(SCENE_ID::TITLE);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
    {
        CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTMODE);
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
    }

    if (!m_SceneUIParent || m_SceneUIParent->GetState() != CSceneUIParent::STATE::WAIT) return;

    const float min_height = -vivid::GetWindowHeight() / 2;
    const float max_height = vivid::GetWindowHeight() * 1.5;
    if (m_SceneUIParent->GetPosition().y <= min_height || max_height <= m_SceneUIParent->GetPosition().y)
        CSceneManager::GetInstance().PopScene(SCENE_ID::SELECTPLAYER);


}

void CSelectPlayer::Draw(void)
{
    CUIManager::GetInstance().Draw();
    vivid::DrawText(50, "スキルミニバトル", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "スキルミニバトル") / 2, vivid::WINDOW_HEIGHT / 2));

    vivid::DrawText(20, "ADキーで人数の増減, ENTERキーで決定", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "現在" + std::to_string(CDataManager::GetInstance().GetCurrentPlayer()) + "人", vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Delete(m_SceneUIParent);
}
