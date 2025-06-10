#include "daruma_falldown_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../unit_manager/unit/player/player.h"
#include "../../../../unit_manager/unit/unit.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"

#include <EffekseerForDXLib.h>


const CVector3	CDaruma_FallDownGame::m_camera_position = CVector3(-500,700.0f, -1000.0f);
const CVector3	CDaruma_FallDownGame::m_camera_direction = CVector3(0, -100, 100);

const CVector3	CDaruma_FallDownGame::m_ogre_position = CVector3(500, 0, 0);
const CVector3	CDaruma_FallDownGame::m_ogre_rotation = CVector3(0, 0, 0);

const float CDaruma_FallDownGame::m_move_speed = 0.3f;

const CVector3 CDaruma_FallDownGame::m_player_default_forward = CVector3(1.0f, 0.0f, 0.0f);
const CVector3 CDaruma_FallDownGame::m_goal_position = CVector3(300.0f, 0.0f, 0.0f);

const CVector3 CDaruma_FallDownGame::m_reset_speed = CVector3(2.0f, 0.0f, 0.0f);

CDaruma_FallDownGame::CDaruma_FallDownGame(void)
	: m_PlayerPosition{ (CVector3(-1500,0,100)) }
	, m_Timer()
	, m_OgreObject(nullptr)
	, m_GimmickOn(false)
	, m_StartPosition{ (CVector3(0,0,0)) }
	, m_MovePlayer()
	, m_TextureColor{(0x00000000)}
	, m_TextPosition(vivid::Vector2(0,0))
{
}

CDaruma_FallDownGame::~CDaruma_FallDownGame(void)
{
}
void CDaruma_FallDownGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);
	m_RemainCount = CDataManager::GetInstance().GetCurrentJoinPlayer();
	m_CountTime = 90;
	m_Timer.SetUp(m_CountTime);

	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		m_PlayerPosition[i] = CVector3();
	}
	CTransform Temp;
	Temp.position = m_ogre_position;
	Temp.rotation = m_ogre_rotation;

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		std::shared_ptr<IUnit> unit = CUnitManager::GetInstance().Create((UNIT_ID)i, CVector3(-1500, 100, 100 * i));
		m_StartPosition[i] = unit->GetPosition();
		std::shared_ptr<CPlayer> Player = dynamic_pointer_cast<CPlayer>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
	}

	CSkillManager::GetInstance().SetSkill();

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		std::shared_ptr<CPlayer> Player = CUnitManager::GetInstance().GetPlayer((UNIT_ID)i);
		Player->MulMoveSpeedRate(m_move_speed);
		Player->SetActionFlag(false);
	}

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//�I�u�W�F�N�g�̐���
	m_OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE_OBJECT, Temp);

	

	CUnitManager::GetInstance();
	CObjectManager::GetInstance().Create(OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT, CTransform(CVector3(0,-1000, -100)));

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

	vivid::DrawTexture("data\\Textures\\1P_ogre_saw.png", vivid::Vector2(1000, 0), m_TextureColor[0]);
	vivid::DrawTexture("data\\Textures\\2P_ogre_saw.png", vivid::Vector2(1050, 0), m_TextureColor[1]);
	vivid::DrawTexture("data\\Textures\\3P_ogre_saw.png", vivid::Vector2(1100, 0), m_TextureColor[2]);
	vivid::DrawTexture("data\\Textures\\4P_ogre_saw.png", vivid::Vector2(1150, 0), m_TextureColor[3]);
}

void CDaruma_FallDownGame::Finalize(void)
{
	CGame::Finalize();
	CCamera::GetInstance().Finalize();
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
}

void CDaruma_FallDownGame::Ranking(void)
{
	CUnitManager& um = CUnitManager::GetInstance();

	std::list<std::shared_ptr<CPlayer>> LosePlayerList;

	//��ʈȊO��s�k��Ԃɂ���
	for (int j = 0; j < CDataManager::GetInstance().GetCurrentJoinPlayer(); j++)
	{
		if (j != m_TempFirstNum)
		{
			um.GetPlayer((UNIT_ID)j)->SetDefeatFlag(true);
			LosePlayerList.emplace_back(um.GetPlayer((UNIT_ID)j));
		}
	}

	while (!LosePlayerList.empty())
	{
		std::list<std::shared_ptr<CPlayer>>::iterator temp = LosePlayerList.begin();

		for (std::list<std::shared_ptr<CPlayer>>::iterator it = LosePlayerList.begin(); it != LosePlayerList.end(); it++)
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

void CDaruma_FallDownGame::ResetPosition(void)
{
	//std::shared_ptr<CPlayer> ReturnPlayer = m_MovePlayer.front();
	for (int i = 0; i < m_MovePlayer.size(); i++)
	{
		if (m_MovePlayer.front()->GetPosition().x > -1500)
		{
			m_MovePlayer.front()->SetPosition(CVector3(m_MovePlayer.front()->GetPosition() - m_reset_speed));
			m_MovePlayer.emplace_back(m_MovePlayer.front());
			m_MovePlayer.pop_front();
		}
		else
		{
			m_MovePlayer.front()->SetActionFlag(true);
			m_MovePlayer.pop_front();
		}
	}
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

	if (m_TextPosition.x > 0)
	{
		m_TextPosition.x -= 10;
	}
	else
		m_TextPosition.x = 1100;

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
		std::shared_ptr<CGimmick> gimmick = (*it)->GetGimmick();
		std::shared_ptr<CPlayer> player;

		if (!gimmick) continue;

		for (int i = 0; i < dm.GetCurrentJoinPlayer(); i++)
		{
			player = um.GetPlayer((UNIT_ID)i);

			if (!player) continue;

			//�S���U��Ԃ��Ă鎞�̏���
			if (gimmick->GetState() == GIMMICK_STATE::PLAY && player->GetInvincibleFlag() == false)
			{
				if (player->GetPlayerMoving())
				{
					player->SetActionFlag(false);
					player->SetVelocity(CVector3::ZERO);

					m_TextureColor[i] = 0xffffffff;

					std::shared_ptr<CSkill> skill = player->GetSkill();
					if (skill->GetSkillID() == SKILL_ID::RESURRECT_DARUMA && skill->GetState() != SKILL_STATE::COOLDOWN)
						skill->SetState(SKILL_STATE::ACTIVE);
					else
					{
						m_MovePlayer.emplace_back(player);
					}
				}
			}
			else
			{
				m_TextureColor[i] = 0x00000000;

				if (player->GetPosition().x <= -1500)
				{
					player->SetActionFlag(true);
				}

				if ((player->GetPosition().x >= m_goal_position.x)&& (player->GetPosition().z <= m_goal_position.z + 100)&& (player->GetPosition().z >= m_goal_position.z - 100))
				{
					m_TempFirstNum = i;
					Ranking();
				}
			}
			if (m_MovePlayer.empty() == false)
				ResetPosition();
		}
	}

	


	if (m_Timer.Finished())
	{
		float FirstPosX = -1500;
		for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
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
	CSoundManager::GetInstance().Finalize();
}