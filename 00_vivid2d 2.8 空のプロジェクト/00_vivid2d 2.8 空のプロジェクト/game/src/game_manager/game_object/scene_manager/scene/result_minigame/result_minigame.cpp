#include "result_minigame.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../animation_manager/animation_manager.h"

const vivid::Vector2  CResultMiniGame::m_OriginKeyPos = vivid::Vector2(20, 500);
const float  CResultMiniGame::m_key_offset = 55.0f;
const float  CResultMiniGame::m_players_key_offset = 6.0f;
CResultMiniGame::CResultMiniGame(void)
{

}

CResultMiniGame::~CResultMiniGame(void)
{
}

void CResultMiniGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    CAnimationManager::GetInstance().Initialize();
    CDataManager& dm = CDataManager::GetInstance();
    vivid::Vector2 offsetPos;
    int firstPlayerID = (int)dm.GetLastGameRanking(0);
    for (int i = 0; i < dm.GetCurrentPlayer(); i++)
    {
        //背景表示
        for (int j = 0; j < dm.GetMaxGameNum(); j++)
        {
            offsetPos = vivid::Vector2(m_key_offset * j + m_key_offset * m_players_key_offset * i, 0);
            CUIManager::GetInstance().Create(UI_ID::KEY_BG, m_OriginKeyPos + offsetPos);
        }
        //これまでの勝利数表示
        //一位のプレイヤー以外は勝利数そのままで表示
        int playerWin = dm.GetPlayerWin(i);
        if (i == firstPlayerID)
            playerWin--;
        for (int j = 0; j < playerWin; j++)
        {
            offsetPos = vivid::Vector2(m_key_offset * j + m_key_offset * m_players_key_offset * i, 0);
            CUIManager::GetInstance().Create(UI_ID::KEY, m_OriginKeyPos + offsetPos);
        }

    }

    //アニメーション付きのカギの表示(一位のみ)
    offsetPos = vivid::Vector2(m_key_offset * (dm.GetPlayerWin(firstPlayerID) - 1) + m_key_offset * m_players_key_offset * firstPlayerID, 0);

    CUI* animationKey = CUIManager::GetInstance().Create(UI_ID::KEY, m_OriginKeyPos + offsetPos);
    CAnimationManager::GetInstance().Create(ANIMATION_ID::KEY_SCALE, animationKey);
}

void CResultMiniGame::Update(void)
{
    CAnimationManager::GetInstance().Update();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::X))
    {
        CDataManager& dm = CDataManager::GetInstance();
        SCENE_ID sceneID = SCENE_ID::SELECTGAME;
        for (int i = 0; i < dm.GetCurrentPlayer(); i++)
        {
            if (dm.GetPlayerWin(i) == dm.GetMaxGameNum())
            {
                sceneID = SCENE_ID::RESULT_GAME;
                break;
            }
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
    CAnimationManager::GetInstance().Finalize();
    IScene::Finalize();


}
