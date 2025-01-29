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

    CStage::GetInstance().Initialize();

    CDataManager::GetInstance().Initialize();
    //CUIManager::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);
    CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG);
    CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT);

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

    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    //{
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    //}

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

}
