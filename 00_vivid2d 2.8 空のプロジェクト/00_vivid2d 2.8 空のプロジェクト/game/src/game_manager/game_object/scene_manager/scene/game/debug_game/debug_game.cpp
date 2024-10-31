#include "debug_game.h"
#include "../../../../unit_manager/unit_manager.h"

CDebugGame::CDebugGame(void)
{
}

CDebugGame::~CDebugGame(void)
{
}

void CDebugGame::Initialize(void)
{

	CGame::Initialize();
	m_DebugText = "デバッグゲーム";
}
