#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CSelect_Player::CSelect_Player(void)
{

}

CSelect_Player::~CSelect_Player(void)
{
}

void CSelect_Player::Initialize(void)
{
    m_State = STATE::WAIT;

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CSelect_Player::Update(void)
{
    switch (m_State)
    {
    case STATE::WAIT:
    {
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        {
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
        }
    }
    break;
    }
    CStage::GetInstance().Update();
    CStage::GetInstance().Update();

}

void CSelect_Player::Draw(void)
{
    CStage::GetInstance().Draw();
    switch (m_State)
    {
    case STATE::WAIT:
    {
        vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

        vivid::DrawText(20, "プレイヤーセレクト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    }
    break;
    }

}

void CSelect_Player::Finalize(void)
{
    CStage::GetInstance().Finalize();
    CStage::GetInstance().Finalize();

}
