#include "select_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CSelectGame::CSelectGame(void)
{

}

CSelectGame::~CSelectGame(void)
{
}

void CSelectGame::Initialize(void)
{

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CSelectGame::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTGAME);
    }
    CStage::GetInstance().Update();

}

void CSelectGame::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "プレイヤーセレクト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectGame::Finalize(void)
{
    CStage::GetInstance().Finalize();

}
