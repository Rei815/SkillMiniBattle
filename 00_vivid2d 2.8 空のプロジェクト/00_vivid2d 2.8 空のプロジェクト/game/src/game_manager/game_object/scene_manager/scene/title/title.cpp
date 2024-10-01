#include "title.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CTitle::CTitle(void)
{

}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(void)
{
	m_State = STATE::WAIT;

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();


}

void CTitle::Update(void)
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

void CTitle::Draw(void)
{
    CStage::GetInstance().Draw();
    switch (m_State)
    {
    case STATE::WAIT:
    {
        vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

        vivid::DrawText(20, "Z�ŊJ�n,���N���b�N�Ŏˌ��܂��͌���,AD�L�[�ňړ�,�X�y�[�X�L�[�ŃW�����v,Tab�L�[�ňꎞ��~", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    }
    break;
    }

}

void CTitle::Finalize(void)
{
    CStage::GetInstance().Finalize();
    CStage::GetInstance().Finalize();

}
