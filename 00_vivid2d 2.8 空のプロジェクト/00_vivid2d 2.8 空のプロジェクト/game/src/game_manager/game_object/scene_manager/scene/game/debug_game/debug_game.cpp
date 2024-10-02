#include "debug_game.h"

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
