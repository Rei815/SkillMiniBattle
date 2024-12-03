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
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() - 1);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() + 1);

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }
    CStage::GetInstance().Update();

}

void CSelectPlayer::Draw(void)
{
    vivid::DrawText(50, "�X�L���~�j�o�g��", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�X�L���~�j�o�g��") / 2, vivid::WINDOW_HEIGHT / 2));

    vivid::DrawText(20, "AD�L�[�Ől���̑���, ENTER�L�[�Ō���", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "����" + std::to_string(CDataManager::GetInstance().GetCurrentPlayer()) + "�l", vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    IScene::Finalize();

    CStage::GetInstance().Finalize();

}
