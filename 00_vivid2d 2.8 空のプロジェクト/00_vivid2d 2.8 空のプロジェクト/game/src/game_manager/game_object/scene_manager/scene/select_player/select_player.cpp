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
    CUIManager::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);

}

void CSelectPlayer::Update(void)
{
    CDataManager& dm = CDataManager::GetInstance();
    int currentPlayer = dm.GetCurrentPlayer();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
    {
        currentPlayer--;
        dm.SetCurrentPlayer(currentPlayer);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
    {
        currentPlayer++;
        dm.SetCurrentPlayer(currentPlayer);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }

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

}
