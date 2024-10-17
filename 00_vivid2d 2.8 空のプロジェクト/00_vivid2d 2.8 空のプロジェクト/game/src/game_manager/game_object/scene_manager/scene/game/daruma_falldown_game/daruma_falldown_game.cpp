#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"


CDaruma_FallDownGame::CDaruma_FallDownGame(void)
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(void)
{
	CGame::Initialize();
	CCamera::GetInstance().Initialize();
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, 100));
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();
}

void CDaruma_FallDownGame::Draw(void)
{
	vivid::DrawText(20, "ÇæÇÈÇ‹Ç≥ÇÒÇ™Ç±ÇÎÇÒÇæÉVÅ[Éì", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
}

void CDaruma_FallDownGame::Finalize(void)
{
}
