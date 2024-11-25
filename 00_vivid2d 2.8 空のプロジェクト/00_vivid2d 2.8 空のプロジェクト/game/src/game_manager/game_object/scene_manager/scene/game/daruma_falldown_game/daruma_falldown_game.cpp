#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../unit_manager/unit/player/player.h"
#include "../../../../unit_manager/unit/unit.h"
#include "../../../../data_manager/data_manager.h"

const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(200, 1200.0f, -1500.0f);

const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, -100, 100);

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(1500, 0, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
	: m_PlayerPosition{ (CVector3()) }
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(void)
{
	m_RemainCount = CDataManager::GetInstance().GetCurrentPlayer();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		m_PlayerPosition[i] = CVector3();
	}
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;

	IUnit iu;
	iu.SetGravity(CVector3(0,0,0));
	
	CGame::Initialize();
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1,CVector3(-1500, 0, 100));

	m_DebugText = "だるまさんがころんだシーン";

	//オブジェクトの生成
	IObject* OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE_OBJECT, Temp);

	CGimmickManager& gm = CGimmickManager::GetInstance();
	gm.Create(GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK, OgreObject);
	CUnitManager::GetInstance();
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

	CUnitManager& um = CUnitManager::GetInstance();
	CDataManager& dm = CDataManager::GetInstance();

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it;

	for (it = objectList.begin();it != objectList.end();it++)
	{
		if ((*it)->GetGimmick()->GetState() == GIMMICK_STATE::PLAY)
		{
			for (int i = 0; i < dm.GetCurrentPlayer(); i++)
			{
				CPlayer* player = um.GetPlayer((UNIT_ID)i);

				if (!player) continue;

				if (player->GetPlayerMoving())
				{
					if (m_PlayerPosition[i] != CVector3::ZERO)
						m_PlayerPosition[i] = player->GetPosition();


					//player->SetDefeatFlag(true);
					player->SetActionFlag(false);
					m_RemainCount--;

					
				}
			}
		}
	}

	if (m_RemainCount == 0)
	{
		/*
		CVector3 temp = CVector3(1, 1, 1);　　　見本
		float length = temp.Length();
		*/

		float m_TempFirstDis = FLT_MAX;
		int   m_TempFirstNum = -1;


		for (int j = 0; j < dm.GetCurrentPlayer();j++)
		{
			float m_PlayerDis = (m_PlayerPosition[j] - m_ogre_position).Length();

			if (m_PlayerDis < m_TempFirstDis)
			{
				m_TempFirstDis = m_PlayerDis;
				m_TempFirstNum = j;
			}

		}

		for (int j = 0; j < dm.GetCurrentPlayer(); j++)
		{
			if (j != m_TempFirstNum)
			{
				um.GetPlayer((UNIT_ID)j)->SetDefeatFlag(true);
			}
		}
	}
}

void CDaruma_FallDownGame::Draw(void)
{
	CGame::Draw();
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1).x),vivid::Vector2(100.0f, 10.0f));
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1).y),vivid::Vector2(100.0f, 40.0f));
}

void CDaruma_FallDownGame::Finalize(void)
{

}
