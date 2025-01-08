#include "title.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"

CTitle::CTitle(void)
{

}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(SCENE_ID scene_id)
{
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Specular = GetColorF(0.0f, 1.0f, 0.0f, 0.0f);
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Power = 20.0f;
    SetMaterialParam(Material);

    IScene::Initialize(scene_id);

	m_State = STATE::WAIT;

    CCamera::GetInstance().Initialize();

    CStage::GetInstance().Initialize();
    CUIManager::GetInstance().Initialize();
    CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);
}

void CTitle::Update(void)
{
    switch (m_State)
    {
    case STATE::WAIT:
    {
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
        {
            CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTPLAYER);
        }
    }
    break;
    }
    CStage::GetInstance().Update();
    CStage::GetInstance().Update();
    CUIManager::GetInstance().Update();

}

void CTitle::Draw(void)
{
    CStage::GetInstance().Draw();
    switch (m_State)
    {
    case STATE::WAIT:
    {
        vivid::DrawText(50, "�X�L���~�j�o�g��", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "�X�L���~�j�o�g��") / 2, vivid::WINDOW_HEIGHT / 2));
        //vivid::DrawTexture("data\\Textures\\title.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - 400, vivid::WINDOW_HEIGHT / 2 - 300));

        vivid::DrawText(20, "ENTER�L�[�ŊJ�n,WASD�L�[�ňړ�,�X�y�[�X�L�[�ŃW�����v,Tab�L�[�ňꎞ��~", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    }
    break;
    }
    CUIManager::GetInstance().Draw();

}

void CTitle::Finalize(void)
{
    IScene::Finalize();
    CStage::GetInstance().Finalize();
    CStage::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();

}
