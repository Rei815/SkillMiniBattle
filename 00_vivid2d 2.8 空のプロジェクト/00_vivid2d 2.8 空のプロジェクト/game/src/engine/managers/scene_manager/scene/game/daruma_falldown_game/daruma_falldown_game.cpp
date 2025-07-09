#include "daruma_falldown_game.h"
#include <EffekseerForDXLib.h>
#include "../../../../object_manager/object_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"
#include "game/components/player_component/player_component.h"
#include "engine/components/transform_component/transform_component.h"
#include <algorithm>
#include "game/components/gimmick_component/daruma_fall_down_gimmick_component/daruma_fall_down_gimmick_component.h"
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
		std::shared_ptr<CGameObject> player = CObjectManager::GetInstance().Create(OBJECT_ID::PLAYER, CVector3(-1500, 100, 100 * i), (PLAYER_ID)i);
		auto playerComp = player->GetComponent<PlayerComponent>();
		auto transform = player->GetComponent<TransformComponent>();
		m_StartPosition[i] = transform->GetPosition();
		if (playerComp != nullptr)
		{
			playerComp->SetActionFlag(false);
			playerComp->SetForwardVector(m_player_default_forward);
			playerComp->MulMoveSpeedRate(m_move_speed);
		}
	}

	CSkillManager::GetInstance().SetSkill();

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//オブジェクトの生成
	m_OgreObject = CObjectManager::GetInstance().Create(OBJECT_ID::OGRE, Temp);

	CObjectManager::GetInstance().Create(OBJECT_ID::DARUMA_FALLDOWN_STAGE, CTransform(CVector3(0,-1000, -100)));

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
	// 毎フレーム、PlayerComponentを持つオブジェクトを全て取得
	auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
	PLAYER_ID winnerId = (PLAYER_ID)m_TempFirstNum; // 勝利者のID
	// 2. 敗者リストを作成
	std::vector<std::shared_ptr<CGameObject>> loserObjects;
	for (auto& playerObject : allPlayers)
	{
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		if (playerComp)
		{
			// 勝利者でなければ、敗者リストに追加
			if (playerComp->GetPlayerID() != winnerId)
			{
				playerComp->SetDefeated(true); // 敗北状態に設定
				loserObjects.push_back(playerObject);
			}
		}
	}
	// 3. 敗者をX座標でソートする (昇順：Xが小さいほど順位が上)
	std::sort(loserObjects.begin(), loserObjects.end(),
		[](const auto& a, const auto& b) {
			auto transA = a->GetComponent<TransformComponent>();
			auto transB = b->GetComponent<TransformComponent>();
			// transformが両方有効な場合のみ比較
			if (transA && transB) {
				return transA->GetPosition().x < transB->GetPosition().x;
			}
			return false;
		});

	// 4. ソートされた順に、敗者をランキングに登録
	for (const auto& loserObject : loserObjects)
	{
		if (auto playerComp = loserObject->GetComponent<PlayerComponent>())
		{
			CDataManager::GetInstance().AddLastGameRanking(playerComp->GetPlayerID());
		}
	}
	CDataManager::GetInstance().AddLastGameRanking(winnerId);
	CDataManager::GetInstance().PlayerWin(winnerId);

	CGame::SetGameState(GAME_STATE::FINISH);
}

void CDaruma_FallDownGame::ResetPosition(void)
{
	for (int i = 0; i < m_MovePlayer.size(); i++)
	{
		auto playerComp = m_MovePlayer.front()->GetComponent<PlayerComponent>();
		auto transform = m_MovePlayer.front()->GetComponent<TransformComponent>();

		if (transform->GetPosition().x > -1500)
		{
			transform->SetPosition(CVector3(transform->GetPosition() - m_reset_speed));
			m_MovePlayer.emplace_back(m_MovePlayer.front());
			m_MovePlayer.pop_front();
		}
		else
		{
			playerComp->SetActionFlag(true);
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
	CDataManager& dm = CDataManager::GetInstance();

	if (m_TextPosition.x > 0)
	{
		m_TextPosition.x -= 10;
	}
	else
		m_TextPosition.x = 1100;

	if (!m_GimmickOn)
	{
		m_OgreObject->AddComponent<DarumaFallDownGimmickComponent>();
		m_GimmickOn = true;
	}

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it;

	m_Timer.Update();

	// DarumaGimmickComponentは、鬼オブジェクト用のラッパーコンポーネントとします
	auto darumaObjects = CObjectManager::GetInstance().GetObjectsWithComponent<DarumaFallDownGimmickComponent>();
	auto gimmick = darumaObjects.begin()->get()->GetComponent<DarumaFallDownGimmickComponent>();
	auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

	for (auto& playerObject : allPlayers)
	{
			auto player = playerObject->GetComponent<PlayerComponent>();
			auto transform = playerObject->GetComponent<TransformComponent>();

			if (!player) continue;

			//鬼が振り返ってる時の処理
			if (gimmick->GetState() == GIMMICK_STATE::PLAY && player->IsInvincible() == false)
			{
				if (player->GetPlayerMoving())
				{
					player->SetActionFlag(false);
					player->SetVelocity(CVector3::ZERO);

					m_TextureColor[(int)player->GetPlayerID()] = 0xffffffff;

					std::shared_ptr<CSkill> skill = player->GetSkill();
					if (skill->GetSkillID() == SKILL_ID::RESURRECT_DARUMA && skill->GetState() != SKILL_STATE::COOLDOWN)
						skill->SetState(SKILL_STATE::ACTIVE);
					else
					{
						m_MovePlayer.emplace_back(playerObject);
					}
				}
			}
			else
			{
				m_TextureColor[(int)player->GetPlayerID()] = 0x00000000;

				if (transform->GetPosition().x <= -1500)
				{
					player->SetActionFlag(true);
				}

				if ((transform->GetPosition().x >= m_goal_position.x)&& (transform->GetPosition().z <= m_goal_position.z + 100)&& (transform->GetPosition().z >= m_goal_position.z - 100))
				{
					m_TempFirstNum = (int)player->GetPlayerID();
					Ranking();
				}
			}
			if (m_MovePlayer.empty() == false)
				ResetPosition();
	}

	


	if (m_Timer.Finished())
	{
		float FirstPosX = -1500;

		for (auto& player : allPlayers)
		{
			auto transform = player->GetComponent<TransformComponent>();
			float TempPosX = transform->GetPosition().x;
			if (TempPosX >= FirstPosX)
			{
				m_TempFirstNum = (int)player->GetID();
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