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
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -5000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CUIManager::GetInstance().Initialize();
    for (int i = 0; i < 10; i++)
    {
        CUIManager::GetInstance().Create(UI_ID::RANDOM_GAME);

    }
    // Ｘ軸のマイナス方向のディレクショナルライトに変更
    ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.0f));

}

void CSelectGame::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager::GetInstance().Update();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        int game_id = rand() % (int)GAME_ID::MAX;
        switch (game_id)
        {
        case (int)GAME_ID::FALLGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME); break;
        case (int)GAME_ID::DODGEBALLGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME); break;
        case (int)GAME_ID::DEBUGGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME); break;
        }
    }
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
#endif

}

void CSelectGame::Draw(void)
{
    CUIManager::GetInstance().Draw();

    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "ゲーム選択中", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectGame::Finalize(void)
{
    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Finalize();


}
