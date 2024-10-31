#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../unit_manager/unit/player/player.h"

const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(0, 600.0f, -1000.0f);
const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, 0, 100);

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(0, 0, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(void)
{
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;

	
	CGame::Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	CCamera::GetInstance().Initialize();
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, 100));


	m_DebugText = "だるまさんがころんだシーン";
	
	//オブジェクトの生
	IObject* OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE_OBJECT, Temp);


	CGimmickManager& gm = CGimmickManager::GetInstance();
	gm.Create(GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK, OgreObject);
	
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

}

void CDaruma_FallDownGame::Draw(void)
{
	CGame::Draw();
}

void CDaruma_FallDownGame::Finalize(void)
{
}
