#include "dodgeball_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../launcher/launcher.h"

//�㉺���E��4���� �~ �e������3���� �� 12��
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(    0,   0, 1800),CVector3(  900,   0, 1550),CVector3(- 900,   0, 1550),	//��
	CVector3(    0,   0,-1800),CVector3(- 900,   0,-1550),CVector3(  900,   0,-1550),	//��
	CVector3( 1800,   0,    0),CVector3( 1550,   0,- 900),CVector3( 1550,   0,  900),	//�E
	CVector3(-1800,   0,    0),CVector3(-1550,   0,  900),CVector3(-1550,   0,- 900)	//��
};

//�㉺���E��4����
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0, 180,0),CVector3(0, 210,0),CVector3(0, 150,0),	//��
	CVector3(0,   0,0),CVector3(0,  30,0),CVector3(0, -30,0),	//��
	CVector3(0, -90,0),CVector3(0, -60,0),CVector3(0,-120,0),	//�E
	CVector3(0,  90,0),CVector3(0, 120,0),CVector3(0,  60,0)	//��
};

const int			CDodgeBallGame::m_max_cannnon_count = 3;
const float			CDodgeBallGame::m_cannnon_spawn_time = 3.0f;
const float			CDodgeBallGame::m_initial_shot_time = 2.0f;
const float			CDodgeBallGame::m_min_shot_time = 0.1f;
const float			CDodgeBallGame::m_shot_time_acceleration = 0.03f;
const float			CDodgeBallGame::m_defeat_distance = 3000.0f;
const CVector3		CDodgeBallGame::m_camera_position = CVector3(0, 2500.0f, -1800.0f);
const CVector3		CDodgeBallGame::m_camera_direction = CVector3(0, -1.0f, 0.6f);

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
	m_SpawnTimer.SetUp(0);
	m_ShotTimer.SetUp(m_initial_shot_time);
	CGame::Initialize();

	//CStage::GetInstance().Initialize();
	CObjectManager::GetInstance().Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT,CTransform(CVector3(0.0f,-100.0f,0.0f)));

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	m_DebugText = "�h�b�W�{�[���Q�[��";

	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(-100, 0, 0));
	//CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, 0));

	CLauncher::GetInstance().Initialize();
	CBulletManager::GetInstance().Initialize();
}

void CDodgeBallGame::Update(void)
{
	//CStage::GetInstance().Update();
	CGame::Update();
	CCamera::GetInstance().Update();
	CLauncher::GetInstance().Update();
	CBulletManager::GetInstance().Update();
}

void CDodgeBallGame::Draw(void)
{
	//CStage::GetInstance().Draw();
	CGame::Draw();
	CBulletManager::GetInstance().Draw();
}

void CDodgeBallGame::Finalize(void)
{
	CGame::Finalize();
	//CStage::GetInstance().Finalize();
	CCamera::GetInstance().Finalize();
	CLauncher::GetInstance().Finalize();
	CBulletManager::GetInstance().Finalize();
}

void CDodgeBallGame::Start(void)
{
	CGame::Start();
}

void CDodgeBallGame::Play(void)
{
	CGame::Play();
	
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
		if (m_NowShotTime > m_min_shot_time)
		{
			m_NowShotTime -= m_shot_time_acceleration * m_NowShotTime;

			if (m_NowShotTime < m_min_shot_time)
				m_NowShotTime = m_min_shot_time;
		}

		m_ShotTimer.SetUp(m_NowShotTime);

		IObject* temp = ChooseCannon();
		if(temp != nullptr)
			temp->GetGimmick()->SetSwitch(true);
	}

	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		if ((*it)->GetPosition().Length() > m_defeat_distance)
			(*it)->SetDefeatFlag(true);

		++it;
	}
}

void CDodgeBallGame::Finish(void)
{
	CGame::Finish();
}

void CDodgeBallGame::SpawnCannnon(void)
{

	//��C�I�u�W�F�N�g�̐������W����ѐ�����]�l�̃Z�b�g
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * 3 + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir * 3 + m_CannonCount];

	//��C�I�u�W�F�N�g�̐���
	IObject* CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON_OBJECT, Temp);

	//��C�M�~�b�N�̃Z�b�g
	CGimmickManager::GetInstance().Create(GIMMICK_ID::DODGEBALL_GIMMICK, CannonObject);
}


IObject* CDodgeBallGame::ChooseCannon(void)
{
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty())
		return nullptr;

	CObjectManager::OBJECT_LIST ReadyCannonObjectList;
	CObjectManager::OBJECT_LIST::iterator it;

	for (it = objectList.begin(); it != objectList.end(); it++)
	{
		CDodgeBallGimmick* DodgeBallGimmick = nullptr;

		if((*it)->GetGimmick() != nullptr)
			DodgeBallGimmick = dynamic_cast<CDodgeBallGimmick*>((*it)->GetGimmick());


		if (DodgeBallGimmick != nullptr)
		{
			if (DodgeBallGimmick->GetNowState() == CANNON_STATE::MOVE && 
				!DodgeBallGimmick->GetShotFlag())
			{
				ReadyCannonObjectList.push_back((*it));
			}
		}
	}

	if (ReadyCannonObjectList.size() < 1)
		return nullptr;

	it = ReadyCannonObjectList.begin();
	int index = rand() % ReadyCannonObjectList.size();

	std::advance(it, index);

	return *it;
}