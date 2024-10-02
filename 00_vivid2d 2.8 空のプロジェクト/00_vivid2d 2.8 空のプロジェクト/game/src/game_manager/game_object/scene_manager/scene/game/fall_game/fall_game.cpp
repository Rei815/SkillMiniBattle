#include "fall_game.h"

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
}
