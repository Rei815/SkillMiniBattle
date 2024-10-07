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
        int game_id = rand() % (int)GAME_ID::MAX;
        switch (game_id)
        {
        case (int)GAME_ID::FALLGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME); break;
        case (int)GAME_ID::DEBUGGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME); break;
        }
        
    }
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
#endif
    CStage::GetInstance().Update();

}

void CSelectGame::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "ÉQÅ[ÉÄëIëíÜ", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectGame::Finalize(void)
{
    CStage::GetInstance().Finalize();

}
