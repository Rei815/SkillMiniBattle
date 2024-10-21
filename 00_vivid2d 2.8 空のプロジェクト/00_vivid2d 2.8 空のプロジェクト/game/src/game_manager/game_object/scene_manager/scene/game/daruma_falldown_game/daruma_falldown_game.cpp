#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../unit_manager/unit/player/player.h"

const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(0, 600.0f, -1000.0f);
const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, -0.75f, 1.0f);

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(void)
{
	
	CGame::Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	CCamera::GetInstance().Initialize();
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, 100));

	m_Timer.SetUp(0);
	
	
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

	m_Timer.Update();
}

void CDaruma_FallDownGame::Draw(void)
{
	CGame::Draw();
	vivid::DrawText(20, "ÇæÇÈÇ‹Ç≥ÇÒÇ™Ç±ÇÎÇÒÇæÉVÅ[Éì", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
}

void CDaruma_FallDownGame::Finalize(void)
{
}
