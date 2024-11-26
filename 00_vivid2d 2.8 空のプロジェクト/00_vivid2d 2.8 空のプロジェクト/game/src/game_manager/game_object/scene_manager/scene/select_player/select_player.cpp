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
}

void CSelectPlayer::Update(void)
{
    CDataManager& dm = CDataManager::GetInstance();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() - 1);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() + 1);

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }
    CStage::GetInstance().Update();

}

void CSelectPlayer::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "プレイヤーセレクト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, std::to_string(CDataManager::GetInstance().GetCurrentPlayer()), vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    IScene::Finalize();

    CStage::GetInstance().Finalize();

}
