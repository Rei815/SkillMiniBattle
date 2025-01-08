#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../unit_manager/unit/player/player.h"
#include "../../../../unit_manager/unit/unit.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"


const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(200, 1200.0f, -1500.0f);
const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, -100, 100);

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(1500, 100, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

const float CDaruma_FallDownGame::m_move_speed = 0.3f;

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
	: m_PlayerPosition{ (CVector3(-1500,0,100)) }
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);
	m_RemainCount = CDataManager::GetInstance().GetCurrentPlayer();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		m_PlayerPosition[i] = CVector3();
	}
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		CUnitManager::GetInstance().Create((UNIT_ID)i, CVector3(-1500, 100, 100 * i));
	}

	CSkillManager::GetInstance().SetSkill();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		CUnitManager::GetInstance().GetPlayer((UNIT_ID)i)->MulMoveSpeedRate(m_move_speed);
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
	CObjectManager::GetInstance().Create(OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT, CTransform(CVector3(0,-2500, -100)));

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
		
		for (int i = 0; i < dm.GetCurrentPlayer(); i++)
		{
			player = um.GetPlayer((UNIT_ID)i);

			if (!player) continue;
			

			if (gimmick->GetState() == GIMMICK_STATE::PLAY && player->GetInvincibleFlag() == false)
			{
				if (player->GetPlayerMoving())
				{
					if (m_PlayerPosition[i] != CVector3::ZERO)
						m_PlayerPosition[i] = player->GetPosition();
					
					player->SetActionFlag(false);
					player->SetVelocity(CVector3::ZERO);

					CSkill* skill = player->GetSkill();
					if (skill->GetSkillCategory() == SKILL_CATEGORY::RESURRECT && skill->GetState() != SKILL_STATE::COOLDOWN)
						skill->SetState(SKILL_STATE::ACTIVE);
					else
						player->SetPosition(CVector3(-1500, 100, 100 * i));

				}
			}
			else
			{
				if (player->GetPosition().x <= -1500)
				{
					player->SetActionFlag(true);
				}

				if ((player->GetPosition().x >= 1400))
				{
					m_TempFirstNum = i;
					Ranking();
				}
			}
		}
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
	for (int j = 0; j < CDataManager::GetInstance().GetCurrentPlayer(); j++)
	{
		if (j != m_TempFirstNum)
		{
			um.GetPlayer((UNIT_ID)j)->SetDefeatFlag(true);
		}
	}
	CGame::SetGameState(GAME_STATE::FINISH);
}