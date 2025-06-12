#include "game_result.h"
#include "..\..\scene_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\game_object.h"
#include "../../../controller_manager/controller_manager.h"

CGameResult::CGameResult(void)
{

}

CGameResult::~CGameResult(void)
{
}

void CGameResult::Initialize(SCENE_ID scene_id)
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

void CGameResult::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    cm.Update();

    if (cm.GetAnyControllerButtonDown(BUTTON_ID::ANY))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
}

void CGameResult::Draw(void)
{

}

void CGameResult::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
    CDataManager::GetInstance().Finalize();
    CSoundManager::GetInstance().Stop_BGM(m_Sound);
}
