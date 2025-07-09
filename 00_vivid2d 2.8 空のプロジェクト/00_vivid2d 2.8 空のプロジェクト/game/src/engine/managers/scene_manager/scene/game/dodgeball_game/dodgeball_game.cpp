#include "dodgeball_game.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../launcher/launcher.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"


#include "../../../scene_manager.h"
#include "game/components/player_component/player_component.h"
#include "game/components/gimmick_component/dodge_ball_gimmick_component/dodge_ball_gimmick_component.h"
#include "engine/components/transform_component/transform_component.h"

// 大砲の位置
// 上下左右の4方向 × 各方向に5つずつ ＝ 20こ
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(    0,   0, 1440),CVector3(  444,   0, 1370),CVector3(  845,   0, 1165),CVector3( 1165,   0,  845),CVector3( 1370,   0,  444),	//上
	CVector3( 1440,   0,    0),CVector3( 1370,   0,- 444),CVector3( 1165,   0,- 845),CVector3(  845,   0,-1165),CVector3(  444,   0,-1370),	//右
	CVector3(    0,   0,-1440),CVector3(- 444,   0,-1370),CVector3(- 845,   0,-1165),CVector3(-1165,   0,- 845),CVector3(-1370,   0,- 444),	//下
	CVector3(-1440,   0,    0),CVector3(-1370,   0,  444),CVector3(-1165,   0,  845),CVector3(- 845,   0, 1165),CVector3(- 444,   0, 1370)	//左
};

// 大砲のデフォルトの向き
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0,-180,0),CVector3(0,-162,0),CVector3(0,-144,0),CVector3(0,-126,0),CVector3(0,-108,0),	//上
	CVector3(0, -90,0),CVector3(0, -72,0),CVector3(0, -54,0),CVector3(0,- 36,0),CVector3(0,- 18,0),	//右
	CVector3(0,   0,0),CVector3(0,  18,0),CVector3(0,  36,0),CVector3(0,  54,0),CVector3(0,  72,0),	//下
	CVector3(0,  90,0),CVector3(0, 108,0),CVector3(0, 126,0),CVector3(0, 144,0),CVector3(0, 162,0)	//左
};

const CVector3 CDodgeBallGame::m_player_spawnpos_list[] =
{
	CVector3(-100, 0,  100),	//Player1
	CVector3( 100, 0,  100),	//Player2
	CVector3(-100, 0, -100),	//Player3
	CVector3( 100, 0, -100)		//Player4
};

const CVector3 CDodgeBallGame::m_player_default_forward = CVector3(0.0f,0.0f,-1.0f);

const int			CDodgeBallGame::m_max_cannnon_count = 5;
const float			CDodgeBallGame::m_cannnon_spawn_time = 2.0f;
const float			CDodgeBallGame::m_initial_shot_time = 2.0f;
const float			CDodgeBallGame::m_min_shot_time = 0.1f;
const float			CDodgeBallGame::m_shot_time_acceleration = 0.04f;
const float			CDodgeBallGame::m_stage_shrink_time = 60.0f;
const CVector3		CDodgeBallGame::m_default_stage_position = CVector3(0.0f, -100.0f, 0.0f);
const CVector3		CDodgeBallGame::m_default_stage_rotation = CVector3::ZERO;
const float			CDodgeBallGame::m_default_stage_scale = 0.8f;
const float			CDodgeBallGame::m_defeat_distance = 3000.0f;
const CVector3		CDodgeBallGame::m_camera_position = CVector3(0, 1600.0f, -1450.0f);
const CVector3		CDodgeBallGame::m_camera_direction = CVector3(0, -1.0f, 0.6f);

CDodgeBallGame::CDodgeBallGame(void)
	:m_CannonCount(0)
	,m_SpawnTimer(0)
	,m_ShotTimer(m_initial_shot_time)
	,m_NowShotTime(m_initial_shot_time)
	,m_StageShrinkTimer()
	,m_StageShrinkFlg(false)
	,m_StageObject(nullptr)
	,m_NextCannnonDir(CANNON_DIRECTION::UP)
	,m_bgm(nullptr)
{
}

CDodgeBallGame::~CDodgeBallGame(void)
{

}

void CDodgeBallGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);

	m_BackGround.Initialize("data\\Textures\\dodge_ball_bg.jpg");

	m_SpawnTimer.SetUp(0);
	m_ShotTimer.SetUp(m_initial_shot_time);
	m_StageShrinkTimer.SetUp(m_stage_shrink_time);

	//ステージ生成
	CTransform StageTr = CTransform(m_default_stage_position, m_default_stage_rotation);
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::DODGEBALL_STAGE,StageTr);
	auto stageTransform = m_StageObject->GetComponent<TransformComponent>();
	stageTransform->SetScale(CVector3(m_default_stage_scale, m_default_stage_scale, m_default_stage_scale));

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	//プレイヤーのスポーン
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		std::shared_ptr<CGameObject> gameObject = CObjectManager::GetInstance().Create(OBJECT_ID::PLAYER, m_player_spawnpos_list[i], (PLAYER_ID)i);
		auto Player = gameObject->GetComponent<PlayerComponent>();
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.emplace_back(gameObject);
	}

	CSkillManager::GetInstance().SetSkill();

	CLauncher::GetInstance().Initialize();
	CBulletManager::GetInstance().Initialize();

}

void CDodgeBallGame::Update(void)
{
	CGame::Update();

	if (!CSceneManager::GetInstance().Pausing())
	{
		CCamera::GetInstance().Update();
		CLauncher::GetInstance().Update();
		CBulletManager::GetInstance().Update();
	}
}

void CDodgeBallGame::Draw(void)
{
	m_BackGround.Draw();
	CBulletManager::GetInstance().Draw();
	CGame::Draw();
}

void CDodgeBallGame::Finalize(void)
{
	CGame::Finalize();
	CCamera::GetInstance().Finalize();
	CLauncher::GetInstance().Finalize();
	CBulletManager::GetInstance().Finalize();

	//BGM停止
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);

}

void CDodgeBallGame::Start(void)
{
	CGame::Start();
}

void CDodgeBallGame::Play(void)
{
	CGame::Play();

	//ポーズだったら処理をスキップ
	if (CSceneManager::GetInstance().Pausing())
		return;
	
	if (m_CannonCount < m_max_cannnon_count)
	{
		m_SpawnTimer.Update();

		if (m_SpawnTimer.Finished())
		{
			m_SpawnTimer.SetUp(m_cannnon_spawn_time);

			//大砲の生成
			SpawnCannnon();

			//次の砲の向きを変更
			int Temp = (int)m_NextCannnonDir;
			Temp++;
			if (Temp > (int)CANNON_DIRECTION::LEFT)
			{
				Temp = (int)CANNON_DIRECTION::UP;
				m_CannonCount++;
			}
			m_NextCannnonDir = (CANNON_DIRECTION)Temp;
		}
	}

	m_ShotTimer.Update();
	if (m_ShotTimer.Finished())
	{
		m_ShotTimer.Reset();
		if (m_NowShotTime > m_min_shot_time)
		{
			m_NowShotTime -= m_shot_time_acceleration * m_NowShotTime;

			if (m_NowShotTime < m_min_shot_time)
				m_NowShotTime = m_min_shot_time;
		}

		m_ShotTimer.SetUp(m_NowShotTime);

		std::shared_ptr<CGameObject> temp = ChooseCannon();
		if (temp != nullptr)
		{
			auto gimmick = temp->GetComponent<DodgeBallGimmickComponent>();
			gimmick->SetOperationFlag(true);
		}
	}

	m_StageShrinkTimer.Update();
	if (m_StageShrinkFlg)
	{
		auto stageTransform = m_StageObject->GetComponent<TransformComponent>();
		if (m_StageShrinkTimer.Finished())
		{
			stageTransform->SetScale(CVector3());
		}
		else
		{
			stageTransform->SetScale((m_stage_shrink_time - m_StageShrinkTimer.GetTimer()) / m_stage_shrink_time * m_default_stage_scale);
		}
	}
	else
	{
		if (m_StageShrinkTimer.Finished())
		{
			m_StageShrinkTimer.Reset();
			m_StageShrinkFlg = true;
		}
	}
}

void CDodgeBallGame::Finish(void)
{
	CGame::Finish();

	CSoundManager::GetInstance().Finalize();


}

/*!
	 *  @brief      終了判定
	 */
void CDodgeBallGame::CheckFinish(void)
{
	// 毎フレーム、PlayerComponentを持つオブジェクトを全て取得
	auto activePlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

	int trulyActivePlayerCount = 0;

	// --- 脱落プレイヤーのチェック ---
	for (auto& playerObject : activePlayers)
	{
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		auto transform = playerObject->GetComponent<TransformComponent>();

		if (!playerComp || !transform) continue;

		if (playerComp->IsDefeated())
		{
			continue;
		}

		trulyActivePlayerCount++;

		if (transform->GetLength() > m_defeat_distance)
		{
			AddRanking(playerComp->GetPlayerID());
			playerComp->SetDefeated(true);

			CDataManager::GetInstance().AddLastGameRanking(playerComp->GetPlayerID());

			//念のため、同一フレームで全滅した場合に一人残すようにする
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}

	//二人以上の場合
	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		auto winnerComp = m_EntryList.begin()->get()->GetComponent<PlayerComponent>();
		//一人が生き残った時に終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//生き残った一人を勝ちにする
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());

			CDataManager::GetInstance().AddLastGameRanking(winnerComp->GetPlayerID());
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else //一人の場合
	{
		auto winnerComp = m_ResultList.begin()->get()->GetComponent<PlayerComponent>();

		//やられたら終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//やられているためリザルトリストから勝ちにする
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}

}

void CDodgeBallGame::SpawnCannnon(void)
{

	//大砲オブジェクトの生成座標および生成回転値のセット
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * m_max_cannnon_count + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir * m_max_cannnon_count + m_CannonCount];

	//大砲オブジェクトの生成
	std::shared_ptr<CGameObject> CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON, Temp);
}


std::shared_ptr<CGameObject> CDodgeBallGame::ChooseCannon(void)
{
	// 毎フレーム、PlayerComponentを持つオブジェクトを全て取得
	auto allCannons = CObjectManager::GetInstance().GetObjectsWithComponent<DodgeBallGimmickComponent>();

	std::vector<std::shared_ptr<CGameObject>> readyCannonsList;
	for (auto& cannonObject : allCannons)
	{
		auto gimmickComp = cannonObject->GetComponent<DodgeBallGimmickComponent>();

		// 条件に合うものだけを絞り込む
		if (gimmickComp && gimmickComp->GetNowState() == CANNON_STATE::MOVE && !gimmickComp->GetShotFlag())
		{
			readyCannonsList.push_back(cannonObject);
		}
	}

	// 4. 発射可能な大砲が1つもなければ、nullptrを返す
	if (readyCannonsList.empty())
	{
		return nullptr;
	}

	// 5. 準備OKのリストから、ランダムに1つ選んで返す
	int index = rand() % readyCannonsList.size();
	return readyCannonsList[index];
}