#include "result_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\game_object.h"
#include "../../../controller_manager/controller_manager.h"

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
    m_Sound = BGM_ID::RESULT_BGM;

    CSoundManager::GetInstance().Play_BGM(m_Sound, true);

    CCamera::GetInstance().Initialize();
    CUIManager& um = CUIManager::GetInstance();
    um.Create(UI_ID::CONCENTRATION_LINE);
    um.Create(UI_ID::RESULT_WINNER);
    um.Create(UI_ID::TITLE_BUTTON);
}

void CResultGame::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    cm.Update();

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) || controller_1->GetButtonDown(BUTTON_ID::ALL))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
}

void CResultGame::Draw(void)
{

}

void CResultGame::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
    CDataManager::GetInstance().Finalize();
    CSoundManager::GetInstance().Stop_BGM(m_Sound);
}
