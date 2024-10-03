#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"

CFallGame::CFallGame(void)
{
}

CFallGame::~CFallGame(void)
{
}

void CFallGame::Initialize(void)
{
	CGame::Initialize();

	m_DebugText = "フォールゲーム";
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, -1000));
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, -1000));
}
