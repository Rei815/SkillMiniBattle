#include "result_minigame.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../data_manager/data_manager.h"

const vivid::Vector2  CResultMiniGame::m_OriginKeyPos = vivid::Vector2(0, 0);
const float  CResultMiniGame::m_KeyOffset = 100.0f;
CResultMiniGame::CResultMiniGame(void)
{

}

CResultMiniGame::~CResultMiniGame(void)
{
}

void CResultMiniGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    CUIManager::GetInstance().Create(UI_ID::FINISH_GAME_BG);

    //これまでの勝利数表示
    for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
    {
        for (int j = 0; j < CDataManager::GetInstance().GetMaxGameNum(); j++)
        {
            CUIManager::GetInstance().Create(UI_ID::KEY_BG, m_OriginKeyPos + vivid::Vector2(m_KeyOffset * j, -m_KeyOffset * i));
        }
        for (int j = 0; j < CDataManager::GetInstance().GetPlayerWin(i) - 1; j++)
        {
            CUIManager::GetInstance().Create(UI_ID::KEY, m_OriginKeyPos + vivid::Vector2(m_KeyOffset * j, -m_KeyOffset * i));
        }
    }

    CUI* animationKey = CUIManager::GetInstance().Create(UI_ID::KEY);

}

void CResultMiniGame::Update(void)
{
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::X))
    {
        CDataManager& dm = CDataManager::GetInstance();
        SCENE_ID sceneID = SCENE_ID::RESULT_GAME;
        for (int i = 0; i < dm.GetCurrentPlayer(); i++)
        {
            if (dm.GetPlayerWin(i) != dm.GetMaxGameNum())
                sceneID = SCENE_ID::SELECTGAME;
        }
        CSceneManager::GetInstance().ChangeScene(sceneID);
    }
}

void CResultMiniGame::Draw(void)
{
    
    vivid::DrawText(20, "ミニゲームリザルト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "Xで次へ", vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, 0));

}

void CResultMiniGame::Finalize(void)
{
    IScene::Finalize();


}
