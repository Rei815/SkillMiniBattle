#include "entry.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../unit_manager/unit_manager.h"

CEntry::CEntry(void)
{

}

CEntry::~CEntry(void)
{
}

void CEntry::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();
    CObjectManager& om = CObjectManager::GetInstance();
    CUIManager& um = CUIManager::GetInstance();
    CUIManager::UI_LIST uiList = um.GetList();
    um.Initialize();
    um.Create(UI_ID::TITLE_LOGO);

    CControllerManager& cm = CControllerManager::GetInstance();
    om.Initialize();
    cm.Initialize();

    om.Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT, CTransform());

    m_PlayerControllerList.clear();

}

void CEntry::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CObjectManager& om = CObjectManager::GetInstance();
    CUnitManager& um = CUnitManager::GetInstance();
    om.Update();
    cm.Update();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    CController* controller_2 = cm.GetController(CONTROLLER_ID::TWO);
    CController* controller_3 = cm.GetController(CONTROLLER_ID::THREE);
    CController* controller_4 = cm.GetController(CONTROLLER_ID::FOUR);

    if (controller_1->GetButtonDown(BUTTON_ID::X))
    {

    }
}

void CEntry::Draw(void)
{
}

void CEntry::Finalize(void)
{
    IScene::Finalize();
    CUIManager::GetInstance().Finalize();
}
