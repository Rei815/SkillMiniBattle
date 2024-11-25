#include "select_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"

const int CSelectGame::m_games_num = 20;
const float CSelectGame::m_circle_radius = 3500.0f;
CSelectGame::CSelectGame(void)
{

}

CSelectGame::~CSelectGame(void)
{
}

void CSelectGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -5000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CUIManager::GetInstance().Initialize();
    for (int i = 0; i < m_games_num; i++)
    {
        CTransform transform;
        const float rad = i / (float)m_games_num * DX_TWO_PI;
        const float _x = m_circle_radius * sin(rad);
        const float _z = m_circle_radius * cos(rad);
        transform.rotation.y = DEG_TO_RAD( i * (360.0f / (float)m_games_num));
        transform.position.y = 500.0f;
        transform.position.x = 0.0f;// _x;
        transform.position.z = -m_circle_radius;//_z;
        CUIManager::GetInstance().Create(UI_ID::RANDOM_GAME, transform);
    }
    // Ｘ軸のマイナス方向のディレクショナルライトに変更
    ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.0f));

}

void CSelectGame::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager::GetInstance().Update();
    CDataManager& dm = CDataManager::GetInstance();
    GAME_ID _gameID = GAME_ID::MAX;
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        int game_id = rand() % (int)GAME_ID::MAX;
        _gameID = (GAME_ID)game_id;
        switch (game_id)
        {
        case (int)GAME_ID::FALL_GAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME); break;
        case (int)GAME_ID::DODGE_BALL_GAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME); break;
        case (int)GAME_ID::DEBUG_GAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME); break;
        }
    }
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
    {
        _gameID = GAME_ID::DARUMA_FALL_DOWN_GAME;
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
    {
        _gameID = GAME_ID::FALL_GAME;
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
    {
        _gameID = GAME_ID::DODGE_BALL_GAME;
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
    }
#endif
        dm.SetGameID(_gameID);

}

void CSelectGame::Draw(void)
{
    CUIManager::GetInstance().Draw();


    vivid::DrawText(20, "ゲーム選択中", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectGame::Finalize(void)
{
    IScene::Finalize();

    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Finalize();


}
