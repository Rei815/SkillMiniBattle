#include "debug_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera/camera.h"

CDebugGame::CDebugGame(void)
{
}

CDebugGame::~CDebugGame(void)
{
}

void CDebugGame::Initialize(SCENE_ID scene_id)
{

	CGame::Initialize(scene_id);
	CCamera::GetInstance().Initialize();
	CUIManager::GetInstance().Create(UI_ID::TOPIC_SHUTTER,vivid::Vector2(0,50));
	m_DebugText = "デバッグゲーム";
}

void CDebugGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

}

void CDebugGame::Draw(void)
{
	CGame::Draw();
	
}
