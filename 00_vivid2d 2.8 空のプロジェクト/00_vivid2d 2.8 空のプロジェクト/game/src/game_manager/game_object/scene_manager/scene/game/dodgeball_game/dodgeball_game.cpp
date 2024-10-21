#include "dodgeball_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"

//�㉺���E��4���� �~ �e������3���� �� 12��
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(   0,   0, 500),CVector3( 250,   0, 500),CVector3(-250,   0, 500),	//��
	CVector3(   0,   0,-500),CVector3(-250,   0,-500),CVector3( 250,   0,-500),	//��
	CVector3( 500,   0,   0),CVector3( 500,   0,-250),CVector3( 500,   0, 250),	//�E
	CVector3(-500,   0,   0),CVector3(-500,   0, 250),CVector3(-500,   0,-250)	//��
};

//�㉺���E��4����
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0,180,0),	//��
	CVector3(0,  0,0),	//��
	CVector3(0,-90,0),	//�E
	CVector3(0, 90,0)	//��
};

const int			CDodgeBallGame::m_max_cannnon_count = 3;
const float			CDodgeBallGame::m_cannnon_spawn_time = 3.0f;
const float			CDodgeBallGame::m_initial_shot_time = 1.5f;
const float			CDodgeBallGame::m_min_shot_time = 0.5f;
const float			CDodgeBallGame::m_shot_time_acceleration = 0.1f;
const CVector3		CDodgeBallGame::m_camera_position = CVector3(0, 600.0f, -1000.0f);
const CVector3		CDodgeBallGame::m_camera_direction = CVector3(0, -0.75f, 1.0f);

CDodgeBallGame::CDodgeBallGame(void)
	:m_CannonCount(0)
	,m_SpawnTimer()
	,m_ShotTimer()
	,m_NowShotTime(m_initial_shot_time)
	,m_NextCannnonDir(CANNON_DIRECTION::UP)

{

}

CDodgeBallGame::~CDodgeBallGame(void)
{

}

void CDodgeBallGame::Initialize(void)
{
	m_SpawnTimer.SetUp(m_cannnon_spawn_time);
	m_ShotTimer.SetUp(m_initial_shot_time);
	CGame::Initialize();
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	m_DebugText = "�h�b�W�{�[���Q�[��";

	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(-100, 0, 0));
	//CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, 0));
}

void CDodgeBallGame::Update(void)
{
	if (m_CannonCount < m_max_cannnon_count)
	{
		m_SpawnTimer.Update();

		if (m_SpawnTimer.Finished())
		{
			m_SpawnTimer.Reset();

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
		//ChooseCannon()->GetGimmick()->SetSwitch(true);
	}

}

void CDodgeBallGame::Draw(void)
{
	CGame::Draw();
}

void CDodgeBallGame::Finalize(void)
{
	CGame::Finalize();
	CCamera::GetInstance().Finalize();
}

void CDodgeBallGame::Start(void)
{
	CGame::Start();
}

void CDodgeBallGame::Play(void)
{
	CGame::Play();
}

void CDodgeBallGame::Finish(void)
{
	CGame::Finish();
}

void CDodgeBallGame::SpawnCannnon(void)
{
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * 3 + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir];

	//��C�I�u�W�F�N�g�̐���
	IObject* CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON_OBJECT, Temp);

	//��C�M�~�b�N�̃Z�b�g
	CGimmickManager::GetInstance().Create(GIMMICK_ID::DODGEBALL_GIMMICK, CannonObject);
}


IObject* CDodgeBallGame::ChooseCannon(void)
{
	return nullptr;
}