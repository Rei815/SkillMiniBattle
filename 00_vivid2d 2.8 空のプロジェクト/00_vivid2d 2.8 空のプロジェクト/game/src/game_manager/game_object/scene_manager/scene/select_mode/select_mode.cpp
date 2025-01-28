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
    CUIManager::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);


}

void CSelectMode::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTGAME);
    }

}

void CSelectMode::Draw(void)
{

    vivid::DrawText(50, "�J�W���A�����[�h", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�J�W���A�����[�h") / 2, vivid::WINDOW_HEIGHT / 2 ));

    vivid::DrawText(20, "�Q�[�����[�h�Z���N�g", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectMode::Finalize(void)
{
    IScene::Finalize();
}
