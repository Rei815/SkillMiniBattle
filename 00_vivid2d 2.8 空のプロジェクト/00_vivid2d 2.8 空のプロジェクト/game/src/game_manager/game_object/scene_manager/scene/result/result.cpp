#include "result.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../ui_manager/ui_manager.h"

CResult::CResult(void)
{

}

CResult::~CResult(void)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CUIManager::GetInstance().Create(UI_ID::FINISH_GAME_BG);
}

void CResult::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::X))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
}

void CResult::Draw(void)
{

    vivid::DrawText(20, "���U���g", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "X�Ń^�C�g����", vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, 0));

}

void CResult::Finalize(void)
{
    IScene::Finalize();


}
