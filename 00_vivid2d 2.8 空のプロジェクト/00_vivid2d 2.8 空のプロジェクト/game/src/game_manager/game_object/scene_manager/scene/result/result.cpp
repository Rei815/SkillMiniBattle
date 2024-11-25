#include "result.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CResult::CResult(void)
{

}

CResult::~CResult(void)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CResult::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
    CStage::GetInstance().Update();
    CStage::GetInstance().Update();

}

void CResult::Draw(void)
{
    CStage::GetInstance().Draw();
    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "ƒŠƒUƒ‹ƒg", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CResult::Finalize(void)
{
    IScene::Finalize();

    CStage::GetInstance().Finalize();

}
