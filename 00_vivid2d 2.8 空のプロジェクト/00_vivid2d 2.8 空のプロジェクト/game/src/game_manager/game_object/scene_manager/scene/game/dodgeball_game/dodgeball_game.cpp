#include "dodgeball_game.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../launcher/launcher.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"


#include "../../../../gimmick_manager/gimmick/fall_gimmick/fall_gimmick.h"
#include "../../../scene_manager.h"

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
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT,StageTr);
	m_StageObject->SetScale(m_default_stage_scale);

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM�Đ�
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	//�v���C���[�̃X�|�[��
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		std::shared_ptr<IUnit> unit = CUnitManager::GetInstance().Create((UNIT_ID)i, m_player_spawnpos_list[i]);
		std::shared_ptr<CPlayer> Player = dynamic_pointer_cast<CPlayer>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.emplace_back(unit);
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
	//CStage::GetInstance().Draw();
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

		std::shared_ptr<IObject> temp = ChooseCannon();
		if(temp != nullptr)
			temp->GetGimmick()->SetOperationFlag(true);
	}

	m_StageShrinkTimer.Update();
	if (m_StageShrinkFlg)
	{
		if (m_StageShrinkTimer.Finished())
		{
			m_StageObject->SetScale(0.0f);
		}
		else
		{
			m_StageObject->SetScale((m_stage_shrink_time - m_StageShrinkTimer.GetTimer()) / m_stage_shrink_time * m_default_stage_scale);
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
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		std::shared_ptr<IUnit> unit = (*it);
		++it;

		if (unit->GetDefeatFlag() == true)	continue;

		if (unit->GetPosition().Length() > m_defeat_distance)
		{
			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(unit->GetUnitID());

			//�O�̂��߁A����t���[���őS�ł����ꍇ�Ɉ�l�c���悤�ɂ���
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}

	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//�����c������l�������ɂ���
			CDataManager::GetInstance().PlayerWin((*m_EntryList.begin())->GetUnitID());

			CDataManager::GetInstance().AddLastGameRanking((*m_EntryList.begin())->GetUnitID());

			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//����Ă��邽�߃��U���g���X�g���珟���ɂ���
			CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());

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
	std::shared_ptr<IObject> CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON_OBJECT, Temp);

	//��C�M�~�b�N�̃Z�b�g
	CGimmickManager::GetInstance().Create(GIMMICK_ID::DODGEBALL_GIMMICK, CannonObject);
}


std::shared_ptr<IObject> CDodgeBallGame::ChooseCannon(void)
{
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty())
		return nullptr;

	CObjectManager::OBJECT_LIST ReadyCannonObjectList;
	ReadyCannonObjectList.clear();
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();

	while (it != objectList.end())
	{
		std::shared_ptr<CDodgeBallGimmick> DodgeBallGimmick = nullptr;

		if ((*it)->GetGimmick() != nullptr)
			DodgeBallGimmick = dynamic_pointer_cast<CDodgeBallGimmick>((*it)->GetGimmick());


		if (DodgeBallGimmick != nullptr)
		{
			if (DodgeBallGimmick->GetNowState() == CANNON_STATE::MOVE &&
				!DodgeBallGimmick->GetShotFlag())
			{
				ReadyCannonObjectList.push_back((*it));
			}
		}

		++it;
	}

	if (ReadyCannonObjectList.size() < 1)
		return nullptr;

	it = ReadyCannonObjectList.begin();
	int index = rand() % ReadyCannonObjectList.size();

	std::advance(it, index);

	return *it;
}