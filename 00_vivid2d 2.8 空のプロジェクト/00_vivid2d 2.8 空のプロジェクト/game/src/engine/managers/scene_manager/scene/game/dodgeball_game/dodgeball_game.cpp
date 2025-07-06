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
#include "../../../../../../game/components/player_component/player_component.h"
#include "../../../../../../game/components/gimmick_component/dodge_ball_gimmick_component/dodge_ball_gimmick_component.h"
#include "../../../../../../engine/components/transform_component/transform_component.h"

// ��C�̈ʒu
// �㉺���E��4���� �~ �e������5���� �� 20��
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(    0,   0, 1440),CVector3(  444,   0, 1370),CVector3(  845,   0, 1165),CVector3( 1165,   0,  845),CVector3( 1370,   0,  444),	//��
	CVector3( 1440,   0,    0),CVector3( 1370,   0,- 444),CVector3( 1165,   0,- 845),CVector3(  845,   0,-1165),CVector3(  444,   0,-1370),	//�E
	CVector3(    0,   0,-1440),CVector3(- 444,   0,-1370),CVector3(- 845,   0,-1165),CVector3(-1165,   0,- 845),CVector3(-1370,   0,- 444),	//��
	CVector3(-1440,   0,    0),CVector3(-1370,   0,  444),CVector3(-1165,   0,  845),CVector3(- 845,   0, 1165),CVector3(- 444,   0, 1370)	//��
};

// ��C�̃f�t�H���g�̌���
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0,-180,0),CVector3(0,-162,0),CVector3(0,-144,0),CVector3(0,-126,0),CVector3(0,-108,0),	//��
	CVector3(0, -90,0),CVector3(0, -72,0),CVector3(0, -54,0),CVector3(0,- 36,0),CVector3(0,- 18,0),	//�E
	CVector3(0,   0,0),CVector3(0,  18,0),CVector3(0,  36,0),CVector3(0,  54,0),CVector3(0,  72,0),	//��
	CVector3(0,  90,0),CVector3(0, 108,0),CVector3(0, 126,0),CVector3(0, 144,0),CVector3(0, 162,0)	//��
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

	//�X�e�[�W����
	CTransform StageTr = CTransform(m_default_stage_position, m_default_stage_rotation);
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::DODGEBALL_STAGE,StageTr);
	auto stageTransform = m_StageObject->GetComponent<TransformComponent>();
	stageTransform->SetScale(CVector3(m_default_stage_scale, m_default_stage_scale, m_default_stage_scale));

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM�Đ�
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	//�v���C���[�̃X�|�[��
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

	//BGM��~
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);

}

void CDodgeBallGame::Start(void)
{
	CGame::Start();
}

void CDodgeBallGame::Play(void)
{
	CGame::Play();

	//�|�[�Y�������珈�����X�L�b�v
	if (CSceneManager::GetInstance().Pausing())
		return;
	
	if (m_CannonCount < m_max_cannnon_count)
	{
		m_SpawnTimer.Update();

		if (m_SpawnTimer.Finished())
		{
			m_SpawnTimer.SetUp(m_cannnon_spawn_time);

			//��C�̐���
			SpawnCannnon();

			//���̖C�̌�����ύX
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
	 *  @brief      �I������
	 */
void CDodgeBallGame::CheckFinish(void)
{
	// ���t���[���APlayerComponent�����I�u�W�F�N�g��S�Ď擾
	auto activePlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

	int trulyActivePlayerCount = 0;

	// --- �E���v���C���[�̃`�F�b�N ---
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
			playerComp->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(playerComp->GetPlayerID());

			//�O�̂��߁A����t���[���őS�ł����ꍇ�Ɉ�l�c���悤�ɂ���
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}

	//��l�ȏ�̏ꍇ
	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		auto winnerComp = m_EntryList.begin()->get()->GetComponent<PlayerComponent>();
		//��l�������c�������ɏI��
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//�����c������l�������ɂ���
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());

			CDataManager::GetInstance().AddLastGameRanking(winnerComp->GetPlayerID());
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else //��l�̏ꍇ
	{
		auto winnerComp = m_ResultList.begin()->get()->GetComponent<PlayerComponent>();

		//���ꂽ��I��
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//����Ă��邽�߃��U���g���X�g���珟���ɂ���
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}

}

void CDodgeBallGame::SpawnCannnon(void)
{

	//��C�I�u�W�F�N�g�̐������W����ѐ�����]�l�̃Z�b�g
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * m_max_cannnon_count + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir * m_max_cannnon_count + m_CannonCount];

	//��C�I�u�W�F�N�g�̐���
	std::shared_ptr<CGameObject> CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON, Temp);
}


std::shared_ptr<CGameObject> CDodgeBallGame::ChooseCannon(void)
{
	// ���t���[���APlayerComponent�����I�u�W�F�N�g��S�Ď擾
	auto allCannons = CObjectManager::GetInstance().GetObjectsWithComponent<DodgeBallGimmickComponent>();

	std::vector<std::shared_ptr<CGameObject>> readyCannonsList;
	for (auto& cannonObject : allCannons)
	{
		auto gimmickComp = cannonObject->GetComponent<DodgeBallGimmickComponent>();

		// �����ɍ������̂������i�荞��
		if (gimmickComp && gimmickComp->GetNowState() == CANNON_STATE::MOVE && !gimmickComp->GetShotFlag())
		{
			readyCannonsList.push_back(cannonObject);
		}
	}

	// 4. ���ˉ\�ȑ�C��1���Ȃ���΁Anullptr��Ԃ�
	if (readyCannonsList.empty())
	{
		return nullptr;
	}

	// 5. ����OK�̃��X�g����A�����_����1�I��ŕԂ�
	int index = rand() % readyCannonsList.size();
	return readyCannonsList[index];
}