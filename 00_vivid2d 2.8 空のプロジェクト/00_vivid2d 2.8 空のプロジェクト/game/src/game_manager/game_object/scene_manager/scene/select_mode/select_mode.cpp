#include "select_mode.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CSelect_Mode::CSelect_Mode(void)
{

}

CSelect_Mode::~CSelect_Mode(void)
{
}

void CSelect_Mode::Initialize(void)
{
    m_State = STATE::WAIT;

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CSelect_Mode::Update(void)
{
    switch (m_State)
    {
    case STATE::WAIT:
    {
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
        {
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTPLAYER);
        }
    }
    break;
    }
    CStage::GetInstance().Update();
    CStage::GetInstance().Update();

}

void CSelect_Mode::Draw(void)
{
    CStage::GetInstance().Draw();
    switch (m_State)
    {
    case STATE::WAIT:
    {
        vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

        vivid::DrawText(50, "カジュアル", vivid::Vector2(vivid::WINDOW_WIDTH / 2, vivid::WINDOW_HEIGHT / 2));

        vivid::DrawText(20, "ゲームモードセレクト", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    }
    break;
    }

}

void CSelect_Mode::Finalize(void)
{
    CStage::GetInstance().Finalize();
    CStage::GetInstance().Finalize();

}
