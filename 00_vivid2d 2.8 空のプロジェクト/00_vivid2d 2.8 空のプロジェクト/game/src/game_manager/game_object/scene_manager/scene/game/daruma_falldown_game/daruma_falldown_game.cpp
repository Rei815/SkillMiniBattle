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

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(1500, 100, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
	: m_PlayerPosition{ (CVector3(-1500,0,100)) }
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(void)
{
	CGame::Initialize();
	m_RemainCount = CUnitManager::GetInstance().GetCurrentPlayer();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		m_PlayerPosition[i] = CVector3();
	}
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;



	for (int i = 0; i < CUnitManager::GetInstance().GetCurrentPlayer(); i++)
	{
		CUnitManager::GetInstance().Create((UNIT_ID)i, CVector3(-1500, 0, 100 * i));
	}

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	m_DebugText = "だるまさんがころんだシーン";

	//オブジェクトの生成
	IObject* OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE_OBJECT, Temp);

	CGimmickManager& gm = CGimmickManager::GetInstance();
	gm.Create(GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK, OgreObject);
	CUnitManager::GetInstance();
	CObjectManager::GetInstance().Create(OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT, CTransform(CVector3(0, -2500, -100)));

	m_TempFirstDis = FLT_MAX;
	m_TempFirstNum = -1;
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

	CUnitManager& um = CUnitManager::GetInstance();
	CDataManager& dm = CDataManager::GetInstance();

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it;

	for (it = objectList.begin(); it != objectList.end(); it++)
	{
		CGimmick* gimmick = (*it)->GetGimmick();
		CPlayer* player;

		if (!gimmick) continue;

		//鬼が振り返ってる時の処理
		if (gimmick->GetState() == GIMMICK_STATE::PLAY)
		{
			for (int i = 0; i < dm.GetCurrentPlayer(); i++)
			{
				player = um.GetPlayer((UNIT_ID)i);

				if (!player) continue;

				if (player->GetPlayerMoving())
				{
					if (m_PlayerPosition[i] != CVector3::ZERO)
						m_PlayerPosition[i] = player->GetPosition();

					player->SetActionFlag(false);
					m_RemainCount--;
				}
			}
		}

		if (gimmick->GetState() != GIMMICK_STATE::PLAY)
		{
			for (int i = 0; i < um.GetCurrentPlayer(); i++)
			{
				player = um.GetPlayer((UNIT_ID)i);
				if ((player->GetPosition().x >= 1400))
				{
					m_TempFirstNum = i;
					Ranking();
				}
			}

		}
		
	}

	//プレイヤーの生き残りが0人になったら
	if (m_RemainCount == 0)
	{
		for (int j = 0; j < CUnitManager::GetInstance().GetCurrentPlayer();j++)
		{
			float m_PlayerDis = (m_PlayerPosition[j] - m_ogre_position).Length();

			if (m_PlayerDis < m_TempFirstDis)
			{
				m_TempFirstDis = m_PlayerDis;
				m_TempFirstNum = j;
			}
		}
		Ranking();
	}
}

void CDaruma_FallDownGame::Draw(void)
{
	CGame::Draw();
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1).x),vivid::Vector2(100.0f, 10.0f));
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft
	(vivid::controller::DEVICE_ID::PLAYER1).y),vivid::Vector2(100.0f, 40.0f));

	
}

void CDaruma_FallDownGame::Finalize(void)
{

}

void CDaruma_FallDownGame::Ranking(void)
{
	CUnitManager& um = CUnitManager::GetInstance();
	//一位以外を敗北状態にする
	for (int j = 0; j < CUnitManager::GetInstance().GetCurrentPlayer(); j++)
	{
		if (j != m_TempFirstNum)
		{
			um.GetPlayer((UNIT_ID)j)->SetDefeatFlag(true);
		}
	}
}