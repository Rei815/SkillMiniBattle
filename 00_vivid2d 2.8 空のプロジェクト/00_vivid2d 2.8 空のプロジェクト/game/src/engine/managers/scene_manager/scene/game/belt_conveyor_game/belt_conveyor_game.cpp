#include "belt_conveyor_game.h"
#include "../../../../data_manager\data_manager.h"
#include "../../../../object_manager\object_manager.h"
#include "../../../../camera\camera.h"
#include "../../../../skill_manager\skill_manager.h"
#include "../../../../scene_manager\scene_manager.h"
#include "../../../../../../engine\components\transform_component\transform_component.h"
#include "../../../../../../game/components/player_component/player_component.h"
#include "../../../../../../game/components/gimmick_component/belt_conveyor_gimmick_componet/belt_conveyor_gimmick_componet.h"

const float		CBeltConveyorGame::m_defeat_height			= -500.0f;
const CVector3	CBeltConveyorGame::m_camera_position		= CVector3(0.0f, 800.0f, -1350.0f);
const CVector3	CBeltConveyorGame::m_camera_direction		= CVector3(0.0f, -0.45f, 0.6f);

const CVector3	CBeltConveyorGame::m_belt_conveyor_position	= CVector3(0.0f, -100.0f, 0.0f);
const float		CBeltConveyorGame::m_belt_conveyor_rotate_y	= -135.0f;
const float     CBeltConveyorGame::m_belt_conveyor_scale	= 0.6f;

const CVector3 CBeltConveyorGame::m_player_spawnpos_list[] =
{
	CVector3(-150, 0,  75),	//Player1
	CVector3( -50, 0,  25),	//Player2
	CVector3(  50, 0, -25),	//Player3
	CVector3( 150, 0, -75)	//Player4
};

const CVector3 CBeltConveyorGame::m_player_default_forward = CVector3(1.0f, 0.0f, 1.0f);


CBeltConveyorGame::CBeltConveyorGame(void)
	: m_StageObject(nullptr)
{

}

CBeltConveyorGame::~CBeltConveyorGame(void)
{

}


void CBeltConveyorGame::Initialize(SCENE_ID scene_id)
{
	SetLightDirection(CVector3::DOWN + CVector3::FORWARD);

	CGame::Initialize(scene_id);

	m_BackGround.Initialize("data\\Textures\\belt_conveyor_bg.png");

	//ステージ生成
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::BELT_CONVEYOR, CTransform(m_belt_conveyor_position, CVector3(0.0f, m_belt_conveyor_rotate_y, 0.0f)));
	m_StageObject->GetComponent<TransformComponent>()->SetScale(m_belt_conveyor_scale);
	
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
	CTransform transform = CTransform();
}

void CBeltConveyorGame::Update(void)
{
	CGame::Update();

	if (!CSceneManager::GetInstance().Pausing())
	{
		CCamera::GetInstance().Update();
	}
}

void CBeltConveyorGame::Draw(void)
{
	m_BackGround.Draw();

	CGame::Draw();
}

void CBeltConveyorGame::Finalize(void)
{
	CGame::Finalize();
	CSoundManager::GetInstance().Finalize();

	CCamera::GetInstance().Finalize();

	//BGM停止
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
}

void CBeltConveyorGame::Start(void)
{
	CGame::Start();

	//プレイになるタイミングで 、ギミックを付与する
	if (m_GameState == GAME_STATE::PLAY)
		m_StageObject->AddComponent<BeltConveyorGimmickComponent>();
}

void CBeltConveyorGame::Play(void)
{
	CGame::Play();

	//ポーズだったら処理をスキップ
	if (CSceneManager::GetInstance().Pausing())
		return;
}

void CBeltConveyorGame::Finish(void)
{
	CGame::Finish();
}

void CBeltConveyorGame::CheckFinish(void)
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


		// 落下判定
		if (transform->GetPosition().y < m_defeat_height)
		{
			auto skill = playerComp->GetSkill();
			if (skill->GetSkillID() == SKILL_ID::RESURRECT_BELT && skill->GetState() != SKILL_STATE::COOLDOWN)
			{
				skill->SetState(SKILL_STATE::ACTIVE);
				continue;
			}
			// 敗北処理
			playerComp->SetDefeated(true);
			AddRanking(playerComp->GetPlayerID());
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