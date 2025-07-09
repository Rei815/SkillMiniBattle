#include "title.h"
#include "..\..\scene_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../ui_manager/ui_manager.h"

CTitle::CTitle(void)
{

}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(SCENE_ID scene_id)
{

    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();
    CDataManager::GetInstance().Initialize();
    CObjectManager::GetInstance().Initialize();
    CUIManager& um = CUIManager::GetInstance();
    CUIManager::UI_LIST uiList = um.GetList();
    CSoundManager::GetInstance().Play_BGM(BGM_ID::READY_BGM, true);

    um.Initialize();
    um.Create(UI_ID::TITLE_LOGO);
    um.Create(UI_ID::TITLE_BUTTON);

    CControllerManager::GetInstance().Initialize();
}

void CTitle::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    cm.Update();

    CSceneManager& sm = CSceneManager::GetInstance();
    if (cm.GetAnyControllerButtonDown(BUTTON_ID::B))
    {
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::ENTRY);

    }
}

void CTitle::Draw(void)
{
}

void CTitle::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
}
