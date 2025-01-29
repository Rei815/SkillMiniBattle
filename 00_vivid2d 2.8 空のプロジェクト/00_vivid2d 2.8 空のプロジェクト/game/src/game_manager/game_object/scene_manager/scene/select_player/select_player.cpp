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
    //CUIManager::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);
    CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC_BG);
    CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT);

}

void CSelectPlayer::Update(void)
{
    CUIManager::GetInstance().Update();
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
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }

    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    //{
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    //}

}

void CSelectPlayer::Draw(void)
{
    CUIManager::GetInstance().Draw();
    vivid::DrawText(50, "�X�L���~�j�o�g��", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�X�L���~�j�o�g��") / 2, vivid::WINDOW_HEIGHT / 2));

    vivid::DrawText(20, "AD�L�[�Ől���̑���, ENTER�L�[�Ō���", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "����" + std::to_string(CDataManager::GetInstance().GetCurrentPlayer()) + "�l", vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    IScene::Finalize();

}
