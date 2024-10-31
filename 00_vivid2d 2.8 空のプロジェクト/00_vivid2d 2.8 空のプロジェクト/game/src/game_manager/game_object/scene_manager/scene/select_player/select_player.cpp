#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CSelectPlayer::CSelectPlayer(void)
{

}

CSelectPlayer::~CSelectPlayer(void)
{
}

void CSelectPlayer::Initialize(void)
{

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();
    CUnitManager::GetInstance().SetCurrentPlayer(1);

}

void CSelectPlayer::Update(void)
{
    CUnitManager& um = CUnitManager::GetInstance();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
        um.SetCurrentPlayer(um.GetCurrentPlayer() - 1);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
        um.SetCurrentPlayer(um.GetCurrentPlayer() + 1);

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }
    CStage::GetInstance().Update();

}

void CSelectPlayer::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

    vivid::DrawText(20, "�v���C���[�Z���N�g", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, std::to_string(CUnitManager::GetInstance().GetCurrentPlayer()), vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    CStage::GetInstance().Finalize();

}
