#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"
#include "../../../sound_manager/sound_manager.h"

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
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() - 1);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() + 1);

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }
    CStage::GetInstance().Update();

}

void CSelectPlayer::Draw(void)
{
    vivid::DrawText(50, "スキルミニバトル", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "スキルミニバトル") / 2, vivid::WINDOW_HEIGHT / 2));

    vivid::DrawText(20, "ADキーで人数の増減, ENTERキーで決定", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "現在" + std::to_string(CDataManager::GetInstance().GetCurrentPlayer()) + "人", vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    IScene::Finalize();

    CStage::GetInstance().Finalize();

}
