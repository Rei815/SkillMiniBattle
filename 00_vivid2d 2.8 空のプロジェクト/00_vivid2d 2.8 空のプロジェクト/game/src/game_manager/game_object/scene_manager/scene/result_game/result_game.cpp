#include "result_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\game_object.h"

CResultGame::CResultGame(void)
{

}

CResultGame::~CResultGame(void)
{
}

void CResultGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    m_State = STATE::WAIT;

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CResultGame::Update(void)
{
    switch (m_State)
    {
    case STATE::WAIT:
    {
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
        {
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
        }
    }
    break;
    }
    CStage::GetInstance().Update();
    CStage::GetInstance().Update();

}

void CResultGame::Draw(void)
{
    CStage::GetInstance().Draw();
    switch (m_State)
    {
    case STATE::WAIT:
    {
        vivid::DrawText(50, "���U���g", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "���U���g") / 2, vivid::WINDOW_HEIGHT / 2));
    }
    break;
    }

}

void CResultGame::Finalize(void)
{
    IScene::Finalize();
    CDataManager::GetInstance().Finalize();
    CStage::GetInstance().Finalize();

}
