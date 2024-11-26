#include "debug_game.h"
#include "../../../../unit_manager/unit_manager.h"

CDebugGame::CDebugGame(void)
{
}

CDebugGame::~CDebugGame(void)
{
}

void CDebugGame::Initialize(SCENE_ID scene_id)
{

	CGame::Initialize(scene_id);
	m_DebugText = "デバッグゲーム";
}
