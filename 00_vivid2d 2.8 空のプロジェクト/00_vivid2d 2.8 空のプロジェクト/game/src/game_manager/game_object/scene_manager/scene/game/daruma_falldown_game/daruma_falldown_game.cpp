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
#include "../../../../sound_manager/sound_manager.h"

#include <EffekseerForDXLib.h>


const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(200, 1200.0f, -1500.0f);
const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, -100, 100);

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(1500, 100, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

const float CDaruma_FallDownGame::m_move_speed = 0.3f;

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
	: m_PlayerPosition{ (CVector3(-1500,0,100)) }
	, m_Timer()
	,m_OgreObject(nullptr)
	,m_GimmickOn(false)
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}

void CDaruma_FallDownGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);
	m_RemainCount = CDataManager::GetInstance().GetCurrentPlayer();
	m_CountTime = 180;
	m_Timer.SetUp(m_CountTime);

	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		m_PlayerPosition[i] = CVector3();
	}
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, CVector3(-1500, 100, 100 * i));
		CPlayer* Player = dynamic_cast<CPlayer*>(unit);
		if (Player != nullptr)
			Player->SetActionFlag(false);
	}

	CSkillManager::GetInstance().SetSkill();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		CPlayer* Player = CUnitManager::GetInstance().GetPlayer((UNIT_ID)i);
		Player->MulMoveSpeedRate(m_move_speed);
		Player->SetActionFlag(false);
	}

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	m_DebugText = "だるまさんがころんだシーン";

	//オブジェクトの生成
	m_OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE_OBJECT, Temp);

	

	CUnitManager::GetInstance();
	CObjectManager::GetInstance().Create(OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT, CTransform(CVector3(0,-2500, -100)));

	m_TempFirstDis = FLT_MAX;
	m_TempFirstNum = -1;
}

void CDaruma_FallDownGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

	

}

void CDaruma_FallDownGame::Draw(void)
{
	CGame::Draw();
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1).x),vivid::Vector2(100.0f, 10.0f));
	vivid::DrawText(30, std::to_string(vivid::controller::GetAnalogStickLeft
	(vivid::controller::DEVICE_ID::PLAYER1).y),vivid::Vector2(100.0f, 40.0f));

	vivid::DrawText(30, std::to_string(m_CountTime-(int)m_Timer.GetTimer()), vivid::Vector2(100.0f, 70.0f));

}

void CDaruma_FallDownGame::Finalize(void)
{
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
}

void CDaruma_FallDownGame::Ranking(void)
{
	CUnitManager& um = CUnitManager::GetInstance();

	std::list<CPlayer*>LosePlayerList;

	//一位以外を敗北状態にする
	for (int j = 0; j < CDataManager::GetInstance().GetCurrentPlayer(); j++)
	{
		if (j != m_TempFirstNum)
		{
			um.GetPlayer((UNIT_ID)j)->SetDefeatFlag(true);
			LosePlayerList.push_back(um.GetPlayer((UNIT_ID)j));
		}
	}

	while (!LosePlayerList.empty())
	{
		std::list<CPlayer*>::iterator temp = LosePlayerList.begin();

		for (std::list<CPlayer*>::iterator it = LosePlayerList.begin(); it != LosePlayerList.end(); it++)
		{
			if ((*temp)->GetPosition().x > (*it)->GetPosition().x)
			{
				temp = it;
			}
		}

		CDataManager::GetInstance().AddLastGameRanking((*temp)->GetUnitID());

		LosePlayerList.erase(temp);
	}

	CDataManager::GetInstance().AddLastGameRanking((UNIT_ID)m_TempFirstNum);
	CDataManager::GetInstance().PlayerWin((UNIT_ID)m_TempFirstNum);

	CGame::SetGameState(GAME_STATE::FINISH);
}

void CDaruma_FallDownGame::Start(void)
{
	CGame::Start();
}

void CDaruma_FallDownGame::Play(void)
{
	CGame::Play();
	CUnitManager& um = CUnitManager::GetInstance();
	CDataManager& dm = CDataManager::GetInstance();

	if (!m_GimmickOn)
	{
		CGimmickManager::GetInstance().Create(GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK, m_OgreObject);
		m_GimmickOn = true;
	}

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it;

	m_Timer.Update();

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
					player->SetActionFlag(false);
					player->SetVelocity(CVector3::ZERO);

					CSkill* skill = player->GetSkill();
					if (skill->GetSkillID() == SKILL_ID::RESURRECT_DARUMA && skill->GetState() != SKILL_STATE::COOLDOWN)
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

				if ((player->GetPosition().x >= 1300))
				{
					m_TempFirstNum = i;
					Ranking();
				}
			}
		}
	}

	if (m_Timer.Finished())
	{
		float FirstPosX = -1500;
		for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
		{
			float TempPosX = um.GetPlayer((UNIT_ID)i)->GetPosition().x;
			if (TempPosX >= FirstPosX)
			{
				m_TempFirstNum = i;
				FirstPosX = TempPosX;
			}
		}

		Ranking();
	}
}

void CDaruma_FallDownGame::Finish(void)
{
	CGame::Finish();
}