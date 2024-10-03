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
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, -1000));
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, -1000));
}
