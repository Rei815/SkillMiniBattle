#include "select_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

const int CSelectGame::m_games_num = 20;
const float CSelectGame::m_circle_radius = 3500.0f;
CSelectGame::CSelectGame(void)
{

}

CSelectGame::~CSelectGame(void)
{
}

void CSelectGame::Initialize(void)
{

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
    // �w���̃}�C�i�X�����̃f�B���N�V���i�����C�g�ɕύX
    ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.0f));

}

void CSelectGame::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager::GetInstance().Update();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
    {
        int game_id = rand() % (int)GAME_ID::MAX;
        switch (game_id)
        {
        case (int)GAME_ID::FALLGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME); break;
        case (int)GAME_ID::DODGEBALLGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME); break;
        case (int)GAME_ID::DEBUGGAME: CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME); break;
        }
    }
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
#endif

}

void CSelectGame::Draw(void)
{
    CUIManager::GetInstance().Draw();


    vivid::DrawText(20, "�Q�[���I��", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));

}

void CSelectGame::Finalize(void)
{
    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Finalize();


}
