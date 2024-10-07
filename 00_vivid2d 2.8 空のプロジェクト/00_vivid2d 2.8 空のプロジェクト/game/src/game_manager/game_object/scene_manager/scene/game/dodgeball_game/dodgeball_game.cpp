#include "dodgeball_game.h"
#include "../../../../unit_manager/unit_manager.h"

CDodgeBallGame::CDodgeBallGame(void)
{
}

CDodgeBallGame::~CDodgeBallGame(void)
{
}

void CDodgeBallGame::Initialize(void)
{
	CGame::Initialize();

	m_DebugText = "ドッジボールゲーム";
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, -1000));
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(0, 0, -500));
}
